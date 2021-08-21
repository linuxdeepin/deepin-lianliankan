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
#include "gamebutton.h"

#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>
#include <QMouseEvent>
#include <QtMath>

GameButton::GameButton(const QPixmap &pic, const QString &text, QWidget *parent)
    : QAbstractButton(parent)
    , m_pic(pic)
    , m_text(text)
    , m_btnType(TextOnPic)
{
}

GameButton::GameButton(const QPixmap &pic, const QPixmap &icon, QWidget *parent)
    : QAbstractButton(parent)
    , m_pic(pic)
    , m_icon(icon)
    , m_btnType(IconOnPic)
{
}

GameButton::GameButton(const QPixmap &pic, QWidget *parent)
    : QAbstractButton(parent)
    , m_pic(pic)
    , m_btnType(OnlyPic)
{
}

void GameButton::setFont(const QFont &font)
{
    m_font=font;
}

void GameButton::setLocation(int x, int y)
{
    m_rowIndex = x;
    m_columnIndex = y;
}

void GameButton::updatePic(const QPixmap &pic)
{
    //更新图标类型
    setBtnMode(OnlyPic);
    //更新按下状态
    m_pressd = false;
    //更新图片资源
    m_pic = pic;
    update();
}

void GameButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    //消失的情况下直接返回不绘制,消失.
    if (m_btnType == NoneType)
        return;
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(rect(),m_pic);
    switch (m_btnType) {
    case TextOnPic: {
        //绘制文字按钮
        QFontMetricsF mertic(m_font);
        qreal fontHeight = mertic.height();
        qreal fontWidth = mertic.width(m_text);
        p.setFont(m_font);
        p.setPen(QColor("#FFFFFF"));
        qreal textX = (rect().width() - fontWidth) / 2;
        qreal textY = (rect().height() - fontHeight - fontHeight / 2) / 2;
        p.drawText(QRectF(textX, textY, fontWidth, fontHeight), m_text);
        break;
    }
    case IconOnPic: {
        break;
    }
    default: {
        //绘制游戏动物按钮
        //点击状态
        if (m_pressd) {
            drawRect(p);
        }

        break;
    }
    }
    //    if (m_text != " ") {
    //    } else {
    //        if (m_pressd) {
    //        }
    //    }
}

void GameButton::mousePressEvent(QMouseEvent *e)
{
    //qInfo()<<"mouseEvent";
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }

    if (hitButton(e->pos())) {
        m_pressd = true;
        e->accept();
    } else {
        m_pressd = false;
        e->ignore();
    }

    return QAbstractButton::mousePressEvent(e);
}

void GameButton::setBtnMode(const GameBtnType &type)
{
    m_btnType = type;
    update();
}

void GameButton::setPressed(bool isPressd)
{
    m_pressd = isPressd;
    update();
}

void GameButton::drawRect(QPainter &p)
{
    qreal rectX = rect().x();
    qreal rectY = rect().y();
    qreal rectWidth = rect().width();
    qreal rectHeight = rect().height();
    QColor color(Qt::yellow);
    for (int i = 0; i < 10; i++) {
        color.setAlpha(static_cast<int>(120 - qSqrt(i) * 40));
        p.setPen(color);
        // 圆角阴影边框;
        p.drawRoundedRect(QRectF(rectX, rectY + i * 1, rectWidth, rectHeight - i * 1 - i * 1), 11, 11);
    }
}
