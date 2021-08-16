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
#include "gamepage.h"
#include "gameblureffectwidget.h"
#include "gamecontrol.h"
#include "gamebutton.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QDebug>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void GamePage::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *gameFrameLayout = new QHBoxLayout;
    QVBoxLayout *controlBtnLayout = new QVBoxLayout;
    QGridLayout *gameBtngridLayout = new QGridLayout;

    GameBlurEffectWidget *gameFrame = new GameBlurEffectWidget(GameBtnSize::Big, this);
    gameFrame->setMinimumSize(835, 516);

    gameBtngridLayout->setContentsMargins(20, 10, 20, 35);
    GameControl::GameInterFace().gameBegin();
    for (int i = 1; i < ROW + 1; i++) {
        for (int j = 1; j < COLUMN + 1; j++) {
            GameButton *gameBtn = BtnFactory::createBtn(GameControl::m_map[i][j], Default, None);
            gameBtn->setLocation(i, j);
            gameBtngridLayout->addWidget(gameBtn, i - 1, j - 1);
        }
    }
    gameFrame->setLayout(gameBtngridLayout);

    GameBlurEffectWidget *controlFrame = new GameBlurEffectWidget(GameBtnSize::Small, this);
    controlFrame->setMinimumSize(175, 516);
    QButtonGroup *controlGrp = new QButtonGroup(controlFrame);
    GameButton *beginBtn = BtnFactory::createBtn(ButtonNormal, Small, None);
    GameButton *resetBtn = BtnFactory::createBtn(ButtonNormal, Small, None);
    GameButton *hintBtn = BtnFactory::createBtn(ButtonNormal, Small, None);
    GameButton *soundBtn = BtnFactory::createBtn(ButtonNormal, Small, None);
    GameButton *homeBtn = BtnFactory::createBtn(ButtonNormal, Small, None);
    controlBtnLayout->addWidget(beginBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(resetBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(hintBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(soundBtn);
    controlBtnLayout->addStretch();
    controlBtnLayout->addWidget(homeBtn);
    controlGrp->addButton(beginBtn);
    controlGrp->addButton(resetBtn);
    controlGrp->addButton(hintBtn);
    controlGrp->addButton(soundBtn);
    controlGrp->addButton(homeBtn);
    controlBtnLayout->setAlignment(Qt::AlignHCenter);
    controlBtnLayout->setContentsMargins(0, 25, 0, 25);
    controlFrame->setLayout(controlBtnLayout);

    gameFrameLayout->addSpacing(-10);
    gameFrameLayout->addWidget(gameFrame);
    gameFrameLayout->addWidget(controlFrame);

    m_progress = new GameProgressBar(this);
    m_progress->setValue(100);
    m_progress->setTextVisible(false);
    m_progress->addThreshold(2, Qt::red);
    m_progress->setFixedSize(816, 49);
    qInfo() << m_progress->minimum() << m_progress->maximum();
    mainLayout->addLayout(gameFrameLayout);
    mainLayout->addWidget(m_progress);
    mainLayout->setContentsMargins(15, 86, 15, 43);
    this->setLayout(mainLayout);
}
