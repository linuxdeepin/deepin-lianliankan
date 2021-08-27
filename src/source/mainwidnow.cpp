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

#include "mainwidnow.h"
#include "gamecontrol.h"

#include <DTitlebar>

#include <QImageReader>
#include <QHBoxLayout>
#include <QTime>

MainWidnow::MainWidnow(QWidget *parent):DMainWindow (parent)
{
    initPic();
    initUI();
    initConnect();
}

void MainWidnow::initUI()
{
   m_titlebar=titlebar();
   m_titlebar->installEventFilter(this);
   m_titlebar->setBackgroundTransparent(true);

   m_stackedWidget = new DStackedWidget(this);
   m_mainPage = new MainPage(m_stackedWidget);
   m_gamePage = new GamePage(m_stackedWidget);

   m_stackedWidget->addWidget(m_mainPage);
   m_stackedWidget->addWidget(m_gamePage);

   setCentralWidget(m_stackedWidget);
}

void MainWidnow::initConnect()
{
    connect(m_mainPage, &MainPage::buttonPress, this, &MainWidnow::onShowClickedPage);
    //主页面音效按钮控制
    connect(m_mainPage, &MainPage::soundSwitch, this, [&] {
        m_gamePage->setSoundSwitch(!m_gamePage->soundSwitch());
    });
    //游戏页面主页面按钮返回主页面
    connect(m_gamePage, &GamePage::backToMainPage, this, [&] {
        m_stackedWidget->setCurrentWidget(m_mainPage);
    });
}

void MainWidnow::initPic()
{
    //    QTime time;
    //    time.start();
    //加载图片
    for (int i = 1; i < 18; i++) {
        GameControl::loadPic(GameBtnFlag(i), GameBtnSize::Default, this);
    }
    for (int i=1;i<4;i++) {
        GameControl::loadPic(GameBtnFlag(-1), GameBtnSize(i), this);
    }

//qInfo()<<time.elapsed()<<GameControl::m_picMap.value(qMakePair(GameBtnFlag::ButtonCat,GameBtnSize::Default));
}

bool MainWidnow::eventFilter(QObject *obj, QEvent *event)
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

void MainWidnow::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPixmap pic = GameControl::m_picMap.value(qMakePair(MainBack, Default));
    p.drawPixmap(rect().x(), rect().y() + m_titlebar->rect().height(), pic);
    DWidget::paintEvent(event);
}

void MainWidnow::onShowClickedPage(int id)
{
    switch (id) {
    case 1:
        m_gamePage->setInitalTime(320);
        break;
    case 2:
        m_gamePage->setInitalTime(160);
        break;
    default:
        m_gamePage->setInitalTime(480);
        break;
    }
    if (!m_firstGame)
        m_gamePage->beginGame();

    m_firstGame = false;
    m_stackedWidget->setCurrentWidget(m_gamePage);
}
