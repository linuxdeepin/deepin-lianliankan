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

#include "mainwindow.h"
#include "gamecontrol.h"
#include "closewindowdialog.h"

#include <DTitlebar>

#include <QTime>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent):DMainWindow (parent)
{
    initUI();
}

void MainWindow::initUI()
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_titlebar = titlebar();
    m_titlebar->setIcon(QIcon(":/assets/icon/com.deepin.lianliankan.svg"));
    m_titlebar->installEventFilter(this);
    m_titlebar->setBackgroundTransparent(true);
    //加载主页面
    loadMainpage();
}

void MainWindow::loadGamePage(int id)
{
    //加载游戏页面图片
    for (int i = 1; i < 13; i++) {
        GameControl::loadPic(GameBtnFlag(i), GameBtnSize::Default, this);
    }
    GameControl::loadPic(GameBtnFlag(19), GameBtnSize::Default, this);
    GameControl::loadPic(GameBtnFlag(20), GameBtnSize::Default, this);
    //游戏页面
    m_gamePage = new GamePage(this);
    //游戏页面音效状态与主页面音效状态同步
    m_gamePage->setSoundSwitch(m_mainPage->soundState());
    //选择游戏难度，设置游戏时间
    switch (id) {
    case 1:
        m_gamePage->setInitalTime(INTER_TIME);
        break;
    case 2:
        m_gamePage->setInitalTime(ADVANCED_TIME);
        break;
    default:
        m_gamePage->setInitalTime(PRIMARY_TIME);
        break;
    }
    m_stackedWidget->addWidget(m_gamePage);

    if (!m_firstGame)
        m_gamePage->restartGame(m_firstGame);

    m_firstGame = false;

    m_stackedWidget->setCurrentWidget(m_gamePage);

    //游戏页面主页面按钮返回主页面
    connect(m_gamePage, &GamePage::backToMainPage, this, [&] {
        m_stackedWidget->setCurrentWidget(m_mainPage);
    });

    connect(m_gamePage, &GamePage::sigResult, this, &MainWindow::showFinishPage);

    connect(m_gamePage, &GamePage::setGameStated, this, [&](bool gameState) {
        m_gameState = gameState;
    });

    //游戏页面反向同步音效状态到主页面
    connect(m_gamePage, &GamePage::soundSync, this, [&](bool soundState) {
        m_mainPage->setSoundState(soundState);
    });
}

void MainWindow::loadOverPage(bool res)
{
    //加载结束界面
    m_gameOverPage = new GameoverBlurEffectWidget(centralWidget());

    QString text = "";
    if (!res) {
        m_gameOverPage->setResult(false);
        text = tr("FAIL");
    } else {
        m_gameOverPage->setResult(true);
        text = tr("VICTORY");
    }
    m_gameOverPage->updateLabel(text);
    m_gameOverPage->show();

    m_gameOverPage->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT - m_titlebar->height()));
    connect(m_gameOverPage, &GameoverBlurEffectWidget::backToMainPage, this, [&] {
        m_gameOverPage->hide();
        m_stackedWidget->setCurrentWidget(m_mainPage);
    });

    connect(m_gameOverPage, &GameoverBlurEffectWidget::reGame, this, [&] {
        m_gameOverPage->hide();
        m_gamePage->reGame();
    });
}

void MainWindow::loadMainpage()
{
    //加载主页面图片资源
    for (int i = 13; i < 19; i++) {
        GameControl::loadPic(GameBtnFlag(i), GameBtnSize::Default, this);
    }
    for (int i=1;i<4;i++) {
    GameControl::loadPic(GameBtnFlag(-1),GameBtnSize(i), this);
    GameControl::loadPic(GameBtnFlag(14), GameBtnSize(i), this);
    GameControl::loadPic(GameBtnFlag(15), GameBtnSize(i), this);
    }
    GameControl::loadPic(GameBtnFlag(16), GameBtnSize(Small), this);
    GameControl::loadPic(GameBtnFlag(17), GameBtnSize(Small), this);
    GameControl::loadPic(GameBtnFlag(18), GameBtnSize(Small), this);

    m_stackedWidget = new DStackedWidget(this);
    m_mainPage = new MainPage(m_stackedWidget);
    m_stackedWidget->addWidget(m_mainPage);
    setCentralWidget(m_stackedWidget);
    connect(m_mainPage, &MainPage::buttonPress, this, &MainWindow::onShowClickedPage);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //对titlebar透明度进行处理
    if(obj==m_titlebar){
    if(event->type()==QEvent::Paint){
        DGuiApplicationHelper::ColorType themtype = DGuiApplicationHelper::instance()->themeType();
        QColor broundColor;
         if (themtype == DGuiApplicationHelper::ColorType::DarkType) {
             broundColor = m_titlebar->palette().color(QPalette::Normal, QPalette::Dark);
         } else if (themtype == DGuiApplicationHelper::ColorType::LightType) {
             broundColor = m_titlebar->palette().color(QPalette::Normal, QPalette::Light);
         }
        QPainter painter(m_titlebar);
        painter.setRenderHint(QPainter::Antialiasing, true);
        broundColor.setAlphaF(0.8);
        painter.setBrush(broundColor);
        painter.setPen(Qt::NoPen);
        painter.fillRect(titlebar()->rect(), broundColor);
        painter.drawRect(titlebar()->rect());
        return  true;
     }

    }
    return  DMainWindow::eventFilter(obj,event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPixmap pic = GameControl::m_picMap.value(qMakePair(MainBack, Default));
    p.drawPixmap(rect().x(), rect().y() + m_titlebar->rect().height(), pic);
    DWidget::paintEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_gameState) {
        CloseWindowDialog *dialog = new CloseWindowDialog(this);
        //保留弹出窗口前的开始暂停状态
        bool preOnOff = m_gamePage->onOffGame();
        //弹出阻塞窗口暂停游戏
        m_gamePage->setOnOffGame(false);
        dialog->setMinimumWidth(390);
        this->setEnabled(false);
        dialog->setEnabled(true);
        dialog->show();
        //添加时间循环，直到获取按钮信息退出循环
        QEventLoop loop;
        connect(dialog, &CloseWindowDialog::buttonClicked, &loop, &QEventLoop::quit);
        connect(dialog, &CloseWindowDialog::finished, &loop, &QEventLoop::quit);
        loop.exec();
        this->setEnabled(true);
        if (dialog->result() == QMessageBox::Ok) {
            event->accept();
        } else {
            m_gamePage->setOnOffGame(preOnOff);
            event->ignore();
        }
        dialog->done(0);
    } else {
        event->accept();
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()!=QEvent::WindowStateChange) {
        event->accept();
    }
    if (this->windowState() == Qt::WindowMinimized && m_gamePage) {
        if (m_gamePage->onOffGame())
            m_gamePage->setOnOffGame(false);
    }
    event->accept();
}

void MainWindow::onShowClickedPage(int id)
{
    //加载游戏页面
    loadGamePage(id);
}

void MainWindow::showFinishPage(bool res)
{
    //加载结束页面
    loadOverPage(res);
    //游戏状态停止
    m_gameState = false;
}
