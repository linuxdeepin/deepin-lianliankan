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
class GameButton : public QPushButton
{
    Q_OBJECT

public:
    explicit GameButton(const QPixmap &pic,const QString &text,QWidget *parent = nullptr);
    explicit GameButton(const QPixmap &pic,const QPixmap &icon,QWidget*parent=nullptr);
    explicit GameButton(const QPixmap &pic,QWidget*parent=nullptr);
    void setFont(const QFont &font); //设置字体
    void setLocation(int x, int y); //设置坐标
    void updatePic(const QPixmap &pic); //刷新按钮
    inline const QPoint location() const
    {
        return QPoint(m_rowIndex, m_columnIndex);
    }
    void setBtnMode(const GameBtnType &type); //设置按钮类型
    void setPressed(bool isPressd); //设置按下
    GameBtnType btnMode() const; //按钮类型
public slots:

protected:
   void paintEvent(QPaintEvent *event) override;
   void mousePressEvent(QMouseEvent *e) override;
   void mouseReleaseEvent(QMouseEvent *e) override;

   private:
   void drawRect(QPainter &p); //绘制阴影
   void drawBackdrop(QPainter &p); //绘制背景

   private:
   QPixmap m_pic;//按钮背景图
   QPixmap m_icon;//按钮图标
   QString m_text;//按钮文字
   QFont  m_font; //按钮字体
   int m_rowIndex; //行
   int m_columnIndex; //列
   bool m_gameBtnPressd = false; //判读游戏按钮是否点击
   bool m_cotrolBtnPressd = false; //判读控制按钮是否点击
   GameBtnType m_btnType; //按钮样式类型
};

#endif // GAMEBUTTON_H
