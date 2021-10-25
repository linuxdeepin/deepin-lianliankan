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

#include <gtest/gtest.h>
#include <stub.h>

#include <gamelinescene.h>

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

class UT_GameLineScene : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_scene = new GameLineScene;
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_scene) {
            delete m_scene;
            m_scene = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
    GameLineScene *m_scene;
};

TEST_F(UT_GameLineScene, UT_GameLineScene_setDrawPath)
{
    QList<QPointF> posList;
    posList.append(QPointF(0, 0));
    posList.append(QPointF(0, 100));
    posList.append(QPointF(100, 200));
    posList.append(QPointF(200, 100));
    m_scene->setDrawPath(posList);
    EXPECT_EQ(m_scene->m_posList, posList) << "check the status after UT_GameBlurEffectWidget_setDrawPath()";
}

TEST_F(UT_GameLineScene, UT_GameLineScene_setMissing)
{
    m_scene->setMissing();
    EXPECT_EQ(m_scene->m_posList.isEmpty(), true) << "check the status after UT_GameBlurEffectWidget_setMissing()";
}

TEST_F(UT_GameLineScene, UT_GameLineScene_drawLightEffeec)
{
    QPainter p(m_scene);
    QPainterPath path;
    m_scene->drawLightEffeec(p, path, QPoint(100, 100));
    EXPECT_NE(m_scene, nullptr) << "check the status after UT_GameBlurEffectWidget_drawLightEffeec()";
}

TEST_F(UT_GameLineScene, UT_GameLineScene_paintEvent)
{
    QPaintEvent e(m_scene->rect());
    m_scene->paintEvent(&e);
    QList<QPointF> posList;
    posList.append(QPointF(0, 0));
    posList.append(QPointF(0, 100));
    posList.append(QPointF(100, 200));
    posList.append(QPointF(200, 100));
    m_scene->setDrawPath(posList);
    m_scene->paintEvent(&e);
    EXPECT_NE(m_scene, nullptr) << "check the status after UT_GameBlurEffectWidget_paintEvent()";
}
