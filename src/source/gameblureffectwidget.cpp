// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
    qDebug() << "Enter GameBlurEffectWidget constructor, size:" << size;
    QSize scaledSize;
    QString fileName;

    switch (m_sizeFlag) {
    case Big:
        scaledSize = QSize(835, 542);
        fileName = ":/assets/images/bigRect.png";
        qDebug() << "Selected big size:" << scaledSize << "with file:" << fileName;
        break;
    case Mid:
        scaledSize = QSize(480, 515);
        fileName = ":/assets/images/midRect.png";
        qDebug() << "Selected mid size:" << scaledSize << "with file:" << fileName;
        break;
    default:
        scaledSize = QSize(175, 542);
        fileName = ":/assets/images/smallRect.png";
        qDebug() << "Selected small size:" << scaledSize << "with file:" << fileName;
        break;
    }
    m_pic = Utils::getDpiPixmap(scaledSize, fileName, this);
    qDebug() << "Exit GameBlurEffectWidget constructor";
}

void GameBlurEffectWidget::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.drawPixmap(rect(), m_pic);
}
