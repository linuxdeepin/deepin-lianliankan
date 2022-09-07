// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
        painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
        //获取爆炸图片
        const QPixmap &pic = GameControl::m_picMap.value(qMakePair(ExplodePic, Default));
        QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor("#FFFFFF"));
        painter.setPen(pen);
        painter.save();
        QPainterPath path;
        int posCount = m_posList.count();
        for (int i = 0; i < posCount; i++) {
            qreal posX = m_posList.at(i).x();
            qreal posY = m_posList.at(i).y();
            //第一个pos和最后一个pos绘制爆炸效果
            if (i == 0 || i == posCount - 1) {
                painter.drawPixmap(QRect(static_cast<int>(posX - pic.width() / 2), static_cast<int>(posY - pic.height() / 2), pic.width(), pic.height()), pic);
                continue;
            } else if (i == 1) {
                //第二个pos是连线的起点
                path.moveTo(QPointF(posX, posY));
            } else if (i == posCount - 2) {
                drawLightEffeec(painter, path, QPointF(posX, posY));
            } else {
                //其他的转向点正常加入path
                path.lineTo(QPointF(posX, posY));
            }
        }
    }
}

void GameLineScene::drawLightEffeec(QPainter &p, QPainterPath &path, const QPointF &pos)
{
    //倒数第二pos是连线的终点,进行路径的绘制
    path.lineTo(pos);
    //绘制最后一层连线光效阴影
    p.setOpacity(0.1);
    //设置画笔宽度
    QPen pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(6);
    p.setPen(pen);
    p.drawPath(path);
    //绘制第三层连线光效阴影
    p.setOpacity(0.2);
    //设置画笔宽度
    pen.setWidth(4);
    p.setPen(pen);
    p.drawPath(path);
    //绘制第二层连线光效阴影
    p.setOpacity(0.4);
    //设置画笔宽度
    pen.setWidth(2);
    p.setPen(pen);
    p.drawPath(path);
    p.restore();
    p.setOpacity(0.6);
    p.drawPath(path);
}
