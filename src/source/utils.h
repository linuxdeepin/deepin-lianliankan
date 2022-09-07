// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef UTIL_H
#define UTIL_H
#include "global.h"

#include <DWidget>

#include <QObject>
#include <QPixmap>

DWIDGET_USE_NAMESPACE

class Utils
{
public:
    static QPixmap getDpiPixmap(QSize size, const QString &filename, DWidget *w);
};

#endif // UTIL_H
