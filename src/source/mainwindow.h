// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "gamepage.h"
#include "gameblureffectwidget.h"
#include "gameoverblureffectwidget.h"

#include <DMainWindow>
#include <DStackedWidget>
DWIDGET_USE_NAMESPACE
class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event)override;
    void closeEvent(QCloseEvent *event) override;
    void changeEvent(QEvent *event) override;

private slots:
    void onShowClickedPage(int id);
    void showFinishPage(bool res);

private:
    /**
   * @brief  MainWindow::initUI 初始化页面
   */
    void initUI();
    /**
   * @brief  MainWindow::loadMainPage 加载主页面
   */
    void loadMainpage();
    /**
   * @brief  MainWindow::loadGamePage 加载游戏页面
   * @param  id 游戏难度按钮id
   */
    void loadGamePage(int id);
    /**
   * @brief  MainWindow::loadOverPage 加载结束页面
   * @param  res 游戏结果
   */
    void loadOverPage(bool res);

private:
   DStackedWidget *m_stackedWidget;
   DTitlebar *m_titlebar;
   MainPage *m_mainPage; //主页面
   GamePage *m_gamePage = nullptr; //游戏页面
   GameoverBlurEffectWidget *m_gameOverPage; //结算界面模糊蒙版
   bool m_firstGame = true; //判断是否为第一次游戏
   bool m_soundSwtich = true; //保存音效开关设置
   bool m_gameState = false;//判断游戏是否开始
};

#endif // MAINWINDOW_H
