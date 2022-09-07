// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gamecontrol.h"

#include <QQueue>

#include <algorithm>
#include <chrono>
#include <random>

#include "time.h"

const int m_row = 10;
const int m_column = 16;
const int m_total = 160;
const int INF = 0x3f;

GameBtnFlag GameControl::m_map[12][18];
int GameControl::m_minTurn[12][18];
int GameControl::m_dir[12][18];
QPoint GameControl::m_pathMap[12][18];
QHash<QPair<GameBtnFlag, GameBtnSize>, QPixmap> GameControl::m_picMap;

GameControl::GameControl(QObject *parent)
    : QObject(parent)
{
}

void GameControl::loadPic(const GameBtnFlag &flag, const GameBtnSize &btnSize, DWidget *widget)
{
    QString fileName;
    QSize scaledSize;

    switch (btnSize) {
    case Big:
        scaledSize = QSize(250, 135);
        break;
    case Mid:
        scaledSize = QSize(200, 115);
        break;
    case Over:
        scaledSize = QSize(180, 98);
        break;
    case Small:
        scaledSize = QSize(150, 90);
        break;
    default:
        scaledSize = QSize(50, 50);
    }

    switch (flag) {
    case ButtonNormal:
        fileName = ":/assets/images/normal.png";
        break;
    case ButtonCow:
        fileName = ":/assets/images/cow.png";
        break;
    case ButtonTiger:
        fileName = ":/assets/images/tiger.png";
        break;
    case ButtonRabbit:
        fileName = ":/assets/images/rabbit.png";
        break;
    case ButtonSnake:
        fileName = ":/assets/images/snake.png";
        break;
    case ButtonHorse:
        fileName = ":/assets/images/horse.png";
        break;
    case ButtonSheep:
        fileName = ":/assets/images/sheep.png";
        break;
    case ButtonDog:
        fileName = ":/assets/images/dog.png";
        break;
    case ButtonPig:
        fileName = ":/assets/images/pig.png";
        break;
    case ButtonCat:
        fileName = ":/assets/images/cat.png";
        break;
    case ButtonLion:
        fileName = ":/assets/images/lion.png";
        break;
    case ButtonFox:
        fileName = ":/assets/images/fox.png";
        break;
    case ButtonPanda:
        fileName = ":/assets/images/panda.png";
        break;
    case MainBack:
        scaledSize = QSize(1024, 718);
        fileName = ":/assets/images/background.png";
        break;
    case ButtonHover:
        fileName = ":/assets/images/hover.png";
        break;
    case ButtonPress:
        fileName = ":/assets/images/press.png";
        break;
    case ButtonSmall:
        fileName = ":/assets/images/snormal.png";
        break;
    case ButtonSHover:
        fileName = ":/assets/images/shover.png";
        break;
    case ButtonSPress:
        fileName = ":/assets/images/spress.png";
        break;
    case checkeffect:
        scaledSize = QSize(60, 60);
        fileName = ":/assets/images/checkanimal.png";
        break;
    default:
        fileName = ":/assets/images/explode.png";
        break;
    }
    QPixmap pic = Utils::getDpiPixmap(scaledSize, fileName, widget);
    m_picMap.insert(qMakePair(flag, btnSize), pic);
}

void GameControl::gameBegin()
{
    gameShuffle(true);
}

void GameControl::gameReset()
{
    gameShuffle(false);
}

QPair<bool, QList<QPoint>> GameControl::gameJudge()
{
    QList<QPoint> pointList;
    int rowOffset = 0;
    int columnOffset = 0;
    for (int i = 1; i < m_row + 1; i++) {
        for (int j = 1; j < m_column + 1; j++) {
            while (i + rowOffset != m_row + 1) {
                if (j + columnOffset == m_column) {
                    columnOffset = 1 - j;
                    rowOffset++;
                    //qInfo()<<"trun"<<columnOffset<<rowOffset;
                } else {
                    columnOffset++;
                }

                if (rowOffset != m_row - i + 1) {
                    //                  qInfo()<<QPoint(i,j)<<QPoint(i+rowOffset,j+columnOffset);
                    QPoint startPoint = QPoint(i, j);
                    QPoint endPoint = QPoint(i + rowOffset, j + columnOffset);
                    GameSearchResult res = gameSearch(startPoint, endPoint);
                    if (res != FAIL) {
                        pointList.append(startPoint);
                        pointList.append(endPoint);
                        return qMakePair(true, pointList);
                    }
                    //qInfo()<<QPoint(i,j)<<QPoint(i+rowOffset,j+columnOffset)<<rowOffset<<columnOffset;
                }
            }
            columnOffset = 0;
            rowOffset = 0;
        }
    }
    return qMakePair(false, pointList);
}

