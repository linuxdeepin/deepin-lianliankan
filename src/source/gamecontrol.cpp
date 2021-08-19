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

#include <QQueue>

#include <algorithm>
#include <chrono>
#include <random>

#include "time.h"

const int m_row = 10;
const int m_column = 16;
const int m_total = 160;

GameBtnFlag GameControl::m_map[12][18];
bool GameControl::m_vis[12][18];
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

bool GameControl::gameSearch(const QPoint &startPos, const QPoint &endPos)
{
    return bfs(startPos, endPos);
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

bool GameControl::bfs(const QPoint &startPos, const QPoint &endPos)
{
    memset(m_vis, false, sizeof(m_vis));
    GameBtnFlag startFlag = m_map[startPos.x()][startPos.y()];
    GameBtnFlag endFlag = m_map[endPos.x()][endPos.y()];
    if (startFlag != endFlag)
        return false;

    QQueue<GameNode> quene;
    GameNode startNode, tmpNode;
    startNode.rowIndex = startPos.x();
    startNode.columnIndex = startPos.y();
    startNode.direction = -1;
    startNode.turnNum = -1;
    m_vis[startNode.rowIndex][startNode.columnIndex] = true;
    int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    quene.enqueue(startNode);
    while (!quene.isEmpty()) {
        GameNode popNode = quene.first();
        quene.pop_front();

        if (popNode.rowIndex == endPos.x() && popNode.columnIndex == endPos.y()) {
            //qInfo()<<popNode.rowIndex<<popNode.columnIndex<<popNode.direction<<popNode.turnNum<<"lastNode";
            return popNode.turnNum <= 2;
        }

        for (int i = 0; i < 4; i++) {
            tmpNode = popNode;
            m_vis[tmpNode.rowIndex][tmpNode.columnIndex] = true;
            tmpNode.rowIndex += dir[i][0];
            tmpNode.columnIndex += dir[i][1];
            //qInfo()<<tmpNode.rowIndex<<tmpNode.columnIndex<<"index";
            int endRow = endPos.x();
            int endColumn = endPos.y();
            GameBtnFlag tmpFlag = m_map[tmpNode.rowIndex][tmpNode.columnIndex];
            //qInfo()<<tmpFlag<<"1111";
            bool coordinateValid = tmpNode.rowIndex >= 0 && tmpNode.rowIndex <= 11 && tmpNode.columnIndex >= 0 && tmpNode.columnIndex <= 17;
            // qInfo()<<coordinateValid<<m_vis[tmpNode.rowIndex][tmpNode.columnIndex]<<"2222";
            if (coordinateValid && (tmpFlag == ButtonBlank || (tmpNode.rowIndex == endRow && tmpNode.columnIndex == endColumn)) && m_vis[tmpNode.rowIndex][tmpNode.columnIndex] == false) {
                tmpNode.prev = &popNode;

                if (tmpNode.direction != i) {
                    if (tmpNode.turnNum + 1 <= 2) {
                        tmpNode.turnNum++;
                        tmpNode.direction = i;
                        // qInfo()<< tmpNode.rowIndex<< tmpNode.columnIndex<< tmpNode.direction<< tmpNode.turnNum<<" tmpNode";
                        quene.enqueue(tmpNode);
                    } else {
                    }

                } else {
                    tmpNode.direction = i;
                    //qInfo()<< tmpNode.rowIndex<< tmpNode.columnIndex<< tmpNode.direction<< tmpNode.turnNum<<" dirNode";
                    quene.enqueue(tmpNode);
                }
            }
        }
    }
    //qInfo()<<"false";
    return false;
}
