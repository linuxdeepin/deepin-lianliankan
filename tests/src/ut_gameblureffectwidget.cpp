// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <gameblureffectwidget.h>

#include <QDebug>
#include <QPaintEvent>

class UT_GameBlurEffectWidget : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_widget = new GameBlurEffectWidget(Default);
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_widget) {
            delete m_widget;
            m_widget = nullptr;
        }

        qInfo() << "TearDown" << endl;
    }
    GameBlurEffectWidget *m_widget;
};

TEST_F(UT_GameBlurEffectWidget, UT_GameBlurEffectWidget_Constructor_001)
{
    GameBlurEffectWidget *widget = new GameBlurEffectWidget(Big);
    EXPECT_NE(m_widget, nullptr) << "check the status after UT_GameBlurEffectWidget_Constructor_001()";
    EXPECT_NE(widget, nullptr) << "check the status after UT_GameBlurEffectWidget_Constructor_001()";
    EXPECT_EQ(widget->m_sizeFlag, Big) << "check the status after UT_GameBlurEffectWidget_Constructor_001()";
    widget->deleteLater();
}

TEST_F(UT_GameBlurEffectWidget, UT_GameBlurEffectWidget_Constructor_002)
{
    GameBlurEffectWidget *widget = new GameBlurEffectWidget(Mid);
    EXPECT_NE(m_widget, nullptr) << "check the status after UT_GameBlurEffectWidget_Constructor_002()";
    EXPECT_NE(widget, nullptr) << "check the status after UT_GameBlurEffectWidget_Constructor_002()";
    EXPECT_EQ(widget->m_sizeFlag, Mid) << "check the status after UT_GameBlurEffectWidget_Constructor_002()";
    widget->deleteLater();
}

TEST_F(UT_GameBlurEffectWidget, UT_GameBlurEffectWidget_paintEvent)
{
    QPaintEvent paintEvent(m_widget->rect());
    m_widget->paintEvent(&paintEvent);
    EXPECT_NE(m_widget, nullptr) << "check the status after UT_GameBlurEffectWidget_paintEvent()";
}