GameSearchResult GameControl::gameSearch(const QPoint &startPos, const QPoint &endPos)
{
    //先保证的无交叉正向覆盖搜索,如果没有通路,再进行反向覆盖搜索，最后进行交叉搜索
    if (!gameBfs(false, startPos, endPos)) {
        if (!gameBfs(false, endPos, startPos)) {
            if (gameBfs(true, startPos, endPos)) {
                return PositiveSuccess;
            } else {
                return FAIL;
            }
        }
        return ReverseSuccess;
    }
    return PositiveSuccess;
}

bool GameControl::gameJudgeVictory()
{
    for (int i = 1; i < m_row + 1; i++) {
        for (int j = 1; j < m_column + 1; j++) {
            if (m_map[i][j] != ButtonBlank)
                return false;
        }
    }
    return true;
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

bool GameControl::gameBfs(bool isOveride, const QPoint &startPos, const QPoint &endPos)
{
    memset(m_minTurn, INF, sizeof(m_minTurn));
    memset(m_pathMap, 0, sizeof(m_pathMap));
    GameBtnFlag startFlag = m_map[startPos.x()][startPos.y()];
    GameBtnFlag endFlag = m_map[endPos.x()][endPos.y()];
    //如果开始点和结束点的值不相等或者两个空白值,直接返回false
    if (startFlag != endFlag || startFlag == ButtonBlank)
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
                } else { //否则，trunNum加1
                    tmpNode.direction = i;
                    tmpNode.turnNum = popNode.turnNum + 1;
                }

                //如果方向转换超过两次,不进入队列,可以去掉一部分重复检查
                if (tmpNode.turnNum > 2)
                    continue;

                //无交叉覆盖搜索
                if (!isOveride) {
                    if (tmpNode.turnNum < m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex]) {
                        m_pathMap[tmpNode.rowIndex][tmpNode.columnIndex] = QPoint(popNode.rowIndex, popNode.columnIndex);
                        m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex] = tmpNode.turnNum;
                        m_dir[tmpNode.rowIndex][tmpNode.columnIndex] = tmpNode.direction;
                        quene.enqueue(tmpNode);
                    }

                } else {
                    //交叉覆盖搜索
                    if (tmpNode.turnNum <= m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex]) {
                        m_pathMap[tmpNode.rowIndex][tmpNode.columnIndex] = QPoint(popNode.rowIndex, popNode.columnIndex);
                        m_minTurn[tmpNode.rowIndex][tmpNode.columnIndex] = tmpNode.turnNum;
                        m_dir[tmpNode.rowIndex][tmpNode.columnIndex] = tmpNode.direction;
                        quene.enqueue(tmpNode);
                    }
                }
            }
        }
    }
    return false;
}

GameButton *BtnFactory::createBtn(const GameBtnFlag &flag, const GameBtnSize &btnSize, const GameIconType &iconType, const QString &text, QWidget *parent)
{
    QFont btnFont;
    btnFont.setFamily("Noto Sans CJK SC");
    btnFont.setWeight(QFont::DemiBold);

    QSize size;
    GameButton *btn = nullptr;

    switch (btnSize) {
    case Big:
        btnFont.setPointSize(20);
        size = QSize(250, 135);
        break;
    case Mid:
        btnFont.setPointSize(16);
        size = QSize(200, 115);
        break;
    case Small:
        btnFont.setPointSize(10);
        size = QSize(150, 90);
        break;
    case Over:
        btnFont.setPointSize(16);
        size = QSize(180, 98);
        break;
    default:
        size = QSize(50, 50);
    }

    if (flag == ButtonNormal || flag == ButtonSmall) {
        if (iconType == None) {
            btn = new GameButton(flag, btnSize, text, parent);
        } else {
            btn = new GameButton(GameControl::m_picMap.value(qMakePair(flag, btnSize)), iconType, parent);
        }
    } else {
        btn = new GameButton(GameControl::m_picMap.value(qMakePair(flag, btnSize)), parent);
    }

    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn->setFixedSize(size);
    btn->setFont(btnFont);
    return btn;
}
