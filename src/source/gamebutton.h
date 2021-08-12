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
#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"
#include <DPushButton>

DWIDGET_USE_NAMESPACE
class GameButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit GameButton(const QPixmap &pic,const QString &text,QWidget *parent = nullptr);
    explicit GameButton(const QPixmap &pic,const QPixmap &icon,QWidget*parent=nullptr);
    explicit GameButton(const QPixmap &pic,QWidget*parent=nullptr);
    void setFont(const QFont &font);
    void setLocation(int x, int y);
signals:

public slots:

protected:
   void paintEvent(QPaintEvent *event) override;
private:
   void initUI();
   void initIcon(GameBtnFlag flag);
private:
   QPixmap m_pic;//按钮背景图
   QPixmap m_icon;//按钮图标
   QString m_text;//按钮文字
   QFont  m_font; //按钮字体
   int m_rowIndex; //行
   int m_columnIndex; //列
};

#endif // GAMEBUTTON_H
