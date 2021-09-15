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
#include "gamecontrol.h"

#include <QDebug>
#include <QPainter>

GameProgressBar::GameProgressBar(QWidget *parent)
    : DColoredProgressBar(parent)
{
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
    //    QImageReader reader;
    //    reader.setFileName(":/assets/images/progressback.png");
    //    reader.setScaledSize(QSize(816,60));
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPixmap pic = GameControl::m_picMap.value(qMakePair(ProgressBack, Default));
    painter.drawPixmap(rect(), pic);
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

    //    // 进度条外框,固定的路径
    //    QPainterPath path;
    //    painter.setPen(QColor("#FFFFFF"));
    //    path.setFillRule(Qt::WindingFill);
    //    path.moveTo(rectX + rectHeight / 2, rectY);
    //    path.lineTo(rectX + rectWidth - rectHeight / 2, rectY);
    //    path.arcTo(QRectF(rectX + rectWidth - rectHeight, rectY, rectHeight, rectHeight), 90, -180);
    //    path.lineTo(rectX + rectHeight / 2, rectY + rectHeight);
    //    path.arcTo(QRectF(rectX + rectHeight, rectY + rectHeight, -rectHeight, -rectHeight), 90, -180);
    //    painter.drawPath(path);
    //    //   painter.drawPixmap(QRect(rect().x(),rect().y(),816,60),QPixmap::fromImageReader(&reader));

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
    painter.drawText(QRectF(rectWidth / 2 - merticWidth / 2, rectHeight / 2 - merticHeight / 2 + 2, merticWidth, merticHeight), text);
    //绘制字体
    painter.setPen(QColor("#FFFFFF"));
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
