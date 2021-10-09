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

class UT_Utils : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        qInfo() << "TearDown" << endl;
    }
};

TEST_F(UT_Utils, UT_Utils_getDpiPixmap_001)
{
    Stub stub;
    stub.set(ADDR(QGuiApplication, devicePixelRatio), UT_Utils_DevicePixelRatioF);
    stub.set(ADDR(QImageReader, canRead), UT_Utils_CanRead);
    Utils::getDpiPixmap(QSize(0, 0), "test", nullptr);
    Utils::getDpiPixmap(QSize(50, 50), "test", nullptr);
}
