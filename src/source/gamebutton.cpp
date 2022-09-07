// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gamebutton.h"
#include "utils.h"
#include "gamecontrol.h"

#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>
#include <QMouseEvent>
#include <QtMath>

#define ICON_WIDTH 30
#define ICON_HEIGHT 30

GameButton::GameButton(const GameBtnFlag &flag, const GameBtnSize &size, const QString &text, QWidget *parent)
    : QPushButton(parent)
    , m_pic(GameControl::m_picMap.value(qMakePair(flag, size)))
    , m_iconType(None)
    , m_text(text)
    , m_size(size)
    , m_rowIndex(0)
    , m_columnIndex(0)
    , m_btnType(TextOnPic)
{
    setBtnMask(m_pic);
}

GameButton::GameButton(const QPixmap &pic, const GameIconType &icontype, QWidget *parent)
    : QPushButton(parent)
    , m_pic(pic)
    , m_iconType(icontype)
    , m_size(Small)
    , m_rowIndex(0)
    , m_columnIndex(0)
    , m_btnType(IconOnPic)
{
    loadIcon(m_iconType);
    setBtnMask(m_pic);
}

GameButton::GameButton(const QPixmap &pic, QWidget *parent)
    : QPushButton(parent)
    , m_pic(pic)
    , m_iconType(None)
    , m_size(Default)
    , m_rowIndex(0)
    , m_columnIndex(0)
    , m_btnType(OnlyPic)
{
}

void GameButton::setFont(const QFont &font)
{
    m_font = font;
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

void GameButton::updatePlayIcon(const GameBtnType &btntype, bool isStarted)
{
    if (btntype == GameCtl) {
        if (isStarted) {
            loadIcon(Pause);
        } else {
            loadIcon(Begin);
        }
    } else if (btntype == SoundCtl) {
        if (isStarted) {
            loadIcon(Sound);
        } else {
            loadIcon(Mute);
        }
    }
    update();
}

void GameButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    //绘制游戏页面控制按钮不可点击状态
    if (!this->isEnabled() && this->btnMode() == IconOnPic && (this->btnIconType() == Reset || this->btnIconType() == Hint)) {
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
    p.drawPixmap(rect(), m_pic);
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
        int iconX = (rect().width() - ICON_WIDTH) / 2;
        int iconY = (rect().height() - ICON_HEIGHT - ICON_HEIGHT / 2) / 2;
        p.drawPixmap(QRect(iconX, iconY, ICON_WIDTH, ICON_HEIGHT), m_icon);
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
        return;
    }

    if (hitButton(e->pos())) {
        if (m_btnType == OnlyPic) {
            m_gameBtnPressd = true;
        } else if (m_btnType == TextOnPic) {
            QPixmap pressPic = GameControl::m_picMap.value(qMakePair(ButtonPress, m_size));
            m_pic = pressPic;
        } else if (m_btnType == IconOnPic) {
            m_cotrolBtnPressd = true;
            QPixmap pressPic = GameControl::m_picMap.value(qMakePair(ButtonSPress, Small));
            m_pic = pressPic;
        }
    } else {
        if (m_btnType == OnlyPic) {
            m_gameBtnPressd = false;
        } else {
            m_cotrolBtnPressd = false;
        }
    }

    return QPushButton::mousePressEvent(e);
}

void GameButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnType == TextOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonHover, m_size));
        m_pic = normalPic;
    } else if (m_btnType == IconOnPic) {
        m_cotrolBtnPressd = false;
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonSHover, Small));
        m_pic = normalPic;
    }
    return QPushButton::mouseReleaseEvent(e);
}

void GameButton::enterEvent(QEvent *event)
{
    if (!this->isEnabled()) {
        return;
    }
    if (m_btnType == TextOnPic) {
        QPixmap hoverPic = GameControl::m_picMap.value(qMakePair(ButtonHover, m_size));
        m_pic = hoverPic;
    } else if (m_btnType == IconOnPic) {
        QPixmap hoverPic = GameControl::m_picMap.value(qMakePair(ButtonSHover, Small));
        m_pic = hoverPic;
    }

    return QPushButton::enterEvent(event);

}

void GameButton::leaveEvent(QEvent *event)
{
    if (m_btnType == TextOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonNormal, m_size));
        m_pic = normalPic;
    } else if (m_btnType == IconOnPic) {
        QPixmap normalPic = GameControl::m_picMap.value(qMakePair(ButtonSmall, Small));
        m_pic = normalPic;
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

GameIconType GameButton::btnIconType() const
{
    return m_iconType;
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

void GameButton::setBtnMask(QPixmap &pic)
{
    //设置控制按钮的蒙版,调整点击区域
    QSize scaledSize;
    QPixmap map;
    switch (m_size) {
    case Mid:
        scaledSize = QSize(200, 110);
        break;
    case Small:
        scaledSize = QSize(150, 85);
        break;
    case Over:
        scaledSize = QSize(180, 93);
        break;
    default:
        return;
    }
    map = pic.scaled(scaledSize);
    setMask(map.mask());
}

void GameButton::loadIcon(GameIconType iconType)
{
    if (!iconType) {
        return;
    }
    QSize IconSize(ICON_WIDTH, ICON_HEIGHT);
    switch (iconType) {
    case Sound:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/sound.svg", nullptr);
        break;
    case Mute:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/mute.svg", nullptr);
        break;
    case Begin:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/begin.svg", nullptr);
        break;
    case Pause:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/pause.svg", nullptr);
        break;
    case Reset:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/reset.svg", nullptr);
        break;
    case Hint:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/hint.svg", nullptr);
        break;
    default:
        m_icon = Utils::getDpiPixmap(IconSize, ":/assets/icon/home.svg", nullptr);
        break;
    }
}
