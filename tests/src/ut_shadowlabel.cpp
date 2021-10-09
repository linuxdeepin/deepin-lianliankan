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
        delete m_label;
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
