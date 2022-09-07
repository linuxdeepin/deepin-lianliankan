// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
        if (m_progress) {
            delete m_progress;
            m_progress = nullptr;
        }
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
