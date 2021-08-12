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

#include <QObject>
#include <QMap>
#include <QImageReader>
#include <QFont>
#include <QDebug>

class BtnFactory{
public:
    static GameButton * createBtn(const GameBtnFlag &flag,const GameBtnSize &btnSize ,const GameIconType &iconType,const QString &text=" ",QWidget *parent=nullptr){
        QFont btnFont;
        btnFont.setFamily("Noto Sans CJK SC");
        btnFont.setWeight(QFont::DemiBold);

        GameButton *btn=nullptr;
        QImageReader imageReader;
        QSize scaledSize;
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

        switch (flag) {
        case ButtonNormal:
            imageReader.setFileName(":/assets/images/normal.svg");
            break;
        case ButtonCow:
            imageReader.setFileName(":/assets/images/cow.png");
            break;
        case ButtonTiger:
            imageReader.setFileName(":/assets/images/tiger.png");
            break;
        case ButtonRabbit:
            imageReader.setFileName(":/assets/images/rabbit.png");
            break;
        case ButtonSnake:
            imageReader.setFileName(":/assets/images/snake.png");
            break;
        case ButtonHorse:
            imageReader.setFileName(":/assets/images/horse.png");
            break;
        case ButtonSheep:
            imageReader.setFileName(":/assets/images/sheep.png");
            break;
        case ButtonDog:
            imageReader.setFileName(":/assets/images/dog.png");
            break;
        case ButtonPig:
            imageReader.setFileName(":/assets/images/pig.png");
            break;
        case ButtonCat:
            imageReader.setFileName(":/assets/images/cat.png");
            break;
        case ButtonLion:
            imageReader.setFileName(":/assets/images/lion.png");
            break;
        case ButtonFox:
            imageReader.setFileName(":/assets/images/fox.png");
            break;
        case ButtonPanda:
            imageReader.setFileName(":/assets/images/panda.png");
            break;
        default:
            break;
        }

        switch (btnSize) {
        case Big:
            btnFont.setPointSize(20);
            scaledSize=QSize(250,135);
            break;
        case Mid:
            btnFont.setPointSize(16);
            scaledSize=QSize(200,115);
            break;
        case Small:
            scaledSize=QSize(140,80);
            break;
        default:
            scaledSize=QSize(50,50);
        }

        imageReader.setScaledSize(scaledSize);
        if(flag==ButtonNormal){
            if(!btnIcon){
                btn=new GameButton(QPixmap::fromImageReader(&imageReader),text,parent);
            }else {
                btn=new GameButton(QPixmap::fromImageReader(&imageReader),*btnIcon,parent);
            }
        }else {
            btn=new GameButton (QPixmap::fromImageReader(&imageReader),parent);
        }

        btn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        btn->setFixedSize(scaledSize);
        btn->setFont(btnFont);
        return  btn;
    }
};


class GameControl : public QObject
{
    Q_OBJECT
public:
    static GameControl& GameInterFace(){
        static GameControl control;
        return  control;
    }

    void gameBegin(); //游戏开始
    void gameReset();//游戏重置
    static GameBtnFlag m_map[12][18];
signals:

public slots:

private:
    explicit GameControl(QObject *parent = nullptr);
    void gameShuffle(bool inital);
};

#endif // GAMECONTROL_H
