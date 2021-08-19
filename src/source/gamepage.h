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
#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "gameprogressbar.h"
#include "gameblureffectwidget.h"
#include "gamebutton.h"

#include <QGridLayout>
#include <QButtonGroup>
#include <QTimer>
#include <QVector>

DWIDGET_USE_NAMESPACE
class GamePage : public QWidget
{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = nullptr);
    void setInitalTime(int time); //设置初始化时间
public slots:
    void onControlBtnControl(int id);
    void onAnimalBtnControl(QAbstractButton *btn);
    void onProgressChanged(int value);
private:
    void initUI();
    void initConnect();

private:
    GameBlurEffectWidget *m_gameFrame; //游戏区域
    GameProgressBar *m_progress; //进度条
    QButtonGroup *m_animalGrp; //游戏动物按钮组
    QButtonGroup *m_controlGrp; //控制按钮组
    QTimer *m_timer; //定时器
    QVector<GameButton *> m_locationVec; //按钮地址容器
    int m_value; //进度值
    bool m_isStart = false; //开始暂停的控制
};

#endif // GAMEPAGE_H
