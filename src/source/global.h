#ifndef GLOBAL_H
#define GLOBAL_H

#define GAMEROW 10
#define GAMECOLUMN 16

#define ICONWIDTH 50
#define ICONHEIGHT 50

//主界面/游戏界面背景圆角
#define FRAMERADIUS 18

//游戏所有按钮类型
enum GameBtnFlag{
    ButtonNormal=0,
    blank,
    cow,
    tiger,
    rabbit,
    snake,
    horse,
    sheep,
    dog,
    pig,
    cat,
    lion,
    fox,
    panda
};

//游戏所有按钮类型大小
enum GameBtnSize{
    Default=0,
    Big,
    Mid,
    Small
};

//游戏图标类型
enum GameIconType{
    None=0,
    Sound,
    Begin,
    Reset,
    Hint,
    Home
};
#endif // GLOBAL_H
