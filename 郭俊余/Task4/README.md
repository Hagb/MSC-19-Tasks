# 将“送给最好的TA”的音频替换为<https://www.microsoftstudent.club/uploads/cat.mp3>
实在不想分发这个玩意。所以写了个完成该操作的小 Makefile 当作 Task4 来提交了。

生成的文件是 catofyou.apk
## 依赖
- jdk
- [apktool](https://github.com/iBotPeaches/Apktool)
- wget

## 折腾这个过程中遇到的坑
1. 若直接用 jar 命令来覆盖 res/raw/wind.mp3，apk 可以安装，但运行则会报错“停止运行”。
2. 目前（2019年11月5日）Debian stable、testing、unstable 中的 apktool 似乎均有问题，无法正常打包，会报错`W: aapt: brut.common.BrutException: brut.common.BrutException: Could not extract resource: /prebuilt/linux/aapt_64 (defaulting to $PATH binary) `等。
3. 如果遇到以下报错
```
W: bestofyou/AndroidManifest.xml:1: error: No resource identifier found for attribute 'compileSdkVersion' in package 'android'
W: bestofyou/AndroidManifest.xml:1: error: No resource identifier found for attribute 'compileSdkVersionCodename' in package 'android'
W: bestofyou/AndroidManifest.xml:2: error: No resource identifier found for attribute 'appComponentFactory' in package 'android'
```
可以`rm ~/.local/share/apktool/framework/1.apk`（GNU/Linux 下）再进行 make。该方法来自<https://github.com/iBotPeaches/Apktool/issues/1842#issuecomment-406868946>。
