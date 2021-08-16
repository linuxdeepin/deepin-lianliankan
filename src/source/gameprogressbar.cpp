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
#include "gameprogressbar.h"

#include <QStylePainter>
#include <QStyleOptionProgressBar>

GameProgressBar::GameProgressBar(QWidget *parent)
    : DColoredProgressBar(parent)
{
}

void GameProgressBar::paintEvent(QPaintEvent *e)
{
    //    QStylePainter painter(this);
    //    QStyleOptionProgressBar styopt;
    //    initStyleOption(&styopt);

    //    int rectX=rect().x();
    //    int rectY=rect().y();
    //    int arcX=rectX+15;
    //    int rectWidth=rect().width();
    //    int rectHeight=rect().height();
    //    QPainterPath path;
    //    painter.setRenderHint(QPainter::Antialiasing);
    //    painter.setPen(QColor("#FFFFFF"));
    //    path.setFillRule(Qt::WindingFill);
    //    path.moveTo(rectX+15,rectY);
    //    path.lineTo(rectX+rectWidth-15,rectY);
    //    path.arcTo(QRect(rectX+rectWidth-30,rectY,30,rectHeight),90,-180);
    //    path.lineTo(rectX+15,rectY+rectHeight);
    //    path.arcTo(QRect(rectX+30,rectY+rectHeight,-30,-rectHeight),90,-180);
    //    QLinearGradient linearGradient(QPointF(rectX, rectY),QPointF(rectX+rectWidth, rectY+rectHeight)); //线性渐变
    //    linearGradient.setColorAt(0.03, QColor("#f66610"));//插入颜色
    //    linearGradient.setColorAt(0.33, QColor("#ffc24a"));
    //    linearGradient.setColorAt(0.65,QColor("#f7aa62"));
    //    linearGradient.setColorAt(0.98,QColor("#ffd273"));
    //    linearGradient.setSpread(QGradient::RepeatSpread);//指定渐变区域以外的区域的扩散方式
    //    painter.setBrush(linearGradient);//使用线性渐变作为画刷
    //    painter.drawPath(path);
}

void GameProgressBar::initStyleOption(QStyleOptionProgressBar *option) const
{
    DColoredProgressBar::initStyleOption(option);
}
