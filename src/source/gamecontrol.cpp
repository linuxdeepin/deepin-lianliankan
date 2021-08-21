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
const int INF = 0x3f3f3f3f;

GameBtnFlag GameControl::m_map[12][18];
int GameControl::m_minTurn[12][18];
QPoint GameControl::m_pathMap[12][18];
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
    return gameBfs(startPos, endPos);
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

bool GameControl::gameBfs(const QPoint &startPos, const QPoint &endPos)
{
    memset(m_minTurn, INF, sizeof(m_minTurn));
    memset(m_pathMap, 0, sizeof(m_pathMap));
    GameBtnFlag startFlag = m_map[startPos.x()][startPos.y()];
    GameBtnFlag endFlag = m_map[endPos.x()][endPos.y()];
    //如果开始点和结束点的值不相等,直接返回false
    if (startFlag != endFlag)
        return false;

    QQueue<GameNode> quene;
    GameNode startNode, popNode, tmpNode;
    startNode.rowIndex = startPos.x();
    startNode.columnIndex = startPos.y();
    startNode.direction = -1;
    startNode.turnNum = 0;
    int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    quene.enqueue(startNode);
    while (!quene.isEmpty()) {
        popNode = quene.first();
        quene.pop_front();

        //判读是否是找到最后的点且是否转弯次数大于三次,如果大于,则返回false,反之,返回true.
        if (popNode.rowIndex == endPos.x() && popNode.columnIndex == endPos.y()) {
            return popNode.turnNum <= 2;
        }
        for (int i = 0; i < 4; i++) {
            int newRowIndex = popNode.rowIndex + dir[i][0];
            int newColumnIndex = popNode.columnIndex + dir[i][1];
            int endRow = endPos.x();
            int endColumn = endPos.y();
            GameBtnFlag tmpFlag = m_map[newRowIndex][newColumnIndex];

            if (newRowIndex >= 0 && newRowIndex <= 11 && newColumnIndex >= 0 && newColumnIndex <= 17 && (tmpFlag == ButtonBlank || (newRowIndex == endRow && newColumnIndex == endColumn))) {
                tmpNode.rowIndex = newRowIndex;
                tmpNode.columnIndex = newColumnIndex;
                //队首元素的方向任意(-1)或队首元素的方向与当前方向相同，trunNum不变
                if (popNode.direction == -1 || popNode.direction == i) {
                    tmpNode.direction = i;
                    tmpNode.turnNum = popNode.turnNum;
                } else //否则，trunNum加1
                {
                    tmpNode.direction = i;
                    tmpNode.turnNum = popNode.turnNum + 1;
                }

                //如果方向转换超过两次,不进入队列,可以去掉一部分重复检查
                if (tmpNode.turnNum > 2)
                    continue;

                //保证转弯次数最少
                if (tmpNode.turnNum <= m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex]) {
                    m_pathMap[tmpNode.rowIndex][tmpNode.columnIndex] = QPoint(popNode.rowIndex, popNode.columnIndex);
                    m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex] = tmpNode.turnNum;
                    quene.enqueue(tmpNode);
                }
            }
        }
    }
    //qInfo()<<"false";
    return false;
}
