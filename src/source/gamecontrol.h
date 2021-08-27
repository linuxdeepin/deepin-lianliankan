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
#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "gamebutton.h"
#include "utils.h"

#include <QObject>
#include <QMap>
#include <QImageReader>
#include <QFont>
#include <QDebug>
#include <QMap>

class GameControl : public QObject
{
    Q_OBJECT
public:
    static GameControl& GameInterFace(){
        static GameControl control;
        return  control;
    }

    static void loadPic(const GameBtnFlag &flag, const GameBtnSize &btnSize, DWidget *widget)
    {
        QString fileName;
        QSize scaledSize;

        switch (btnSize) {
        case Big:
            scaledSize=QSize(250,135);
            break;
        case Mid:
            scaledSize=QSize(200,115);
            break;
        case Small:
            scaledSize=QSize(140,80);
            break;
        default:
            scaledSize=QSize(50,50);
        }

        switch (flag) {
        case ButtonNormal:
            fileName = ":/assets/images/normal.svg";
            break;
        case ButtonCow:
            fileName = ":/assets/images/cow.png";
            break;
        case ButtonTiger:
            fileName = ":/assets/images/tiger.png";
            break;
        case ButtonRabbit:
            fileName = ":/assets/images/rabbit.png";
            break;
        case ButtonSnake:
            fileName = ":/assets/images/snake.png";
            break;
        case ButtonHorse:
            fileName = ":/assets/images/horse.png";
            break;
        case ButtonSheep:
            fileName = ":/assets/images/sheep.png";
            break;
        case ButtonDog:
            fileName = ":/assets/images/dog.png";
            break;
        case ButtonPig:
            fileName = ":/assets/images/pig.png";
            break;
        case ButtonCat:
            fileName = ":/assets/images/cat.png";
            break;
        case ButtonLion:
            fileName = ":/assets/images/lion.png";
            break;
        case ButtonFox:
            fileName = ":/assets/images/fox.png";
            break;
        case ButtonPanda:
            fileName = ":/assets/images/panda.png";
            break;
        case BigRect:
            scaledSize = QSize(835, 542);
            fileName = ":/assets/images/bigRect.png";
            break;
        case MidRect:
            scaledSize = QSize(480, 515);
            fileName = ":/assets/images/midRect.png";
            break;
        case SmallRect:
            scaledSize = QSize(175, 542);
            fileName = ":/assets/images/smallRect.png";
            break;
        case MainBack:
            scaledSize = QSize(1024, 768);
            fileName = ":/assets/images/background.png";
            break;
        default:
            fileName = ":/assets/images/progressback.png";
            break;
        }
        QPixmap pic = Utils::getDpiPixmap(scaledSize, fileName, widget);
        m_picMap.insert(qMakePair(flag, btnSize), pic);
    }
    void gameBegin(); //游戏开始
    void gameReset();//游戏重置
    QPair<bool, QList<QPoint>> gameJudge(); //游戏判断
    bool gameSearch(const QPoint &startPos, const QPoint &endPos); //寻路
    bool gameJudgeVictory(); //判断是否胜利
    static GameBtnFlag m_map[12][18];//游戏地图
    static int m_minTurn[12][18]; //记录最小转弯数
    static QPoint m_pathMap[12][18]; //通路坐标
    static QHash<QPair<GameBtnFlag, GameBtnSize>, QPixmap>m_picMap;//图片资源
signals:

public slots:

private:
    explicit GameControl(QObject *parent = nullptr);
    void gameShuffle(bool inital); //游戏洗牌
    bool gameBfs(const QPoint &startPos, const QPoint &endPos); //游戏寻路
};

class BtnFactory{
public:
    static GameButton * createBtn(const GameBtnFlag &flag,const GameBtnSize &btnSize ,const GameIconType &iconType,const QString &text=" ",QWidget *parent=nullptr){
        QFont btnFont;
        btnFont.setFamily("Noto Sans CJK SC");
        btnFont.setWeight(QFont::DemiBold);

        QSize size;
        GameButton *btn=nullptr;
        QPixmap *btnIcon=nullptr;

        switch (iconType) {
           case Sound:
            break;
           case Begin:
            break;
           case Reset:
            break;
           case Hint:
            break;
           case Home:
            break;
           default:
            break;
        }

        switch (btnSize) {
        case Big:
            btnFont.setPointSize(20);
            size=QSize(250,135);
            break;
        case Mid:
            btnFont.setPointSize(16);
            size=QSize(200,115);
            break;
        case Small:
            size=QSize(140,80);
            break;
        default:
            size=QSize(50,50);
        }

        if(flag==ButtonNormal){
            if(!btnIcon){
                btn=new GameButton(GameControl::m_picMap.value(qMakePair(flag,btnSize)) ,text,parent);
            }else {
                btn=new GameButton(GameControl::m_picMap.value(qMakePair(flag,btnSize)),*btnIcon,parent);
            }
        }else {
            btn=new GameButton (GameControl::m_picMap.value(qMakePair(flag,btnSize)),parent);
        }

        btn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        btn->setFixedSize(size);
        btn->setFont(btnFont);
        return  btn;
    }
};

#endif // GAMECONTROL_H
