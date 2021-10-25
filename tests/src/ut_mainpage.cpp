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

#include <mainpage.h>

#include <QDebug>
#include <QMouseEvent>

class UT_MainPage : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        qInfo() << "SetUp" << endl;
        m_mainPage = new MainPage;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_mainPage) {
            delete m_mainPage;
            m_mainPage = nullptr;
        }

        qInfo() << "TearDown" << endl;
    }
    MainPage *m_mainPage;
};

TEST_F(UT_MainPage, UT_MainPage_initUI)
{
    m_mainPage->initUI();
    EXPECT_EQ(m_mainPage->m_btnGrp->buttons().count(), 3) << "check the status after UT_MainPage_initUI()";
    EXPECT_NE(m_mainPage->m_soundBtn, nullptr) << "check the status after UT_MainPage_initUI()";
}

TEST_F(UT_MainPage, UT_MainPage_initConnect)
{
    m_mainPage->initConnect();
    Q_EMIT m_mainPage->buttonPress(1);
    Q_EMIT m_mainPage->soundSwitch();
    EXPECT_EQ(m_mainPage->m_btnGrp->buttons().count(), 3) << "check the status after UT_MainPage_initConnect()";
    EXPECT_NE(m_mainPage->m_soundBtn, nullptr) << "check the status after UT_MainPage_initConnect()";
}

TEST_F(UT_MainPage, UT_MainPage_setSoundState)
{
    m_mainPage->setSoundState(false);
    EXPECT_EQ(m_mainPage->m_soundState, false) << "check the status after UT_MainPage_setSoundState()";
}

TEST_F(UT_MainPage, UT_MainPage_soundState)
{
    m_mainPage->setSoundState(false);
    bool res = m_mainPage->soundState();
    EXPECT_EQ(res, false) << "check the status after UT_MainPage_soundState()";
}

TEST_F(UT_MainPage, UT_MainPage_mouseMoveEvent)
{
    QMouseEvent e(QEvent::Move, QPointF(m_mainPage->x(), m_mainPage->y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_mainPage->mouseMoveEvent(&e);
    EXPECT_NE(m_mainPage, nullptr) << "check the status after UT_MainPage_mouseMoveEvent()";
}
