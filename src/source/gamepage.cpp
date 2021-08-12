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

#include <QDebug>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void GamePage::initUI()
{
    GameBlurEffectWidget *gameFrame = new GameBlurEffectWidget(QSize(850, 516), this);
    m_gridLayout = new QGridLayout;
    m_gridLayout->setContentsMargins(30, 10, 35, 35);
    addBtn();
    gameFrame->setLayout(m_gridLayout);
    gameFrame->setGeometry(-5, 86, 850, 516);
    m_progress = new DProgressBar(this);
    m_progress->setGeometry(15, 633, 816, 49);
}

void GamePage::addBtn()
{
    GameControl::GameInterFace().gameBegin();
    for (int i = 1; i < ROW + 1; i++) {
        for (int j = 1; j < COLUMN + 1; j++) {
            GameButton *gameBtn = BtnFactory::createBtn(GameControl::m_map[i][j], Default, None);
            gameBtn->setLocation(i, j);
            m_gridLayout->addWidget(gameBtn, i - 1, j - 1);
        }
    }
}
