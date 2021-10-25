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

#include <gameoverblureffectwidget.h>

#include <QDebug>
#include <QPaintEvent>

class UT_GameoverBlurEffectWidget : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_overWidget = new GameoverBlurEffectWidget;
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_overWidget) {
            delete m_overWidget;
            m_overWidget = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
    GameoverBlurEffectWidget *m_overWidget;
};

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_initUI)
{
    m_overWidget->initUI();
    EXPECT_NE(m_overWidget->m_tipLabel, nullptr) << "check the status after UT_GameoverBlurEffectWidget_initUI()";
    EXPECT_EQ(m_overWidget->m_OverBtnGroup->buttons().count(), 2) << "check the status after UT_GameoverBlurEffectWidget_initUI()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_initConnect)
{
    m_overWidget->initConnect();
    EXPECT_NE(m_overWidget, nullptr) << "check the status after UT_GameoverBlurEffectWidget_initConnect()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_updateLabel)
{
    m_overWidget->updateLabel("test");
    EXPECT_EQ(m_overWidget->m_tipLabel->text(), "test") << "check the status after UT_GameoverBlurEffectWidget_updateLabel()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_setResult)
{
    m_overWidget->setResult(true);
    EXPECT_EQ(m_overWidget->m_tipLabel->m_result, true) << "check the status after UT_GameoverBlurEffectWidget_setResult()";
    EXPECT_EQ(m_overWidget->m_overType, true) << "check the status after UT_GameoverBlurEffectWidget_setResult()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_onButtonPressed)
{
    m_overWidget->onButtonPressed(0);
    m_overWidget->onButtonPressed(-1);
    EXPECT_NE(m_overWidget, nullptr) << "check the status after UT_GameoverBlurEffectWidget_onButtonPressed()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_paintEvent)
{
    QPaintEvent e(m_overWidget->rect());
    m_overWidget->setResult(true);
    m_overWidget->paintEvent(&e);
    m_overWidget->setResult(false);
    m_overWidget->paintEvent(&e);
    EXPECT_NE(m_overWidget, nullptr) << "check the status after UT_GameoverBlurEffectWidget_paintEvent()";
}

TEST_F(UT_GameoverBlurEffectWidget, UT_GameoverBlurEffectWidget_mouseMoveEvent)
{
    QMouseEvent e(QEvent::Move, QPoint(m_overWidget->x(), m_overWidget->y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_overWidget->mouseMoveEvent(&e);
    EXPECT_NE(m_overWidget, nullptr) << "check the status after UT_GameoverBlurEffectWidget_mouseMoveEvent()";
}
