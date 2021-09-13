/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     linxun <linxun@uniontech.com>
*
* Maintainer: zhangdingwen <zhangdingwen@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
    BigRect, //游戏页面左侧矩形框
    MidRect, //主页面矩形框
    SmallRect, //游戏页面右侧矩形框
    MainBack, //游戏背景图
    ProgressBack, //进度条背景
    VictoryPic, //胜利背景图
    FailedPic, //失败背景图
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
enum CloseButtonType{
    ignore = 0,
    close
};

//点击按钮排列
enum PosType {
    LineType = 0,
    ExplodeType
};

#endif // GLOBAL_H
