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
#include "gamecontrol.h"
#include "gamebutton.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    initUI();
    initConnect();
}

void GamePage::setInitalTime(int time)
{
    m_value = time;
    m_progress->setInintalTime(time);
}

void GamePage::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *gameFrameLayout = new QHBoxLayout;
    QVBoxLayout *controlBtnLayout = new QVBoxLayout;
    QGridLayout *gameBtngridLayout = new QGridLayout;

    m_gameFrame = new GameBlurEffectWidget(GameBtnSize::Big, this);
    m_gameFrame->setMinimumSize(835, 516);
    m_gameFrame->setEnabled(false);
    gameBtngridLayout->setContentsMargins(20, 10, 20, 35);

    GameControl::GameInterFace().gameBegin();
    for (int i = 1; i < ROW + 1; i++) {
        for (int j = 1; j < COLUMN + 1; j++) {
            //游戏按钮阴影处理
            QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
            shadowEffect->setOffset(0, 2);
            QColor shadowColor(0, 0, 0);
            shadowColor.setAlphaF(0.5);
            shadowEffect->setColor(shadowColor);
            shadowEffect->setBlurRadius(4);
            GameButton *gameBtn = BtnFactory::createBtn(GameControl::m_map[i][j], Default, None);
            gameBtn->setLocation(i, j);
            gameBtn->setGraphicsEffect(shadowEffect);
            gameBtngridLayout->addWidget(gameBtn, i - 1, j - 1);
        }
    }
    m_gameFrame->setLayout(gameBtngridLayout);

    GameBlurEffectWidget *controlFrame = new GameBlurEffectWidget(GameBtnSize::Small, this);
    controlFrame->setMinimumSize(175, 516);
    m_controlGrp = new QButtonGroup(controlFrame);
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
    m_controlGrp->addButton(beginBtn, 0);
    m_controlGrp->addButton(resetBtn, 1);
    m_controlGrp->addButton(hintBtn, 2);
    m_controlGrp->addButton(soundBtn, 3);
    m_controlGrp->addButton(homeBtn, 4);
    controlBtnLayout->setAlignment(Qt::AlignHCenter);
    controlBtnLayout->setContentsMargins(0, 25, 0, 25);
    controlFrame->setLayout(controlBtnLayout);

    gameFrameLayout->addSpacing(-10);
    gameFrameLayout->addWidget(m_gameFrame);
    gameFrameLayout->addWidget(controlFrame);

    m_progress = new GameProgressBar(this);
    m_progress->setFixedSize(816, 49);
    qInfo() << m_progress->minimum() << m_progress->maximum();
    mainLayout->addLayout(gameFrameLayout);
    mainLayout->addWidget(m_progress);
    mainLayout->setContentsMargins(15, 86, 15, 43);
    this->setLayout(mainLayout);
}

void GamePage::initConnect()
{
    QObject::connect(m_controlGrp, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &GamePage::onBtnControl);
    QObject::connect(m_progress, &GameProgressBar::valueChanged, this, &GamePage::onProgressChanged);
    QObject::connect(m_timer, &QTimer::timeout, this, [&] {
        m_value--;
        m_progress->setValue(m_value);
    });
}

void GamePage::onBtnControl(int id)
{
    switch (id) {
    case 0: {
        if (!m_isStart) {
            m_gameFrame->setEnabled(true);
            m_timer->start();
            m_isStart = true;
            //更改图标状态
        } else {
            m_gameFrame->setEnabled(false);
            m_timer->stop();
            m_isStart = false;
            //更改图标状态
        }
        break;
    }
    }
}

void GamePage::onProgressChanged(int value)
{
    if (value == 0) {
        m_timer->stop();
        //显示失败结果
    }
}
