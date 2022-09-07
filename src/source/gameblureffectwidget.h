// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMEBLUREFFECTWIDGET_H
#define GAMEBLUREFFECTWIDGET_H

#include "global.h"

#include <DBlurEffectWidget>

DWIDGET_USE_NAMESPACE
class GameBlurEffectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameBlurEffectWidget(const GameBtnSize &size, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event)override;
signals:

public slots:

private:
    GameBtnSize m_sizeFlag;
    QPixmap m_pic;
};

#endif // GAMEBLUREFFECTWIDGET_H
