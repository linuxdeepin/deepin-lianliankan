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
        delete m_widget;
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
