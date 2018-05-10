# raspberrylive
A tool which can play videos on Live site by raspberry

一个树莓派用的直播工具
鉴于斗鱼b站等直播网站经常改推流码，每次重写脚本很烦。所以做个小工具

首先必须安装ffmpeg，树莓派坑爹的软件源并没有这个，所以需要自己手动编译
安装ffmpeg和解码器
先安装解码器（注意要一句一句执行……）

sudo git clone git://git.videolan.org/x264
cd x264
sudo ./configure --host=arm-unknown-linux-gnueabi --enable-static --disable-opencl
make
sudo make install
cd ..
rm -rf x264

再安装ffmpeg（一句一句执行……）

sudo git clone git://source.ffmpeg.org/ffmpeg.git
cd ffmpeg
sudo ./configure --arch=armel --target-os=linux --enable-gpl --enable-libx264 --enable-nonfree
make
sudo make install
cd ..
rm -rf ffmpeg


注意事项：树莓派运行qt软件会出各种莫名其妙的bug，比如键盘映射出错，“5”对应“back”，“6” 对应回车

交叉编译实在看的头皮发麻，树莓派下的qtcreator又有各种问题。。。调试起来太麻烦，正在学习ffmpeg，以后再慢慢加功能吧。。下一步话能在视频里加文字...

