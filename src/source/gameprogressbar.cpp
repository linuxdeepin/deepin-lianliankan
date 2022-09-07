// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gameprogressbar.h"
#include "gamecontrol.h"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

GameProgressBar::GameProgressBar(QWidget *parent)
    : DColoredProgressBar(parent)
{
    QSize scaledSize = QSize(816, 54);
    QString fileName = ":/assets/images/progressback.png";
    m_pic = Utils::getDpiPixmap(scaledSize, fileName, this);
}

void GameProgressBar::setInintalTime(int time)
{
    m_time = time;
    setRange(0, 0);
    setValue(time);
}

void GameProgressBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(rect(), m_pic);

    //根据背景图片位置调整绘制动态效果位置
    qreal rectX = rect().x() + 7;
    qreal rectY = rect().y() + 1;
    qreal rectWidth = rect().width() - 14;
    qreal rectHeight = (rect().height() - 14);
    qreal value = this->value();
    qreal proportion = value / m_time;

    //设置渐变填充颜色
    QLinearGradient linearGradient(QPointF(rectX, rectY), QPointF(rectX + rectWidth, rectY + rectHeight)); //线性渐变
    linearGradient.setColorAt(0.03, QColor(255, 58, 0, 255)); //插入颜色
    linearGradient.setColorAt(0.33, QColor(238, 89, 26, 255));
    linearGradient.setColorAt(0.65, QColor(255, 173, 0, 255));
    linearGradient.setColorAt(0.98, QColor(255, 210, 115, 255));
    linearGradient.setSpread(QGradient::ReflectSpread); //指定渐变区域以外的区域的扩散方式

    //覆盖一层垂直线性渐变色，创造立体效果
    QLinearGradient shadowLg(QPointF(rectX, rectY), QPointF(rectX, (rectY+rectHeight)*0.6));
    shadowLg.setColorAt(0.04, QColor(235, 255, 209));
    shadowLg.setColorAt(0.2, QColor("#F1EB6E"));
    shadowLg.setColorAt(0.61, QColor("#DE8A4C"));
    shadowLg.setColorAt(0.9, QColor("#D56B39"));
    shadowLg.setSpread(QGradient::ReflectSpread);

    //  绘制动态填充状态,若为开始,使用线性渐变作为画刷填满整个路径,若是0,忽略此段绘制
    if (proportion != 0.000) {
        QPainterPath fillPath;
        fillPath.moveTo(rectX + rectHeight / 2, rectY);
        fillPath.lineTo(rectX + rectHeight / 2 + (rectWidth - rectHeight) * proportion, rectY);
        fillPath.arcTo(QRectF(rectX + (rectWidth - rectHeight) * proportion, rectY, rectHeight, rectHeight), 90, -180);
        fillPath.lineTo(rectX + rectHeight / 2, rectY + rectHeight);
        fillPath.arcTo(QRectF(rectX + rectHeight, rectY + rectHeight, -rectHeight, -rectHeight), 90, -180);
        painter.fillPath(fillPath, linearGradient);
        painter.setOpacity(0.5);
        painter.fillPath(fillPath, shadowLg);
    }

    // 绘制倒计时
    painter.setOpacity(1);
    QFont textFont;

    //阴影字体
    QFont BackFont;
    const QString &text = QString::number(value) + "s";
    textFont.setFamily("Noto Sans CJK SC");
    textFont.setWeight(QFont::DemiBold);
    textFont.setPointSize(15);
    BackFont.setFamily("Noto Sans CJK SC");
    BackFont.setWeight(QFont::DemiBold);
    BackFont.setPointSize(15);
    QFontMetricsF mertic(textFont);
    qreal merticWidth = mertic.width(text);
    qreal merticHeight = mertic.height();

    //绘制字体阴影效果
    QColor shadowColor(0, 0, 0);
    shadowColor.setAlphaF(0.50);
    painter.setPen(shadowColor);
    painter.setFont(BackFont);
    //Y轴阴影向下偏移2px
    painter.drawText(QRectF(rectWidth / 2 - merticWidth / 2, rectHeight / 2 - merticHeight / 2 + 2, merticWidth, merticHeight), text);

    //绘制字体
    painter.setPen(QColor("#FFFFFF"));
    painter.setFont(textFont);
    painter.drawText(QRectF(rectWidth / 2 - merticWidth / 2, rectHeight / 2 - merticHeight / 2, merticWidth, merticHeight), text);
}
