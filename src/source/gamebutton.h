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
#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"
#include <DPushButton>

DWIDGET_USE_NAMESPACE
class GameButton : public DPushButton
{
    Q_OBJECT
public:
    explicit GameButton(const QIcon &icon,const QString &text="",QWidget *parent = nullptr);
signals:

public slots:

protected:
   void paintEvent(QPaintEvent *event) override;
   void initStyleOption(QStyleOptionButton *option) const;
private:
   void initIcon(GameBtnFlag flag);
private:
   QIcon m_icon;//按钮图标
   QString m_text;//按钮文字
};

#endif // GAMEBUTTON_H
