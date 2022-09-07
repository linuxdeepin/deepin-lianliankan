// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMEPROGRESSBAR_H
#define GAMEPROGRESSBAR_H

#include <DColoredProgressBar>

DWIDGET_USE_NAMESPACE
class GameProgressBar : public DColoredProgressBar
{
    Q_OBJECT
public:
    explicit GameProgressBar(QWidget *parent = nullptr);
    void setInintalTime(int time); //初始化时间
protected:
    void paintEvent(QPaintEvent *e) override;
signals:

public slots:

private:
    qreal m_time = 0;
    QPixmap m_pic;
};

#endif // GAMEPROGRESSBAR_H
