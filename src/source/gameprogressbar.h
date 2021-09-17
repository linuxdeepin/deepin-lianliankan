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
#ifndef GAMEPROGRESSBAR_H
#define GAMEPROGRESSBAR_H

#include <DColoredProgressBar>

DWIDGET_USE_NAMESPACE
class GameProgressBar : public DColoredProgressBar
{
    Q_OBJECT
public:
    explicit GameProgressBar(QWidget *parent = nullptr);
    void setInintalTime(int time); //初始化时间
protected:
    void paintEvent(QPaintEvent *e) override;
signals:

public slots:

private:
    qreal m_time = 0;
    QPixmap m_pic;
};

#endif // GAMEPROGRESSBAR_H
