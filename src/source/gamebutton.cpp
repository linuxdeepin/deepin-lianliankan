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
#include "gamebutton.h"
#include "utils.h"
#include "gamecontrol.h"

#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>
#include <QMouseEvent>
#include <QtMath>

GameButton::GameButton(const GameBtnFlag &flag, const GameBtnSize &size, const QString &text, QWidget *parent)
    : QPushButton(parent)
    , m_text(text)
    , m_size(size)
    , m_btnType(TextOnPic)
{
    m_pic = GameControl::m_picMap.value(qMakePair(flag, size));
}

GameButton::GameButton(const QPixmap &pic, const QPixmap &icon, QWidget *parent)
    : QPushButton(parent)
    , m_pic(pic)
    , m_icon(icon)
    , m_btnType(IconOnPic)
{
}

GameButton::GameButton(const QPixmap &pic, QWidget *parent)
    : QPushButton(parent)
    , m_pic(pic)
    , m_btnType(OnlyPic)
{
}

void GameButton::setFont(const QFont &font)
{
    m_font=font;
}

void GameButton::setLocation(int x, int y)
{
    m_rowIndex = x;
    m_columnIndex = y;
}

void GameButton::setControlBtnPressed(bool pressed)
{
    m_cotrolBtnPressd = pressed;
}

void GameButton::updatePic(const QPixmap &pic)
{
    //更新按下状态
    m_gameBtnPressd = false;
    //更新图片资源
    m_pic = pic;
    update();
}

void GameButton::updatePlayIcon(bool isStarted)
{
    if (!isStarted) {
        m_icon = Utils::getDpiPixmap(QSize(0, 0), ":/assets/icon/play.svg", nullptr);
    } else {
        m_icon = Utils::getDpiPixmap(QSize(0, 0), ":/assets/icon/pause.svg", nullptr);
    }
    update();
}

void GameButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    //绘制游戏页面控制按钮不可点击状态
    if (!this->isEnabled() && this->btnMode() == IconOnPic) {
        //透明度设置为0.6
        p.setOpacity(0.6);
    }


    //消失的情况消失相匹配元素.
    if (m_btnType == NoneType) {
        drawBackdrop(p);
        return;
    }
    if (m_gameBtnPressd) {
        drawRect(p);
    }
    p.drawPixmap(rect(),m_pic);
    switch (m_btnType) {
    case TextOnPic: {
        //绘制文字按钮
        //阴影字体
        QFont shadowFont;
        shadowFont.setFamily("Noto Sans CJK SC");
        shadowFont.setWeight(QFont::DemiBold);
        shadowFont.setPointSize(m_font.pointSize());
        QColor shadowColor(0, 0, 0);
        shadowColor.setAlphaF(0.50);

        QFontMetricsF mertic(m_font);
        qreal fontHeight = mertic.height();
        qreal fontWidth = mertic.width(m_text);
        qreal textX = (rect().width() - fontWidth) / 2;
        qreal textY = (rect().height() - fontHeight - fontHeight / 2) / 2;
        p.setFont(shadowFont);
        p.setPen(shadowColor);
        //绘制阴影字体
        p.drawText(QRectF(textX, textY + 2, fontWidth, fontHeight), m_text);
        p.setFont(m_font);
        p.setPen(QColor("#FFFFFF"));
        p.drawText(QRectF(textX, textY, fontWidth, fontHeight), m_text);
        break;
    }
    case IconOnPic: {
        //绘制游戏控制按钮
        int iconHeight = m_icon.height();
        int iconWidth = m_icon.width();
        int iconX = (rect().width() - iconWidth) / 2;
        int iconY = (rect().height() - iconHeight - iconHeight / 2) / 2;
        p.drawPixmap(QRect(iconX, iconY, iconWidth, iconHeight), m_icon);
        break;
    }
    default: {
        //绘制背景
        drawBackdrop(p);
        break;
    }
    }
}

void GameButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }

    if (hitButton(e->pos())) {
        if (m_btnType == OnlyPic) {
            m_gameBtnPressd = true;
        } else if (m_btnType == TextOnPic){
            QPixmap pressPic = GameControl::m_picMap.value(qMakePair(ButtonPress, m_size));
            m_pic = pressPic;
        } else if (m_btnType == IconOnPic) {
            m_cotrolBtnPressd = true;
            QPixmap pressPic = GameControl::m_picMap.value(qMakePair(ButtonPress, Small));
            m_pic = pressPic;
        }
        e->accept();
    } else {
        if (m_btnType == OnlyPic) {
            m_gameBtnPressd = false;
        } else {
            m_cotrolBtnPressd = false;
        }
        e->ignore();
    }

    return QPushButton::mousePressEvent(e);
}

void GameButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnType == TextOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonHover, m_size));
        m_pic = normalPic;
    }else if (m_btnType == IconOnPic) {
        m_cotrolBtnPressd = false;
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonHover, Small));
        m_pic = normalPic;
    } else if (m_btnType == OnlyPic){
        m_gameBtnPressd = true;
    }
    return QPushButton::mouseReleaseEvent(e);
}

void GameButton::enterEvent(QEvent *event)
{
    if (m_btnType == TextOnPic) {
        QPixmap hoverPic = GameControl::m_picMap.value(qMakePair(ButtonHover, m_size));
        m_pic = hoverPic;
    }else if (m_btnType == IconOnPic) {
        QPixmap hoverPic = GameControl::m_picMap.value(qMakePair(ButtonHover, Small));
        m_pic = hoverPic;
    } else if (m_btnType == OnlyPic){
        event->ignore();
    }
    return QWidget::enterEvent(event);

}

void GameButton::leaveEvent(QEvent *event)
{
    if (m_btnType == TextOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonNormal, m_size));
        m_pic = normalPic;
    }else if (m_btnType == IconOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonNormal, Small));
        m_pic = normalPic;
    } else if (m_btnType == OnlyPic){
        event->ignore();
    }
    return QWidget::leaveEvent(event);
}

void GameButton::setBtnMode(const GameBtnType &type)
{
    m_btnType = type;
    update();
}

void GameButton::setPressed(bool isPressd)
{
    m_gameBtnPressd = isPressd;
    update();
}

GameBtnType GameButton::btnMode() const
{
    return m_btnType;
}

void GameButton::drawRect(QPainter &p)
{
    int rectX = rect().x();
    int rectY = rect().y();
    QPixmap pic = GameControl::m_picMap.value(qMakePair(checkeffect, Default));

    p.drawPixmap(rectX - 6, rectY - 5, pic);

}

void GameButton::drawBackdrop(QPainter &p)
{
    QColor bgColor("#386635");
    p.setBrush(bgColor);
    p.setOpacity(0.15);
    QPen pen;
    pen.setWidth(0);
    p.setPen(pen);
    p.drawRoundRect(this->rect().x() + 3, this->rect().y() + 5, 42, 42, 40, 40);
}
