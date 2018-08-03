#ifndef AUDIO_WAV_HPP
#define AUDIO_WAV_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include <memory>
#include <cstring>

namespace audio {
  typedef std::uint8_t u8;
  typedef std::uint16_t u16;
  typedef std::uint32_t u32;
  typedef std::uint64_t u64;
  typedef std::int8_t i8;
  typedef std::int16_t i16;
  typedef std::int32_t i32;
  typedef std::int64_t i64;
  constexpr double pi = 3.14159265358979323846264338327950288419716939937;
  struct wavHeader {
    char ID[4];
    i32 size;
    char type[4];
  };
  struct wavFormatChunk {
    char ID[4];
    i32 size;
    i16 audioFormat;
    i16 channelNum;
    i32 sampleRate;
    i32 byteRate;
    i16 blockAlign;
    i16 bitsPerSample;
  };
  struct wavDataChunk {
    char ID[4];
    i32 size;
    i32 dataOffset;
  };
  
  struct s16PCMFrame {
    i16 data[2048];
    //0-L 1-R 2-L 3-R
    i32 offset;
    inline i16 getLeftSoundTrackAt(i32 i) {return data[i * 2];}
    inline i16 getRightSoundTrackAt(i32 i) {return data[i * 2 + 1];}
    inline void setLeftSoundTrackAt(i32 i, i16 d) {data[i * 2] = d;}
    inline void setRightSoundTrackAt(i32 i, i16 d) {data[i * 2 + 1] = d;}
  };
  
  struct u8PCMFrame {
    u8 data[2048];
    i32 offset;
  };
  
  class wavReader {
  private:
    i64 offset;
    u8 *data;
    wavHeader header;
    i64 headeroff;
    wavFormatChunk format;
    i64 formatoff;
    wavDataChunk metadata;
    i64 metadataoff;
    i64 filesize;
  public:
    wavReader() = default;
    explicit wavReader(const char *filepath) {
      int fd = ::open(filepath, O_RDONLY);
      if (fd < 0) {
        perror("open");
        exit(-1);
      }
      struct stat st{};
      fstat(fd, &st);
      filesize = st.st_size;
      offset = 0;
      data = new u8[filesize];
      if (::read(fd, data, filesize) < 0) {
        perror("read");
        exit(-1);
      }
      close(fd);
    }
    bool isEnd() {
      return offset >= filesize;
    }
    bool isBad() {return data == nullptr;}
    ~wavReader() {
      delete data;
    }
    std::string readString(void *str, unsigned long size) {
      return std::string((char *) str, size);
    }
    void wavParse() {
      //Get header frame
      memmove(&header, data + offset, sizeof(header));
      headeroff = offset;
      offset += sizeof(header);
      //Get format frame
      for (;;) {
        while (data[offset] != 'f')offset++;
        if (readString(data + offset, 4) == "fmt ") {
          break;
        } else {
          offset++;
        }
      }
      memmove(&format, data + offset, sizeof(format));
      formatoff = offset;
      offset += sizeof(format);
      //Get data frame
      for (;;) {
        while (data[offset] != 'd')offset++;
        if (readString(data + offset, 4) == "data") {
          break;
        } else {
          offset++;
        }
      }
      memmove(&metadata, data + offset, sizeof(metadata) - sizeof(metadata.dataOffset));
      metadataoff = offset;
      offset += sizeof(metadata) - sizeof(metadata.dataOffset);
      metadata.dataOffset = offset;
    }
    wavHeader getHeader() {
      return header;
    }
    wavFormatChunk getFormat() {
      return format;
    };
    wavDataChunk getMetadata() {
      return metadata;
    };
    i64 getOffset() {
      return offset;
    }
    i64 getFilesize() {
      return filesize;
    }
    s16PCMFrame *readDataFrame16() {
      if (isEnd())
        return nullptr;
      auto res = new s16PCMFrame;
      memmove(res, data + offset, sizeof(s16PCMFrame) - sizeof(res->offset));
      res->offset = offset;
      offset += sizeof(s16PCMFrame) - sizeof(int);
      return res;
    }
    void writeDataFrame16(s16PCMFrame *src) {
      std::uint64_t max_size = sizeof(s16PCMFrame) - sizeof(src->offset);
      if (offset > filesize) {
        max_size = max_size - (offset - filesize);
      }
      memmove(data + src->offset, src, max_size);
    }
    u8PCMFrame *readDataFrame8() {
      if (isEnd())
        return nullptr;
      auto res = new u8PCMFrame;
      memmove(res, data + offset, sizeof(u8PCMFrame) - sizeof(res->offset));
      res->offset = offset;
      offset += sizeof(u8PCMFrame) - sizeof(int);
      return res;
    }
    void writeDataFrame8(u8PCMFrame *src) {
      memmove(data + src->offset, src, sizeof(u8PCMFrame) - sizeof(src->offset));
    }
    void writeToFile(const char *filepath) {
      memmove(data + headeroff, &header, sizeof(header));
      memmove(data + formatoff, &format, sizeof(format));
      memmove(data + metadataoff, &metadata, sizeof(metadata) - sizeof(i32));
      int fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY, 0666);
      write(fd, data, filesize);
      close(fd);
    }
    void setFileSize(i64 size) {
      filesize = size;
      header.size = filesize - 8;
      metadata.size = filesize - metadata.dataOffset;
    }
    u8 *getData() {return data;}
    wavReader operator+(const wavReader &rhs) {
      wavReader res;
      if (format.byteRate == rhs.format.byteRate && format.sampleRate == rhs.format.sampleRate &&
          format.channelNum == rhs.format.channelNum) {
        res.header = header;
        res.headeroff = headeroff;
        res.format = format;
        res.formatoff = formatoff;
        res.metadataoff = metadataoff;
        res.metadata = metadata;
        res.offset = 0;
        res.data = new u8[filesize + rhs.metadata.size];
        memmove(res.data, data, filesize);
        memmove(res.data + filesize, rhs.data + rhs.metadata.dataOffset, rhs.metadata.size);
        res.filesize = filesize + rhs.metadata.size;
        res.header.size = res.filesize - 8;
        res.metadata.size = res.filesize - metadata.dataOffset;
      }
      return res;
    }
  };
  
  double getSin(double off, int cycle);
  double getCos(double off, int cycle);
  void wavPCMs16FrameTransform(s16PCMFrame *frame, int arg);
}

#endif //AUDIO_WAV_HPP
