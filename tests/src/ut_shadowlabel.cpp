// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <shadowlabel.h>

#include <QDebug>
#include <QPaintEvent>

class UT_ShadowLabel : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_label = new ShadowLabel;
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_label) {
            delete m_label;
            m_label = nullptr;
        }

        qInfo() << "TearDown" << endl;
    }
    ShadowLabel *m_label;
};

TEST_F(UT_ShadowLabel, UT_ShadowLabel_setResult)
{
    m_label->setResult(true);
    EXPECT_EQ(m_label->m_result, true) << "check the status after UT_ShadowLabel_setResult()";
}

TEST_F(UT_ShadowLabel, UT_ShadowLabel_paintEvent)
{
    QPaintEvent e(m_label->rect());
    m_label->setResult(true);
    m_label->paintEvent(&e);
    m_label->setResult(false);
    m_label->paintEvent(&e);
    EXPECT_NE(m_label, nullptr) << "check the status after UT_ShadowLabel_paintEvent()";
}
