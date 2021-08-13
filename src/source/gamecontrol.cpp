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
#include "gamecontrol.h"

#include <algorithm>
#include <chrono>
#include <random>

#include "time.h"

const int m_row = 10;
const int m_column = 16;
const int m_total = 160;

GameBtnFlag GameControl::m_map[12][18];
QHash<QPair<GameBtnFlag,GameBtnSize>,QPixmap> GameControl::m_picMap;

GameControl::GameControl(QObject *parent)
    : QObject(parent)
{
}

void GameControl::gameBegin()
{
    gameShuffle(true);
}

void GameControl::gameReset()
{
    gameShuffle(false);
}

void GameControl::gameShuffle(bool inital)
{
    QVector<GameBtnFlag> btnVector; //洗牌容器
    if (!inital) {
        //重置数据
        for (int i = 1; i < m_row + 1; i++) {
            for (int j = 1; j < m_column + 1; j++) {
                btnVector.append(m_map[i][j]);
            }
        }
        memset(m_map, GameBtnFlag(0), sizeof(m_map));
    } else {
        //初始化数据
        for (int i = 0; i < m_total; i += 14) {
            for (int j = 0; j < 14; j++) {
                btnVector.append(GameBtnFlag(i / 14 + 1));
                if (btnVector.count() == m_total)
                    break;
            }
        }
    }

    //打乱数据
    uint seed = static_cast<uint>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(btnVector.begin(), btnVector.begin() + m_total, std::default_random_engine(seed));

    //将数据插入游戏地图

    int k = 0;
    for (int i = 0; i < m_row + 2; i++) {
        for (int j = 0; j < m_column + 2; j++) {
            if (i != 0 && j != 0 && i != m_row + 1 && j != m_column + 1) {
                m_map[i][j] = btnVector[k];
                k++;
            }
        }
    }
}
