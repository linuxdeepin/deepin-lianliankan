// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"
#include <DPushButton>

DWIDGET_USE_NAMESPACE
class GameButton : public QPushButton
{
    Q_OBJECT

public:
    explicit GameButton(const GameBtnFlag &flag, const GameBtnSize &size, const QString &text,QWidget *parent = nullptr);
    explicit GameButton(const QPixmap &pic,const GameIconType &icontype,QWidget*parent=nullptr);
    explicit GameButton(const QPixmap &pic,QWidget*parent=nullptr);

    /**
    * @brief GameButton::setFont 设置字体按钮的字体
    * @param font 具体字体
    */
    void setFont(const QFont &font);
    /**
    * @brief GameButton::setLocation 记录按钮行列
    * @param x 行
    * @param y 列
    */
    void setLocation(int x, int y);
    /**
    * @brief GameButton::setControlBtnPressed 设置游戏控制按钮是否按下
    * @param pressed 按下状态
    */
    void setControlBtnPressed(bool pressed);
    /**
    * @brief GameButton::setPressed 设置游戏按钮是否按下
    * @param pressed 按下状态
    */
    void setPressed(bool isPressd);
    /**
    * @brief GameButton::setBtnMode 设置按钮类型
    * @param type 按钮类型
    */
    void setBtnMode(const GameBtnType &type);
    /**
    * @brief GameButton:: updatePic 更新游戏背景图片
    * @param pic 图片
    */
    void updatePic(const QPixmap &pic);
    /**
    * @brief GameButton:: updatePlayIcon 更新游戏控制按钮开始暂停图标
    * @param isStarted 是否为开始状态
    */
    void updatePlayIcon(const GameBtnType &btntype, bool isStarted);
    /**
    * @brief GameButton:: location 获取游戏按钮行列
    * @return QPoint 按钮行列
    */
    inline const QPoint location() const
    {
        return QPoint(m_rowIndex, m_columnIndex);
    }
    /**
    * @brief GameButton:: btnMode 获取游戏按钮类型
    * @return GameBtnType 按钮类型
    */
    GameBtnType btnMode() const;
    /**
     * @brief btnIconType 获取按钮图标类型
     * @return GameIconType 按钮图标类型
     */
    GameIconType btnIconType() const;

protected:
   void paintEvent(QPaintEvent *event) override;
   void mousePressEvent(QMouseEvent *e) override;
   void mouseReleaseEvent(QMouseEvent *e) override;
   void enterEvent(QEvent *event) override;
   void leaveEvent(QEvent *event) override;

   private:
   /**
   * @brief GameButton:: drawRect 绘制游戏按钮选中阴影
   */
   void drawRect(QPainter &p);
   /**
   * @brief GameButton:: drawBackdrop 绘制游戏按钮背景
   */
   void drawBackdrop(QPainter &p);
   /**
   * @brief GameButton:: setBtnMask 设置按钮蒙版
   */
   void setBtnMask(QPixmap &pic);
   /**
    * @brief loadIcon 加载按钮图标
    * @param iconType 按钮图标类型
    */
   void loadIcon(GameIconType iconType);

   private:
   QPixmap m_pic;//按钮背景图
   QPixmap m_icon;//按钮图标
   GameIconType m_iconType = None; //按钮图标类型
   QString m_text;//按钮文字
   QFont  m_font; //按钮字体
   GameBtnSize m_size = Default; //按钮大小
   int m_rowIndex = 0; //行
   int m_columnIndex = 0; //列
   bool m_gameBtnPressd = false; //判读游戏按钮是否点击
   bool m_cotrolBtnPressd = false; //判读控制按钮是否点击
   GameBtnType m_btnType; //按钮样式类型
};

#endif // GAMEBUTTON_H
