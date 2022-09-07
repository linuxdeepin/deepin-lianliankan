// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
    connect(m_soundBtn, &GameButton::pressed, this, [&] {
        this->setSoundState(!m_soundState);
    });
}

void MainPage::setSoundState(bool state)
{
    m_soundState = state;
    m_soundBtn->updatePlayIcon(SoundCtl, m_soundState);
}

bool MainPage::soundState() const
{
    return m_soundState;
}

void MainPage::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
