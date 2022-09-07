// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMELINESCENE_H
#define GAMELINESCENE_H

#include <QWidget>
#include <QPainterPath>

class GameLineScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameLineScene(QWidget *parent = nullptr);
    /**
    * @brief  GameLineScene::setDrawPath 设置绘制路径
    * @param  posList 路径容器
    */
    void setDrawPath(const QList<QPointF> &posList);
    /**
    * @brief  GameLineScene::setMissing 连线消失
    */
    void setMissing();
public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    /**
    * @brief  GameLineScene::drawLightEffeec 绘制光效效果
    * @param  pos 连线的点
    */
    void drawLightEffeec(QPainter &p, QPainterPath &path, const QPointF &pos);

private:
    QList<QPointF> m_posList;
};

#endif // GAMELINESCENE_H
