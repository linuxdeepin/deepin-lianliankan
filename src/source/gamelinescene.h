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
#ifndef GAMELINESCENE_H
#define GAMELINESCENE_H

#include <QWidget>

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
