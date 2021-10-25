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

#include <closewindowdialog.h>

#include <QMessageBox>

class UT_CloseWindowDialog : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_dialog = new CloseWindowDialog();
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_dialog) {
            delete m_dialog;
            m_dialog = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
    CloseWindowDialog *m_dialog;
};

TEST_F(UT_CloseWindowDialog, UT_CloseWindowDialog_initUI)
{
    m_dialog->initUI();
    EXPECT_NE(m_dialog->m_detailLabel, nullptr) << "check the status after UT_CloseWindowDialog_initUI()";
    EXPECT_EQ(m_dialog->m_detailLabel->text(), "Are you sure you want to exit the game?") << "check the status after UT_CloseWindowDialog_initUI()";
}

TEST_F(UT_CloseWindowDialog, UT_CloseWindowDialog_onButtonClicked)
{
    m_dialog->onButtonClicked(CloseButtonType::CloseDialog, "test");
    EXPECT_EQ(m_dialog->m_result, QMessageBox::Ok) << "check the status after UT_CloseWindowDialog_onButtonClicked()";
    m_dialog->onButtonClicked(CloseButtonType::IgnoreDialog, "test");
    EXPECT_EQ(m_dialog->m_result, QMessageBox::No) << "check the status after UT_CloseWindowDialog_onButtonClicked()";
}

TEST_F(UT_CloseWindowDialog, UT_CloseWindowDialog_setResult)
{
    m_dialog->setResult(1);
    EXPECT_EQ(m_dialog->m_result, 1) << "check the status after UT_CloseWindowDialog_setResult()";
}

TEST_F(UT_CloseWindowDialog, UT_CloseWindowDialog_result)
{
    m_dialog->setResult(1);
    int res = m_dialog->result();
    EXPECT_EQ(res, 1) << "check the status after UT_CloseWindowDialog_result()";
}
