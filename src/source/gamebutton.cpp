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
#include "gamebutton.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QSizePolicy>

#include <DLabel>


GameButton::GameButton(const QPixmap &pic, const QString &text, QWidget *parent):QAbstractButton(parent),m_pic(pic),m_text(text)
{
    initUI();

}

GameButton::GameButton(const QPixmap &pic, const QPixmap &icon, QWidget *parent):QAbstractButton(parent),m_pic(pic),m_icon(icon)
{
    initUI();
}

GameButton::GameButton(const QPixmap &pic, QWidget *parent):QAbstractButton(parent),m_pic(pic)
{
    initUI();
}

void GameButton::setFont(const QFont &font)
{
    m_font=font;
}

void GameButton::initUI()
{
    DLabel *textLabel=new DLabel (m_text,this);
    QFont font;
    QHBoxLayout *mainLayout=new QHBoxLayout ();
    mainLayout->setContentsMargins(0,0,0,20);
    mainLayout->addWidget(textLabel);
    mainLayout->setAlignment(Qt::AlignHCenter);
    this->setLayout(mainLayout);
}

void GameButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(rect(),m_pic);
    if(m_text!=" "){

    }
}
