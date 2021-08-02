#include "gamebutton.h"

#include <QPainter>

const static int iconHeight=50;
const static int iconWidth=50;

GameButton::GameButton(GameBtnFlag flag,QWidget *parent) : DPushButton(parent),m_flag(flag)
{


}

void GameButton::paintEvent(QPaintEvent *e)
{


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect pixRect(0,0,ICONWIDTH,ICONHEIGHT);
    QPixmap pix;
    switch (m_flag) {

    case cow:{
        pix.load(":/images/cow.png");
        break;
    }
    case tiger:{
        pix.load(":/images/cow.png");
        break;
    }
    case sheep:{
        pix.load(":/images/sheep.png");
        break;
    }
    case snake:{
        pix.load(":/images/snake.png");
        break;
    }
    case horse:{
        pix.load(":/images/horse.png");
        break;
    }
    default:{
        pix.load(":/images/horse.png");
        break;
    }
    }

    painter.drawPixmap(rect(),pix);

}

