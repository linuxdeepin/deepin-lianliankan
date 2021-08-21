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
#include <QDebug>

GameProgressBar::GameProgressBar(QWidget *parent)
    : DColoredProgressBar(parent)
{
}

void GameProgressBar::setInintalTime(int time)
{
    m_time = time;
    setRange(0, time);
    setValue(time);
}

void GameProgressBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    qreal rectX = rect().x();
    qreal rectY = rect().y();
    qreal rectWidth = rect().width();
    qreal rectHeight = rect().height();
    qreal value = this->value();
    qreal proportion = value / m_time;

    //设置渐变填充颜色
    QLinearGradient linearGradient(QPointF(rectX, rectY), QPointF(rectX + rectWidth, rectY + rectHeight)); //线性渐变
    linearGradient.setColorAt(0.2, QColor("#F66610")); //插入颜色
    linearGradient.setColorAt(0.33, QColor("#F7AA62"));
    linearGradient.setColorAt(0.65, QColor("#FFC24A"));
    linearGradient.setColorAt(0.98, QColor("#FFD273"));
    linearGradient.setSpread(QGradient::RepeatSpread); //指定渐变区域以外的区域的扩散方式

    //进度条外框,固定的路径
    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor("#FFFFFF"));
    path.setFillRule(Qt::WindingFill);
    path.moveTo(rectX + rectHeight / 2, rectY);
    path.lineTo(rectX + rectWidth - rectHeight / 2, rectY);
    path.arcTo(QRectF(rectX + rectWidth - rectHeight, rectY, rectHeight, rectHeight), 90, -180);
    path.lineTo(rectX + rectHeight / 2, rectY + rectHeight);
    path.arcTo(QRectF(rectX + rectHeight, rectY + rectHeight, -rectHeight, -rectHeight), 90, -180);
    painter.drawPath(path);

    //绘制动态填充状态,若为开始,使用线性渐变作为画刷填满整个路径,若是0,忽略此段绘制
    if (proportion != 0.000) {
        QPainterPath fillPath;
        fillPath.moveTo(rectX + rectHeight / 2, rectY);
        fillPath.lineTo(rectX + rectHeight / 2 + (rectWidth - rectHeight) * proportion, rectY);
        fillPath.arcTo(QRectF(rectX + (rectWidth - rectHeight) * proportion, rectY, rectHeight, rectHeight), 90, -180);
        fillPath.lineTo(rectX + rectHeight / 2, rectY + rectHeight);
        fillPath.arcTo(QRectF(rectX + rectHeight, rectY + rectHeight, -rectHeight, -rectHeight), 90, -180);
        painter.fillPath(fillPath, linearGradient);
    }

    //绘制倒计时
    QFont textFont;
    const QString &text = QString::number(value) + "s";
    textFont.setFamily("Noto Sans CJK SC");
    textFont.setWeight(QFont::DemiBold);
    textFont.setPointSize(16);
    QFontMetricsF mertic(textFont);
    qreal merticWidth = mertic.width(text);
    qreal merticHeight = mertic.height();
    painter.setFont(textFont);
    painter.drawText(QRectF(rectWidth / 2 - merticWidth / 2, rectHeight / 2 - merticHeight / 2, merticWidth, merticHeight), text);

    //阴影

    //        path.moveTo()
    //        painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));
    //          QColor color(50,50,50,10);
    //          for (int i = 0; i < SHADOW_WIDTH; i++)
    //          {
    //              color.setAlpha(120 - qSqrt(i) * 40);
    //              painter.setPen(color);
    //              // 方角阴影边框;
    //                painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
    //              // 圆角阴影边框;
    //              painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
}
