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

GameButton::GameButton(const QPixmap &pic, const QString &text, QWidget *parent):QAbstractButton(parent),m_pic(pic),m_text(text)
{

}

GameButton::GameButton(const QPixmap &pic, const QPixmap &icon, QWidget *parent):QAbstractButton(parent),m_pic(pic),m_icon(icon)
{
}

GameButton::GameButton(const QPixmap &pic, QWidget *parent):QAbstractButton(parent),m_pic(pic)
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

void GameButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(rect(),m_pic);
    if(m_text!=" "){
        QFontMetricsF mertic(m_font);
        qreal fontHeight = mertic.height();
        qreal fontWidth = mertic.width(m_text);
        p.setFont(m_font);
        p.setPen(QColor("#FFFFFF"));
        qreal textX = (rect().width() - fontWidth) / 2;
        qreal textY = (rect().height() - fontHeight - fontHeight / 2) / 2;
        p.drawText(QRectF(textX, textY, fontWidth, fontHeight), m_text);
    }
}

void GameButton::mousePressEvent(QMouseEvent *e)
{
    qInfo() << e->pos();
    return QAbstractButton::mousePressEvent(e);
}
