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

#include <gameprogressbar.h>

#include <QDebug>
#include <QPaintEvent>

class UT_GameProgressBar : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_progress = new GameProgressBar;
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        delete m_progress;
        qInfo() << "TearDown" << endl;
    }
    GameProgressBar *m_progress;
};

TEST_F(UT_GameProgressBar, UT_GameProgressBar_setInintalTime)
{
    m_progress->setInintalTime(0);
    EXPECT_EQ(m_progress->m_time, 0) << "check the status after UT_GameProgressBar_setInintalTime()";
    EXPECT_EQ(m_progress->value(), 0) << "check the status after UT_GameProgressBar_setInintalTime()";
}

TEST_F(UT_GameProgressBar, UT_GameProgressBar_paintEvent)
{
    QPaintEvent e(m_progress->rect());
    m_progress->setInintalTime(100);
    m_progress->paintEvent(&e);
    EXPECT_NE(m_progress, nullptr) << "check the status after UT_GameProgressBar_paintEvent()";
}
