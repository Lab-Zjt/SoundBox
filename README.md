# SoundBox

用于改变音效的小工具。

## Requirement

需要安装ffmpeg,cmake,g++。

## Compile

```
git clone https://github.com/Lab-Zjt/SoundBox.git
cd SoundBox
mkdir build
cd build
cmake ..
make
```

## Usage

`./soundbox`

进入CLI界面。目前可选的有

```
1. Sound Effects Transform //改变音效，目前有7种音效可选择
2. Cut //剪切
3. Merge //合并两首音乐
4. Depart //分离左右声道
5. Mix 2 Music Files //混合两首音乐
6. Volume Adjust //调整音量，调整因子仅支持0-1
7. Speed Up //加速，同时升高音调（0-7，7为两倍速，提高八度）
8. Add Background //加上背景音乐
```

### Sound Effects Transform

目前可选的有：

```
1. Sin-Cos //左声道乘上正弦函数，右声道乘上余弦函数，可以体验到歌声从一边耳朵慢慢转移到另一边耳朵的感觉。
2. 8bit-style //8bit风
3. Block Left Sound Track //屏蔽左声道
4. Block Right Sound Track //屏蔽右声道
5. Make Sound More Consecutive //使声音更平滑
6. Switch Left and Right Sound Track //交换左右声道
7. Get Accompany //消除/降低人声
```

选择后依次输入`输入文件`、`输出文件`。

### Cut

按提示依次输入`输入文件`、`输出文件`、`开始时间`、`结束时间`。

如：

```
Input File: example.mp3
Output File: example_cut.mp3
Time of Begin: 17.8
Time of End: 57.3
```

### Merge

按提示依次输入`输入文件1`、`输入文件2`、`输出文件`。

### Depart

按提示依次输入`输入文件`、`输出左声道文件`、`输出右声道文件`。

### Mix 2 Music Files

按提示依次输入`输入文件1`、`输入文件2`、`输出文件`。

### Volume Adjust

按提示依次输入`输入文件`、`输出文件`、`调整因子`。

### Speed Up

按提示依次输入`输入文件`、`输出文件`、`加速因子`。

### Get Accompany

按提示依次输入`输入文件`、`背景音乐文件`、`输出文件`。
