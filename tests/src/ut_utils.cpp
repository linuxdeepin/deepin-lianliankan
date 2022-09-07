// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <utils.h>

#include <QDebug>
#include <QImageReader>
#include <QGuiApplication>

bool UT_Utils_CanRead()
{
    return true;
}

qreal UT_Utils_DevicePixelRatioF()
{
    return 2.0;
}

TEST(UT_Utils, UT_Utils_getDpiPixmap_001)
{
    Stub stub;
    stub.set(ADDR(QGuiApplication, devicePixelRatio), UT_Utils_DevicePixelRatioF);
    stub.set(ADDR(QImageReader, canRead), UT_Utils_CanRead);
    Utils::getDpiPixmap(QSize(0, 0), "test", nullptr);
    Utils::getDpiPixmap(QSize(50, 50), "test", nullptr);
}
