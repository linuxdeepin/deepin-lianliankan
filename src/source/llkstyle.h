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
#ifndef LLKSTYLE_H
#define LLKSTYLE_H

#include <QCommonStyle>
#include <DStyle>

DWIDGET_USE_NAMESPACE
class LLKStyle : public DStyle
{
    Q_OBJECT
public:
    explicit LLKStyle();
protected:
    void drawControl(QStyle::ControlElement element, const QStyleOption *opt, QPainter *p,
                     const QWidget *w = nullptr) const override;
signals:

public slots:
};

#endif // LLKSTYLE_H
