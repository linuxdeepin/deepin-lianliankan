/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     linxun <linxun@uniontech.com>
*
* Maintainer: linxun <linxun@uniontech.com>
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
#include "gamelinescene.h"
#include "gamecontrol.h"

#include <QDebug>
#include <QPainter>

GameLineScene::GameLineScene(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void GameLineScene::setDrawPath(const QList<QPointF> &posList)
{
    m_posList = posList;
    update();
}

void GameLineScene::setMissing()
{
    m_posList.clear();
    update();
}

void GameLineScene::paintEvent(QPaintEvent *event)
{
    if (m_posList.count() < 4) {
        return QWidget::paintEvent(event);
    } else {
        QPainter painter(this);
        //反走样
        painter.setRenderHint(QPainter::Antialiasing, true);
        //获取爆炸图片
        const QPixmap &pic = GameControl::m_picMap.value(qMakePair(ExplodePic, Default));
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor("#FFFFFF"));
        painter.setPen(pen);
        QPainterPath path;
        int posCount = m_posList.count();
        for (int i = 0; i < posCount; i++) {
            qreal posX = m_posList.at(i).x();
            qreal posY = m_posList.at(i).y();
            //第一个pos和最后一个pos绘制爆炸效果
            if (i == 0 || i == posCount - 1) {
                painter.drawPixmap(QPointF(posX - pic.width() / 2, posY - pic.height() / 2), pic);
                continue;
            } else if (i == 1) {
                //第二个pos是连线的起点
                path.moveTo(QPointF(posX, posY));
            } else if (i == posCount - 2) {
                //倒数第二pos是连线的终点,进行路径的绘制
                path.lineTo(QPointF(posX, posY));
                painter.drawPath(path);
            } else {
                //其他的转向点正常加入path
                path.lineTo(QPointF(posX, posY));
            }
        }
    }
}
