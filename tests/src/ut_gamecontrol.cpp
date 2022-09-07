// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <gamecontrol.h>

#include <QDebug>

bool UT_GameControl_gameBfsFalse(bool isOveride, const QPoint &startPos, const QPoint &endPos)
{
    Q_UNUSED(isOveride);
    Q_UNUSED(startPos);
    Q_UNUSED(endPos);
    return false;
}

bool UT_GameControl_gameBfsTrue(bool isOveride, const QPoint &startPos, const QPoint &endPos)
{
    Q_UNUSED(isOveride);
    Q_UNUSED(startPos);
    Q_UNUSED(endPos);
    return true;
}

class UT_GameControl : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        qInfo() << "TearDown" << endl;
    }
};

TEST_F(UT_GameControl, UT_GameControl_GameInterFace)
{
    GameControl::GameInterFace();
    EXPECT_NE(&GameControl::GameInterFace(), nullptr) << "check the status after UT_GameControl_GameInterFace()";
}

TEST_F(UT_GameControl, UT_GameControl_loadPic)
{
    GameControl::GameInterFace().loadPic(ButtonNormal, Big, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 1) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonCow, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 2) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonTiger, Small, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 3) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonRabbit, Over, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 4) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonSnake, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 5) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonHorse, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 6) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonSheep, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 7) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonDog, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 8) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonPig, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 9) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonCat, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 10) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonLion, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 11) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonFox, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 12) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonPanda, Default, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 13) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(MainBack, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 14) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonHorse, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 15) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonPress, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 16) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonSmall, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 17) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonSHover, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 18) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(ButtonSPress, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 19) << "check the status after UT_GameControl_loadPic()";
    GameControl::GameInterFace().loadPic(checkeffect, Mid, nullptr);
    EXPECT_EQ(GameControl::m_picMap.count(), 20) << "check the status after UT_GameControl_loadPic()";
}

TEST_F(UT_GameControl, UT_GameControl_gameBegin)
{
    GameControl::GameInterFace().gameBegin();
}

TEST_F(UT_GameControl, UT_GameControl_gameReset)
{
    GameControl::GameInterFace().gameReset();
}

TEST_F(UT_GameControl, UT_GameControl_gameJudge)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameBfs), UT_GameControl_gameBfsTrue);
    QPair<bool, QList<QPoint>> res = GameControl::GameInterFace().gameJudge();
    EXPECT_NE(res.second.count(), 0) << "check the status after UT_GameControl_gameJudge()";
    EXPECT_EQ(res.first, true) << "check the status after UT_GameControl_gameJudge()";
}

TEST_F(UT_GameControl, UT_GameControl_gameSearch001)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameBfs), UT_GameControl_gameBfsFalse);
    GameSearchResult res = GameControl::GameInterFace().gameSearch(QPoint(1, 1), QPoint(1, 2));
    EXPECT_EQ(res, FAIL) << "check the status after UT_GameControl_gameSearch001()";
}

TEST_F(UT_GameControl, UT_GameControl_gameSearch002)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameBfs), UT_GameControl_gameBfsTrue);
    GameSearchResult res = GameControl::GameInterFace().gameSearch(QPoint(1, 1), QPoint(1, 2));
    EXPECT_EQ(res, PositiveSuccess) << "check the status after UT_GameControl_gameSearch002()";
}

TEST_F(UT_GameControl, UT_GameControl_gameJudgeVictory)
{
    bool res = GameControl::GameInterFace().gameJudgeVictory();
    EXPECT_EQ(res, false) << "check the status after UT_GameControl_gameJudgeVictory()";
}

TEST_F(UT_GameControl, UT_GameControl_Constructor)
{
    GameControl *control = new GameControl();
    EXPECT_NE(control, nullptr) << "check the status after UT_GameControl_Constructor()";
    control->deleteLater();
}

TEST_F(UT_GameControl, UT_GameControl_gameShuffle)
{
    GameControl::GameInterFace().gameShuffle(true);
    GameControl::GameInterFace().gameShuffle(false);
    EXPECT_NE(sizeof(GameControl::m_map), 0) << "check the status after UT_GameControl_gameShuffle()";
}

TEST_F(UT_GameControl, UT_GameControl_gameBfs001)
{
    GameControl::m_map[1][1] = ButtonTiger;
    GameControl::m_map[1][2] = ButtonTiger;
    bool res = GameControl::GameInterFace().gameBfs(false, QPoint(1, 1), QPoint(1, 2));
    bool resOveride = GameControl::GameInterFace().gameBfs(true, QPoint(1, 1), QPoint(1, 2));
    EXPECT_EQ(res, true) << "check the status after UT_GameControl_gameBfs001()";
    EXPECT_EQ(resOveride, true) << "check the status after UT_GameControl_gameBfs001()";
}

TEST_F(UT_GameControl, UT_GameControl_gameBfs002)
{
    GameControl::m_map[1][1] = ButtonTiger;
    GameControl::m_map[1][2] = ButtonLion;
    bool res = GameControl::GameInterFace().gameBfs(false, QPoint(1, 1), QPoint(1, 2));
    bool resOveride = GameControl::GameInterFace().gameBfs(true, QPoint(1, 1), QPoint(1, 2));
    EXPECT_EQ(res, false) << "check the status after UT_GameControl_gameBfs002()";
    EXPECT_EQ(resOveride, false) << "check the status after UT_GameControl_gameBfs002()";
}

class UT_BtnFactory : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        qInfo() << "TearDown" << endl;
    }
};

TEST_F(UT_BtnFactory, UT_GameControl_createBtn)
{
    GameButton *textBtn = BtnFactory::createBtn(ButtonNormal, Big, None, "test", nullptr);
    EXPECT_NE(textBtn, nullptr) << "check the status after UT_GameControl_createBtn()";
    GameButton *iconBtn = BtnFactory::createBtn(ButtonNormal, Small, Sound, "", nullptr);
    EXPECT_NE(iconBtn, nullptr) << "check the status after UT_GameControl_createBtn()";
    GameButton *animalBtn = BtnFactory::createBtn(ButtonCow, Mid, None, "", nullptr);
    EXPECT_NE(animalBtn, nullptr) << "check the status after UT_GameControl_createBtn()";
    GameButton *overBtn = BtnFactory::createBtn(ButtonPress, Over, None, "", nullptr);
    EXPECT_NE(overBtn, nullptr) << "check the status after UT_GameControl_createBtn()";
}
