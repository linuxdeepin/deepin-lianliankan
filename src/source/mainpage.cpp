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
#define FRAMEWH 480
#define FRAMEHH 515


#include "mainpage.h"
#include "global.h"
#include "gamecontrol.h"
#include "gameblureffectwidget.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QTime>
#include <QBitmap>

MainPage::MainPage(QWidget*parent):DWidget (parent)
{
    initUI();
    initConnect();
}

void MainPage::initUI()
{
    m_btnGrp=new QButtonGroup(this);
    GameButton *primaryBtn = BtnFactory::createBtn(GameBtnFlag::ButtonNormal, GameBtnSize::Mid, GameIconType::None, tr("Easy"), this);
    GameButton *interBtn = BtnFactory::createBtn(GameBtnFlag::ButtonNormal, GameBtnSize::Mid, GameIconType::None, tr("Normal"), this);
    GameButton *advanceBtn = BtnFactory::createBtn(GameBtnFlag::ButtonNormal, GameBtnSize::Mid, GameIconType::None, tr("Hard"), this);
    m_btnGrp->addButton(primaryBtn, 0);
    m_btnGrp->addButton(interBtn, 1);
    m_btnGrp->addButton(advanceBtn, 2);
    m_btnGrp->setExclusive(true);

    GameBlurEffectWidget *switchFrame = new GameBlurEffectWidget(GameBtnSize::Mid, this);
    QVBoxLayout *frameLayout=new QVBoxLayout;
    frameLayout->addWidget(primaryBtn);
    frameLayout->addSpacing(-20);
    frameLayout->addWidget(interBtn);
    frameLayout->addSpacing(-20);
    frameLayout->addWidget(advanceBtn);
    frameLayout->addSpacing(-20);
    frameLayout->setAlignment(Qt::AlignHCenter);
    switchFrame->setGeometry(278,125,FRAMEWH,FRAMEHH);
    switchFrame->setLayout(frameLayout);

    GameButton *swithBtn = BtnFactory::createBtn(GameBtnFlag::ButtonNormal, GameBtnSize::Big, GameIconType::None, tr("Select Level"), this);
    swithBtn->setEnabled(false);
    //这里由于窗口大小固定，且布局较难控制，故将按钮位置写为固定数字
    swithBtn->setGeometry(393,80,250,135);
    m_soundBtn = BtnFactory::createBtn(GameBtnFlag::ButtonSmall, GameBtnSize::Small, GameIconType::Sound);
    m_soundBtn->setParent(this);
    m_soundBtn->setGeometry(854, 569, 140, 80);

}

void MainPage::initConnect()
{
    connect(m_btnGrp, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &MainPage::buttonPress);
    connect(m_soundBtn, &GameButton::pressed, this, &MainPage::soundSwitch);
}

void MainPage::soundSync(bool isOpen)
{
    m_soundState = isOpen;
    m_soundBtn->updatePlayIcon(SoundCtl, m_soundState);
}

void MainPage::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
