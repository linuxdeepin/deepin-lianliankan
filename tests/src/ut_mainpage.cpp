// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
