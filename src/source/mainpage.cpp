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
#define FRAMEWH 486


#include "mainpage.h"
#include "global.h"
#include "gamecontrol.h"

#include <DBlurEffectWidget>

#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainPage::MainPage(QWidget*parent):DWidget (parent)
{
   initUI();
}

void MainPage::initUI()
{
    QHBoxLayout *mainLayout=new QHBoxLayout();
    QVBoxLayout *vLayout=new QVBoxLayout();

    DBlurEffectWidget *switchFrame=new DBlurEffectWidget(this);
    QColor color("#F3AC6C");
    color.setAlphaF(0.2);
    switchFrame->setMaskColor(color);
    switchFrame->setMinimumSize(FRAMEWH,FRAMEWH);
    switchFrame->setBlendMode(DBlurEffectWidget::InWindowBlend);
    switchFrame->setFull(true);
    switchFrame->setBlurRectXRadius(FRAMERADIUS);
    switchFrame->setBlurRectYRadius(FRAMERADIUS);
    switchFrame->setMaskAlpha(10);


    GameButton *btn=BtnFactory::createBtn(GameBtnFlag::control,tr("Diffculty selection"),this);

    btn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    vLayout->addWidget(switchFrame);
    vLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(vLayout);
    mainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainLayout);
}
