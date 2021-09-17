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
#include "gameblureffectwidget.h"
#include "gamecontrol.h"

#include <QPainter>
#include <QtMath>
#include <QImageReader>
#include <QDebug>

GameBlurEffectWidget::GameBlurEffectWidget(const GameBtnSize &size, QWidget *parent)
    : QWidget(parent)
    , m_sizeFlag(size)
{
    QSize scaledSize;
    QString fileName;

    switch (m_sizeFlag) {
    case Big:
        scaledSize = QSize(835, 542);
        fileName = ":/assets/images/bigRect.png";
        break;
    case Mid:
        scaledSize = QSize(480, 515);
        fileName = ":/assets/images/midRect.png";
        break;
    default:
        scaledSize = QSize(175, 542);
        fileName = ":/assets/images/smallRect.png";
        break;
    }
    m_pic = Utils::getDpiPixmap(scaledSize, fileName, this);
}

void GameBlurEffectWidget::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.drawPixmap(rect(), m_pic);
}
