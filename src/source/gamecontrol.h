// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "gamebutton.h"
#include "utils.h"

#include <QObject>
#include <QMap>
#include <QImageReader>
#include <QFont>
#include <QDebug>
#include <QMap>
#include <QBitmap>

class GameControl : public QObject
{
    Q_OBJECT
public:
    static GameControl& GameInterFace(){
        static GameControl control;
        return  control;
    }
    /**
    * @brief  GameControl::loadPic 加载图片
    * @param  flag 图片类型
    * @param  btnSize 图片大小
    * @param  widget 当前组件
    */
    static void loadPic(const GameBtnFlag &flag, const GameBtnSize &btnSize, DWidget *widget);
    /**
    * @brief  GameControl::gameBegin 游戏开始
    */
    void gameBegin();
    /**
    * @brief  GameControl::gameReset 游戏重置
    */
    void gameReset();
    /**
    * @brief  GameControl::gameJudge 游戏判断
    * @return QPair 判断结果和成功之后的pos
    */
    QPair<bool, QList<QPoint>> gameJudge();
    /**
    * @brief  GameControl::gameSearch 游戏寻路
    * @param  startPos 找寻路线的起点
    * @param  endPos   找寻路线的终点
    * @return GameSearchResult 寻路结果
    */
    GameSearchResult gameSearch(const QPoint &startPos, const QPoint &endPos); //寻路
    /**
    * @brief  GameControl::gameJudgeVictory 判断游戏是否胜利
    * @return bool 胜利或者失败
    */
    bool gameJudgeVictory();
    static GameBtnFlag m_map[12][18];//游戏地图
    static int m_minTurn[12][18]; //记录最小转弯数
    static int m_dir[12][18]; //记录转弯方向
    static QPoint m_pathMap[12][18]; //通路坐标
    static QHash<QPair<GameBtnFlag, GameBtnSize>, QPixmap>m_picMap;//图片资源
signals:

public slots:

private:
    explicit GameControl(QObject *parent = nullptr);
    /**
    * @brief  GameControl::gameShuffle 游戏洗牌打乱重置
    * @return inital 开始洗牌或者重置洗牌
    */
    void gameShuffle(bool inital);
    /**
    * @brief  GameControl::gameBfs 游戏广度搜索算法
    * @param  isOveride 是否交叉搜索
    * @param  startPos 找寻路线的起点
    * @param  endPos   找寻路线的终点
    * @return bool 寻路结果
    */
    bool gameBfs(bool isOveride, const QPoint &startPos, const QPoint &endPos);
};

class BtnFactory{
public:
    /**
    * @brief  BtnFactory::createBtn 创建不同类型不同的大小的按钮控件
    * @param  flag 按钮类型
    * @param  btnSize 按钮大小
    * @param  text   文本按钮文本
    */
    static GameButton *createBtn(const GameBtnFlag &flag, const GameBtnSize &btnSize, const GameIconType &iconType, const QString &text = " ", QWidget *parent = nullptr);
};

#endif // GAMECONTROL_H
