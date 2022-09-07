// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GLOBAL_H
#define GLOBAL_H

//游戏行列
#define GAMEROW 10
#define GAMECOLUMN 16

//游戏地图行列
#define GAMEMAPROW 12
#define GAMEMAPCOLUMN 18

//游戏路径上下左右
#define DIR_RIGHT 0
#define DIR_LEFT 1
#define DIR_UP 2
#define DIR_DOWN 3

//游戏难度时间
#define ADVANCED_TIME 160
#define INTER_TIME 320
#define PRIMARY_TIME 480

//窗口大小
#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024

//游戏按钮背景类型||游戏图片类型
enum GameBtnFlag {
    ButtonNormal = -1,
    ButtonBlank,
    ButtonCow,
    ButtonTiger,
    ButtonRabbit,
    ButtonSnake,
    ButtonHorse,
    ButtonSheep,
    ButtonDog,
    ButtonPig,
    ButtonCat,
    ButtonLion,
    ButtonFox,
    ButtonPanda,
    MainBack, //游戏背景图
    ButtonHover,
    ButtonPress,
    ButtonSmall,
    ButtonSHover,
    ButtonSPress,
    checkeffect,//游戏按钮选中效果
    ExplodePic //爆炸效果图
};

//游戏按钮大小类型||图片大小
enum GameBtnSize{
    Default=0,
    Big,
    Mid,
    Over,
    Small
};

//游戏图标类型
enum GameIconType{
    None=0,
    Sound,//音量打开
    Mute,//音量关闭
    Begin,//开始游戏
    Pause,//暂停游戏
    Reset,//重置游戏
    Hint,//提示
    Home//回主菜单
};

//游戏按钮样式类型
enum GameBtnType {
    TextOnPic = 0,//文字按钮
    OnlyPic,//动物图片按钮
    IconOnPic,//图标按钮
    NoneType,//空按钮，不显示
    GameCtl,//开始暂停按钮
    SoundCtl//音量开关按钮
};

//游戏地图结点
struct GameNode {
    int direction; //移动方向
    int rowIndex; //行
    int columnIndex; //列
    int turnNum; //转弯次数
};

//关闭弹窗按钮
enum CloseButtonType {
    IgnoreDialog = 0,
    CloseDialog
};

//点击按钮排列
enum PosType {
    LineType = 0,
    ExplodeType
};

//游戏地图寻路结果
enum GameSearchResult {
    FAIL = 0, //寻找失败
    PositiveSuccess, //正向寻找成功
    ReverseSuccess //反向寻找成功
};

#endif // GLOBAL_H
