// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <gamebutton.h>

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

class UT_GameButton : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_btn = new GameButton(ButtonNormal, Default, "test");
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_btn) {
            delete m_btn;
            m_btn = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
    GameButton *m_btn;
};

TEST_F(UT_GameButton, UT_GameButton_Constructor_001)
{
    QPixmap pic;
    GameButton *btn = new GameButton(pic, Sound);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_Constructor_001()";
    EXPECT_NE(btn, nullptr) << "check the status after UT_GameButton_Constructor_001()";
    EXPECT_EQ(btn->m_iconType, Sound) << "check the status after UUT_GameButton_Constructor_001()";
    btn->deleteLater();
}

TEST_F(UT_GameButton, UT_GameButton_Constructor_002)
{
    QPixmap pic;
    GameButton *btn = new GameButton(pic);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_Constructor_001()";
    EXPECT_NE(btn, nullptr) << "check the status after UT_GameButton_Constructor_001()";
    btn->deleteLater();
}

TEST_F(UT_GameButton, UT_GameButton_setFont)
{
    QFont font;
    font.setPointSize(10);
    font.setItalic(true);
    m_btn->setFont(font);
    EXPECT_EQ(m_btn->m_font.pointSize(), 10) << "check the status after UT_GameButton_setFont()";
    EXPECT_EQ(m_btn->m_font.italic(), true) << "check the status after UT_GameButton_setFont()";
}

TEST_F(UT_GameButton, UT_GameButton_setLocation)
{
    m_btn->setLocation(1, 1);
    EXPECT_EQ(m_btn->m_rowIndex, 1) << "check the status after UT_GameButton_setLocation()";
    EXPECT_EQ(m_btn->m_columnIndex, 1) << "check the status after UT_GameButton_setLocation()";
}

TEST_F(UT_GameButton, UT_GameButton_setControlBtnPressed)
{
    m_btn->setControlBtnPressed(true);
    EXPECT_EQ(m_btn->m_cotrolBtnPressd, true) << "check the status after UT_GameButton_setControlBtnPressed()";
}

TEST_F(UT_GameButton, UT_GameButton_setPressed)
{
    m_btn->setPressed(true);
    EXPECT_EQ(m_btn->m_gameBtnPressd, true) << "check the status after UT_GameButton_setPressed()";
}

TEST_F(UT_GameButton, UT_GameButton_setBtnMode)
{
    m_btn->setBtnMode(TextOnPic);
    EXPECT_EQ(m_btn->m_btnType, TextOnPic) << "check the status after UT_GameButton_setBtnMode()";
}

TEST_F(UT_GameButton, UT_GameButton_updatePic)
{
    QPixmap pic;
    m_btn->updatePic(pic);
    EXPECT_EQ(m_btn->m_pic, pic) << "check the status after UT_GameButton_updatePic()";
    EXPECT_EQ(m_btn->m_gameBtnPressd, false) << "check the status after UT_GameButton_updatePic()";
}

TEST_F(UT_GameButton, UT_GameButton_updatePlayIcon)
{
    QPixmap pic;
    m_btn->updatePlayIcon(GameCtl, true);
    m_btn->updatePlayIcon(GameCtl, false);
    m_btn->updatePlayIcon(SoundCtl, true);
    m_btn->updatePlayIcon(SoundCtl, false);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_updatePlayIcon()";
}

TEST_F(UT_GameButton, UT_GameButton_location)
{
    QPixmap pic;
    m_btn->m_rowIndex = 1;
    m_btn->m_columnIndex = 1;
    QPoint res = m_btn->location();
    EXPECT_EQ(res, QPoint(1, 1)) << "check the status after UT_GameButton_location()";
}

TEST_F(UT_GameButton, UT_GameButton_btnMode)
{
    m_btn->m_btnType = TextOnPic;
    GameBtnType type = m_btn->btnMode();
    EXPECT_EQ(type, TextOnPic) << "check the status after UT_GameButton_btnMode()";
}

TEST_F(UT_GameButton, UT_GameButton_btnIconType)
{
    m_btn->m_iconType = Sound;
    GameIconType type = m_btn->btnIconType();
    EXPECT_EQ(type, Sound) << "check the status after UT_GameButton_btnIconType()";
}

TEST_F(UT_GameButton, UT_GameButton_drawRect)
{
    QPainter p(m_btn);
    m_btn->drawRect(p);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_drawRect()";
}

