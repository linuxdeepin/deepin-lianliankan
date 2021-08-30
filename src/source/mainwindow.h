/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     linxun <linxun@uniontech.com>
*
* Maintainer: zhangdingwen <zhangdingwen@uniontech.com>
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "gamepage.h"
#include "utils.h"
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

signals:

private slots:
    void onShowClickedPage(int id);
    void showFinishPage(bool res);

private:
   void initUI();
   void initConnect();
   void initPic();
   void initOverWindowConnect();

public:
   void handleQuit();

private:
   DStackedWidget *m_stackedWidget;
   DTitlebar *m_titlebar;
   MainPage *m_mainPage; //主页面
   GamePage *m_gamePage; //游戏页面
   bool m_firstGame = true; //判断是否为第一次游戏
   bool m_soundSwtich = true; //保存音效开关设置
   GameoverBlurEffectWidget *m_gameOverPage;//结算界面模糊蒙版
   bool m_gameState = false;//判断游戏是否开始
};

#endif // MAINWINDOW_H
