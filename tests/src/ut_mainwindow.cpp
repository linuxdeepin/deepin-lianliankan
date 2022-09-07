// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <mainwindow.h>
#include <gamepage.h>

#include <DTitlebar>
#include <DGuiApplicationHelper>

#include <QPaintEvent>
#include <QEventLoop>
#include <QDebug>


const int primary = 0;
const int inter = 1;
const int advance = 2;

DGuiApplicationHelper::ColorType UT_MainWindow_themeType_001()
{
    return DGuiApplicationHelper::DarkType;
}

DGuiApplicationHelper::ColorType UT_MainWindow_themeType_002()
{
    return DGuiApplicationHelper::LightType;
}

bool UT_MainWindow_onOffGame()
{
    return true;
}

void UT_MainWindow_setOnOffGame(bool isBegin)
{
    Q_UNUSED(isBegin);
}

int UT_MainWindow_exec(QEventLoop::ProcessEventsFlags flags)
{
    Q_UNUSED(flags);
    return 0;
}

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
        if (m_mainwindow) {
            delete m_mainwindow;
            m_mainwindow = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
    MainWindow *m_mainwindow;
};

TEST_F(UT_MainWindow, UT_MainWindow_initUI)
{
    m_mainwindow->initUI();
    EXPECT_EQ(m_mainwindow->windowFlags(), m_mainwindow->windowFlags() & ~Qt::WindowMaximizeButtonHint) << "check the status after UT_MainWindow_initUI()";
    EXPECT_EQ(m_mainwindow->size(), QSize(WINDOW_WIDTH, WINDOW_HEIGHT)) << "check the status after UT_MainWindow_initUI()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadMainpage)
{
    m_mainwindow->loadMainpage();
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadMainpage()";
    EXPECT_NE(m_mainwindow->m_mainPage, nullptr) << "check the status after UT_MainWindow_loadMainpage()";
    EXPECT_EQ(m_mainwindow->m_stackedWidget->currentWidget(), m_mainwindow->m_mainPage) << "check the status after UT_MainWindow_loadMainpage()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadGamePage_001)
{
    m_mainwindow->loadGamePage(primary);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadGamePage_001()";
    EXPECT_NE(m_mainwindow->m_gamePage, nullptr) << "check the status after UT_MainWindow_loadGamePage_001()";
    EXPECT_EQ(m_mainwindow->m_stackedWidget->currentWidget(), m_mainwindow->m_gamePage) << "check the status after UT_MainWindow_loadGamePage_001()";
    EXPECT_EQ(m_mainwindow->m_gamePage->m_value, PRIMARY_TIME) << "check the status after UT_MainWindow_loadGamePage_001()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadGamePage_002)
{
    m_mainwindow->loadGamePage(inter);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadGamePage_002()";
    EXPECT_NE(m_mainwindow->m_gamePage, nullptr) << "check the status after UT_MainWindow_loadGamePage_002()";
    EXPECT_EQ(m_mainwindow->m_stackedWidget->currentWidget(), m_mainwindow->m_gamePage) << "check the status after UT_MainWindow_loadGamePage_002()";
    EXPECT_EQ(m_mainwindow->m_gamePage->m_value, INTER_TIME) << "check the status after UT_MainWindow_loadGamePage_002()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadGamePage_003)
{
    m_mainwindow->m_firstGame = false;
    m_mainwindow->loadGamePage(advance);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadGamePage_003()";
    EXPECT_NE(m_mainwindow->m_gamePage, nullptr) << "check the status after UT_MainWindow_loadGamePage_003()";
    EXPECT_EQ(m_mainwindow->m_stackedWidget->currentWidget(), m_mainwindow->m_gamePage) << "check the status after UT_MainWindow_loadGamePage_003()";
    EXPECT_EQ(m_mainwindow->m_gamePage->m_value, ADVANCED_TIME) << "check the status after UT_MainWindow_loadGamePage_003()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadOverPage_001)
{
    m_mainwindow->loadOverPage(true);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadOverPage_001()";
    EXPECT_NE(m_mainwindow->m_gameOverPage, nullptr) << "check the status after UT_MainWindow_loadOverPage_001()";
    EXPECT_EQ(m_mainwindow->m_gameOverPage->m_tipLabel->text(), "VICTORY") << "check the status after UT_MainWindow_loadOverPage_001()";
    EXPECT_EQ(m_mainwindow->m_gameOverPage->size(), QSize(WINDOW_WIDTH, WINDOW_HEIGHT - m_mainwindow->m_titlebar->height())) << "check the status after UT_MainWindow_loadOverPage_001()";
}

TEST_F(UT_MainWindow, UT_MainWindow_loadOverPage_002)
{
    m_mainwindow->loadOverPage(false);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_loadOverPage_002()";
    EXPECT_NE(m_mainwindow->m_gameOverPage, nullptr) << "check the status after UT_MainWindow_loadOverPage_002()";
    EXPECT_EQ(m_mainwindow->m_gameOverPage->m_tipLabel->text(), "FAIL") << "check the status after UT_MainWindow_loadOverPage_002()";
    EXPECT_EQ(m_mainwindow->m_gameOverPage->size(), QSize(WINDOW_WIDTH, WINDOW_HEIGHT - m_mainwindow->m_titlebar->height())) << "check the status after UT_MainWindow_loadOverPage_002()";
}

TEST_F(UT_MainWindow, UT_MainWindow_onShowClickedPage)
{
    m_mainwindow->onShowClickedPage(primary);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_onShowClickedPage()";
    EXPECT_NE(m_mainwindow->m_gamePage, nullptr) << "check the status after UT_MainWindow_onShowClickedPage()";
}

TEST_F(UT_MainWindow, UT_MainWindow_showFinishPage)
{
    m_mainwindow->showFinishPage(true);
    EXPECT_NE(m_mainwindow->m_stackedWidget, nullptr) << "check the status after UT_MainWindow_showFinishPage()";
    EXPECT_NE(m_mainwindow->m_gameOverPage, nullptr) << "check the status after UT_MainWindow_showFinishPage()";
    EXPECT_EQ(m_mainwindow->m_gameState, false) << "check the status after UT_MainWindow_showFinishPage()";
}

TEST_F(UT_MainWindow, UT_MainWindow_eventFilter_001)
{
    Stub stub;
    stub.set(ADDR(DGuiApplicationHelper, themeType), UT_MainWindow_themeType_001);
    QEvent event(QEvent::Paint);
    bool res = m_mainwindow->eventFilter(m_mainwindow->m_titlebar, &event);
    EXPECT_NE(m_mainwindow->m_titlebar, nullptr) << "check the status after UT_MainWindow_eventFilter_001()";
    EXPECT_EQ(res, true) << "check the status after UT_MainWindow_eventFilter_001()";
}

TEST_F(UT_MainWindow, UT_MainWindow_eventFilter_002)
{
    Stub stub;
    stub.set(ADDR(DGuiApplicationHelper, themeType), UT_MainWindow_themeType_002);
    QEvent event(QEvent::Paint);
    bool res = m_mainwindow->eventFilter(m_mainwindow->m_titlebar, &event);
    EXPECT_NE(m_mainwindow->m_titlebar, nullptr) << "check the status after UT_MainWindow_eventFilter_002()";
    EXPECT_EQ(res, true) << "check the status after UT_MainWindow_eventFilter_002()";
}

TEST_F(UT_MainWindow, UT_MainWindow_paintEvent)
{
    QPaintEvent paintEvent(m_mainwindow->rect());
    m_mainwindow->paintEvent(&paintEvent);
    EXPECT_NE(m_mainwindow, nullptr) << "check the status after UT_MainWindow_paintEvent()";
}

TEST_F(UT_MainWindow, UT_MainWindow_closeEvent)
{
    Stub stub;
    stub.set(ADDR(GamePage, onOffGame), UT_MainWindow_onOffGame);
    stub.set(ADDR(GamePage, setOnOffGame), UT_MainWindow_setOnOffGame);
    stub.set(ADDR(QEventLoop, exec), UT_MainWindow_exec);
    m_mainwindow->m_gamePage = new GamePage(m_mainwindow);
    QCloseEvent closeEvent;
    m_mainwindow->closeEvent(&closeEvent);
    m_mainwindow->m_gameState = true;
    m_mainwindow->closeEvent(&closeEvent);
    EXPECT_NE(m_mainwindow, nullptr) << "check the status after UT_MainWindow_closeEvent()";
}

TEST_F(UT_MainWindow, UT_MainWindow_changeEvent)
{
    QEvent event(QEvent::WindowStateChange);
    m_mainwindow->changeEvent(&event);
    EXPECT_NE(m_mainwindow, nullptr) << "check the status after UT_MainWindow_changeEvent()";
}
