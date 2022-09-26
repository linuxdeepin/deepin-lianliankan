## deepin-lianliankan
Lianliankan is an easy-to-play puzzle game with cute interface and countdown timer.

连连看是一款规则简单容易上手、游戏速度节奏快、画面清晰可爱的益智类小游戏。

#### Core
The GUI is based on [DTK](https://github.com/linuxdeepin/dtkwidget), Qt (Supported >= 5.12).

Build-Depends:
debhelper (>= 11),cmake, pkg-config, qtbase5-dev, qtchooser (>= 55-gc9562a1-1~),qt5-qmake, libdtkwidget-dev, qttools5-dev-tools, libqt5svg5-dev, qttools5-dev,libgtest-dev, libgmock-dev 

#### Installation
sudo apt-get install deepin-lianliankan

#### Build
- mkdir build
- cd build
- cmake ..
- make
- make install
## License

deepin-lianliankan is licensed under [GPL-3.0-or-later](LICENSE).