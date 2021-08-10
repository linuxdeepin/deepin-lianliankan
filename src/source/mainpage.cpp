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
#define FRAMEWH 480
#define FRAMEHH 515


#include "mainpage.h"
#include "global.h"
#include "gamecontrol.h"
#include "gameblureffectwidget.h"

#include <QPainter>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QDebug>

MainPage::MainPage(QWidget*parent):DWidget (parent)
{
    initUI();
}

void MainPage::initUI()
{
    QButtonGroup *btnGrp=new QButtonGroup;
    GameButton *primaryBtn=BtnFactory::createBtn(GameBtnFlag::ButtonNormal,GameBtnSize::Mid,GameIconType::None,tr("初级"),this);
    GameButton *interBtn=BtnFactory::createBtn(GameBtnFlag::ButtonNormal,GameBtnSize::Mid,GameIconType::None,tr("中级"),this);
    GameButton *advanceBtn=BtnFactory::createBtn(GameBtnFlag::ButtonNormal,GameBtnSize::Mid,GameIconType::None,tr("高级"),this);
    btnGrp->addButton(primaryBtn);
    btnGrp->addButton(interBtn);
    btnGrp->addButton(advanceBtn);
    btnGrp->setExclusive(true);

    GameBlurEffectWidget *switchFrame=new GameBlurEffectWidget(this);
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

    GameButton *swithBtn=BtnFactory::createBtn(GameBtnFlag::ButtonNormal,GameBtnSize::Big,GameIconType::None,tr("选择难度"),this);
    swithBtn->setGeometry(393,80,250,135);
    GameButton *soundBtn=BtnFactory::createBtn(GameBtnFlag::ButtonNormal,GameBtnSize::Small,GameIconType::Sound);
    soundBtn->setParent(this);
    soundBtn->setGeometry(854,569,140,80);
}