TEST_F(UT_GameButton, UT_GameButton_drawBackdrop)
{
    QPainter p(m_btn);
    m_btn->drawBackdrop(p);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_drawBackdrop()";
}

TEST_F(UT_GameButton, UT_GameButton_setBtnMask)
{
    QPixmap pic;
    m_btn->m_size = Mid;
    m_btn->setBtnMask(pic);
    m_btn->m_size = Small;
    m_btn->setBtnMask(pic);
    m_btn->m_size = Over;
    m_btn->setBtnMask(pic);
    m_btn->m_size = Default;
    m_btn->setBtnMask(pic);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_setBtnMask()";
}

TEST_F(UT_GameButton, UT_GameButton_loadIcon)
{
    m_btn->loadIcon(Sound);
    m_btn->loadIcon(Mute);
    m_btn->loadIcon(Begin);
    m_btn->loadIcon(Pause);
    m_btn->loadIcon(Reset);
    m_btn->loadIcon(Hint);
    m_btn->loadIcon(Home);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_loadIcon()";
}

TEST_F(UT_GameButton, UT_GameButton_paintEvent)
{
    QPaintEvent event(m_btn->rect());
    m_btn->m_gameBtnPressd = true;
    m_btn->m_btnType = TextOnPic;
    m_btn->paintEvent(&event);
    m_btn->setEnabled(false);
    m_btn->setBtnMode(IconOnPic);
    m_btn->m_iconType = Hint;
    m_btn->paintEvent(&event);
    m_btn->m_btnType = OnlyPic;
    m_btn->paintEvent(&event);
    m_btn->m_btnType = NoneType;
    m_btn->paintEvent(&event);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_paintEvent()";
}

TEST_F(UT_GameButton, UT_GameButton_mousePressEvent)
{
    QMouseEvent rightBtnEvent(QEvent::MouseButtonPress, QPointF(m_btn->x(), m_btn->y()), Qt::RightButton, Qt::RightButton, Qt::NoModifier);
    m_btn->mousePressEvent(&rightBtnEvent);

    QMouseEvent leftBtnEvent(QEvent::MouseButtonPress, QPointF(m_btn->x(), m_btn->y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_btn->m_btnType = TextOnPic;
    m_btn->mousePressEvent(&leftBtnEvent);
    m_btn->m_btnType = IconOnPic;
    m_btn->mousePressEvent(&leftBtnEvent);
    m_btn->m_btnType = OnlyPic;
    m_btn->mousePressEvent(&leftBtnEvent);
    leftBtnEvent.setLocalPos(QPointF(1000, 1000));
    m_btn->mousePressEvent(&leftBtnEvent);
    m_btn->m_btnType = IconOnPic;
    m_btn->mousePressEvent(&leftBtnEvent);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_mousePressEvent()";
}

TEST_F(UT_GameButton, UT_GameButton_mouseReleaseEvent)
{
    QMouseEvent releaseEvent(QEvent::MouseButtonRelease, QPointF(m_btn->x(), m_btn->y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_btn->m_btnType = TextOnPic;
    m_btn->mouseReleaseEvent(&releaseEvent);
    m_btn->m_btnType = IconOnPic;
    m_btn->mouseReleaseEvent(&releaseEvent);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_mouseReleaseEvent()";
}

TEST_F(UT_GameButton, UT_GameButton_enterEvent)
{
    QEvent enterEvent(QEvent::Enter);
    m_btn->m_btnType = OnlyPic;
    m_btn->enterEvent(&enterEvent);
    m_btn->m_btnType = TextOnPic;
    m_btn->enterEvent(&enterEvent);
    m_btn->m_btnType = IconOnPic;
    m_btn->enterEvent(&enterEvent);
    m_btn->setEnabled(false);
    m_btn->enterEvent(&enterEvent);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_enterEvent()";
}

TEST_F(UT_GameButton, UT_GameButton_leaveEvent)
{
    QEvent leaveEvent(QEvent::Leave);
    m_btn->m_btnType = OnlyPic;
    m_btn->leaveEvent(&leaveEvent);
    m_btn->m_btnType = TextOnPic;
    m_btn->leaveEvent(&leaveEvent);
    m_btn->m_btnType = IconOnPic;
    m_btn->leaveEvent(&leaveEvent);
    EXPECT_NE(m_btn, nullptr) << "check the status after UT_GameButton_leaveEvent()";
}
