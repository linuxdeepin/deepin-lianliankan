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

#include <mainwindow.h>
class UT_MainWindow : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_mainwindow = new MainWindow();
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        delete m_mainwindow;
        qInfo() << "TearDown" << endl;
    }
    MainWindow *m_mainwindow;
};

TEST_F(UT_MainWindow, UT_MainWindow_loadMainpage)
{
    m_mainwindow->loadMainpage();
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after loadMainpage()";
    EXPECT_NE(m_mainwindow->m_mainPage, nullptr) << "check the status after loadMainpage()";
    EXPECT_EQ(m_mainwindow->m_stackedWidget->currentWidget(), m_mainwindow->m_mainPage) << "check the status after loadMainpage()";
}
