// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <gamepage.h>
#include <mainwindow.h>
#include <gamecontrol.h>
#include <closewindowdialog.h>
#include <gamelinescene.h>
#include <gamebutton.h>

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QEventLoop>
#include <QTimer>
#include <QMessageBox>

int UT_GamePage_Exec(QEventLoop::ProcessEventsFlags flag)
{
    Q_UNUSED(flag);
    return 0;
}

bool UT_GamePage_judgeVictoryTrue()
{
    return true;
}

bool UT_GamePage_judgeVictoryFalse()
{
    return false;
}

int UT_GamePage_resultOk()
{
    return QMessageBox::Ok;
}

int UT_GamePage_resultNo()
{
    return QMessageBox::No;
}

QPair<bool, QList<QPoint>> UT_GamePage_gameJudge()
{
    QList<QPoint> pointList;
    pointList.append(QPoint(1, 1));
    pointList.append(QPoint(1, 2));
    return qMakePair(true, pointList);
}

class UT_GamePage : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_window = new MainWindow;
        m_gamePage = new GamePage(m_window->m_stackedWidget);
        Stub stub;
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_gamePage && m_window) {
            delete m_gamePage;
            delete m_window;
            m_gamePage = nullptr;
            m_window = nullptr;
        }

        qInfo() << "TearDown" << endl;
    }
    GamePage *m_gamePage;
    MainWindow *m_window;
};

TEST_F(UT_GamePage, UT_GamePage_setInitalTime)
{
    m_gamePage->setInitalTime(100);
    EXPECT_EQ(m_gamePage->m_value, 100) << "check the status after UT_GamePage_setInitalTime()";
    EXPECT_EQ(m_gamePage->m_progress->value(), 100) << "check the status after UT_GamePage_setInitalTime()";
}

TEST_F(UT_GamePage, UT_GamePage_setSoundSwitch)
{
    m_gamePage->setSoundSwitch(true);
    EXPECT_EQ(m_gamePage->m_soundSwitch, true) << "check the status after UT_GamePage_setSoundSwitch()";
}

TEST_F(UT_GamePage, UT_GamePage_setOnOffGame)
{
    m_gamePage->setOnOffGame(true);
    EXPECT_EQ(m_gamePage->m_isStart, true) << "check the status after UT_GamePage_setOnOffGame()";
    EXPECT_EQ(m_gamePage->m_gameFrame->isEnabled(), true) << "check the status after UT_GamePage_setOnOffGame()";
    EXPECT_EQ(m_gamePage->m_timer->isActive(), true) << "check the status after UT_GamePage_setOnOffGame()";
    m_gamePage->setOnOffGame(false);
    EXPECT_EQ(m_gamePage->m_isStart, false) << "check the status after UT_GamePage_setOnOffGame()";
    EXPECT_EQ(m_gamePage->m_gameFrame->isEnabled(), false) << "check the status after UT_GamePage_setOnOffGame()";
    EXPECT_EQ(m_gamePage->m_timer->isActive(), false) << "check the status after UT_GamePage_setOnOffGame()";
}

TEST_F(UT_GamePage, UT_GamePage_onOffGame)
{
    m_gamePage->setOnOffGame(true);
    bool res = m_gamePage->onOffGame();
    EXPECT_EQ(res, true) << "check the status after UT_GamePage_onOffGame()";
}

TEST_F(UT_GamePage, UT_GamePage_restartGame)
{
    m_gamePage->restartGame(true);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_restartGame()";
    m_gamePage->restartGame(false);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_restartGame()";
}

TEST_F(UT_GamePage, UT_GamePage_onControlBtnControl)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    m_gamePage->setOnOffGame(true);
    m_gamePage->onControlBtnControl(0);
    EXPECT_EQ(m_gamePage->onOffGame(), false) << "check the status after UT_GamePage_onControlBtnControl()";
    m_gamePage->setOnOffGame(false);
    m_gamePage->onControlBtnControl(0);
    EXPECT_EQ(m_gamePage->onOffGame(), true) << "check the status after UT_GamePage_onControlBtnControl()";
    m_gamePage->onControlBtnControl(1);
    m_gamePage->onControlBtnControl(2);
    m_gamePage->onControlBtnControl(3);
    m_gamePage->m_gameStart = true;
    m_gamePage->onControlBtnControl(-1);
    m_gamePage->m_gameStart = false;
    m_gamePage->onControlBtnControl(-1);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_onControlBtnControl()";
}

TEST_F(UT_GamePage, UT_GamePage_onAnimalBtnControl)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    GameButton *firstBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    GameButton *secondBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    GameButton *thirdBtn = BtnFactory::createBtn(ButtonLion, Default, None, "", nullptr);
    GameButton *testBtn = nullptr;
    m_gamePage->onAnimalBtnControl(testBtn);
    m_gamePage->m_locationVec.clear();
    m_gamePage->m_locationVec.append(firstBtn);
    m_gamePage->onAnimalBtnControl(secondBtn);
    m_gamePage->onAnimalBtnControl(thirdBtn);
    EXPECT_EQ(m_gamePage->m_locationVec.count(), 1) << "check the status after UT_GamePage_onAnimalBtnControl()";
    m_gamePage->m_locationVec.append(thirdBtn);
    m_gamePage->onAnimalBtnControl(secondBtn);
    EXPECT_EQ(m_gamePage->m_locationVec.count(), 3) << "check the status after UT_GamePage_onAnimalBtnControl()";
}

TEST_F(UT_GamePage, UT_GamePage_onProgressChanged)
{
    m_gamePage->onProgressChanged(0);
    EXPECT_EQ(m_gamePage->m_isStart, false) << "check the status after UT_GamePage_onProgressChanged()";
}

TEST_F(UT_GamePage, UT_GamePage_reGame)
{
    m_gamePage->reGame();
    EXPECT_EQ(m_gamePage->m_value, m_gamePage->m_timeRecord) << "check the status after UT_GamePage_reGame()";
}

TEST_F(UT_GamePage, UT_GamePage_initUI)
{
    m_gamePage->initUI();
    EXPECT_EQ(m_gamePage->m_controlGrp->buttons().count(), 5) << "check the status after UT_GamePage_initUI()";
    EXPECT_NE(m_gamePage->m_progress, nullptr) << "check the status after UT_GamePage_initUI()";
    EXPECT_NE(m_gamePage->m_drawScene, nullptr) << "check the status after UT_GamePage_initUI()";
}

TEST_F(UT_GamePage, UT_GamePage_initConnect)
{
    m_gamePage->initConnect();
    EXPECT_EQ(m_gamePage->m_controlGrp->buttons().count(), 5) << "check the status after UT_GamePage_initConnect()";
    EXPECT_NE(m_gamePage->m_progress, nullptr) << "check the status after UT_GamePage_initConnect()";
}

TEST_F(UT_GamePage, UT_GamePage_initGameBtn)
{
    m_gamePage->initGameBtn();
    EXPECT_EQ(m_gamePage->m_animalGrp->buttons().count(), 320) << "check the status after UT_GamePage_initGameBtn()";
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_initGameBtn()";
}

TEST_F(UT_GamePage, UT_GamePage_resetGame)
{
    m_gamePage->resetGame();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_resetGame()";
    EXPECT_EQ(m_gamePage->m_hintPicOnTimer->isActive(), false) << "check the status after UT_GamePage_resetGame()";
    EXPECT_EQ(m_gamePage->m_hintPicOffTimer->isActive(), false) << "check the status after UT_GamePage_resetGame()";
}

TEST_F(UT_GamePage, UT_GamePage_hintGame)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    GameButton *firstBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    GameButton *secondBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    firstBtn->setLocation(1, 1);
    secondBtn->setLocation(1, 2);
    m_gamePage->m_locationVec.append(firstBtn);
    m_gamePage->m_locationVec.append(secondBtn);
    m_gamePage->hintGame();
    EXPECT_EQ(m_gamePage->m_animalGrp->buttons().count(), 160) << "check the status after UT_GamePage_hintGame()";
    EXPECT_EQ(m_gamePage->m_hintPicOnTimer->isActive(), true) << "check the status after UT_GamePage_hintGame()";
    EXPECT_EQ(m_gamePage->m_flashCount, 3) << "check the status after UT_GamePage_hintGame()";
    EXPECT_NE(m_gamePage->m_hintBtn.count(), 0) << "check the status after UT_GamePage_hintGame()";
}

TEST_F(UT_GamePage, UT_GamePage_shadowBtn)
{
    GameButton *firstBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    m_gamePage->shadowBtn(firstBtn);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_shadowBtn()";
}

TEST_F(UT_GamePage, UT_GamePage_updateBtn)
{
    m_gamePage->updateBtn();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_shadowBtn()";
}

TEST_F(UT_GamePage, UT_GamePage_successAction001)
{
    Stub stub;
    stub.set(ADDR(GamePage, judgeVictory), UT_GamePage_judgeVictoryTrue);
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    GameControl::m_pathMap[1][2] = QPoint(1, 1);
    m_gamePage->m_soundSwitch = true;
    m_gamePage->hintGame();
    m_gamePage->successAction(m_gamePage->m_hintBtn.at(0), m_gamePage->m_hintBtn.at(1));
    EXPECT_EQ(m_gamePage->m_locationVec.count(), 0) << "check the status after UT_GamePage_successAction001()";
    EXPECT_EQ(m_gamePage->m_pathVec.count(), 0) << "check the status after UT_GamePage_successAction001()";
}

TEST_F(UT_GamePage, UT_GamePage_successAction002)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    stub.set(ADDR(GamePage, judgeVictory), UT_GamePage_judgeVictoryFalse);
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    GameControl::m_pathMap[1][2] = QPoint(1, 1);
    m_gamePage->m_soundSwitch = true;
    m_gamePage->hintGame();
    m_gamePage->successAction(m_gamePage->m_hintBtn.at(0), m_gamePage->m_hintBtn.at(1));
    EXPECT_EQ(m_gamePage->m_locationVec.count(), 0) << "check the status after UT_GamePage_successAction002()";
    EXPECT_EQ(m_gamePage->m_pathVec.count(), 0) << "check the status after UT_GamePage_successAction002()";
}

TEST_F(UT_GamePage, UT_GamePage_failedAction)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    m_gamePage->m_soundSwitch = true;
    m_gamePage->hintGame();
    m_gamePage->failedAction(m_gamePage->m_hintBtn.at(0), m_gamePage->m_hintBtn.at(1));
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_failedAction()";
    EXPECT_EQ(m_gamePage->m_locationVec.count(), 0) << "check the status after UT_GamePage_failedAction()";
}

TEST_F(UT_GamePage, UT_GamePage_popDialog001)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    stub.set(ADDR(CloseWindowDialog, result), UT_GamePage_resultOk);
    m_gamePage->popDialog();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_popDialog001()";
}

TEST_F(UT_GamePage, UT_GamePage_popDialog002)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    stub.set(ADDR(CloseWindowDialog, result), UT_GamePage_resultNo);
    m_gamePage->popDialog();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_popDialog002()";
}

TEST_F(UT_GamePage, UT_GamePage_updateConnection)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UT_GamePage_Exec);
    GameButton *firstBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    GameButton *secondBtn = BtnFactory::createBtn(ButtonCow, Default, None, "", nullptr);
    firstBtn->setLocation(1, 1);
    secondBtn->setLocation(2, 3);
    m_gamePage->updateConnection(firstBtn, secondBtn);
    EXPECT_EQ(m_gamePage->m_pathVec.count(), 0) << "check the status after UT_GamePage_updateConnection()";
    m_gamePage->m_pathVec.append(qMakePair(DIR_DOWN, QPoint(1, 1)));
    m_gamePage->m_pathVec.append(qMakePair(DIR_RIGHT, QPoint(2, 1)));
    m_gamePage->m_pathVec.append(qMakePair(DIR_DOWN, QPoint(2, 2)));
    m_gamePage->m_pathVec.append(qMakePair(DIR_DOWN, QPoint(2, 3)));
    m_gamePage->updateConnection(firstBtn, secondBtn);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_updateConnection()";
    EXPECT_NE(m_gamePage->m_drawScene->m_posList.count(), 0) << "check the status after UT_GamePage_updateConnection()";
    m_gamePage->m_pathVec.clear();
    m_gamePage->m_pathVec.append(qMakePair(DIR_DOWN, QPoint(1, 1)));
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_updateConnection()";
    EXPECT_NE(m_gamePage->m_drawScene->m_posList.count(), 0) << "check the status after UT_GamePage_updateConnection()";
}

TEST_F(UT_GamePage, UT_GamePage_hintBtnflash)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    m_gamePage->hintGame();
    m_gamePage->hintBtnflash(OnlyPic);
    EXPECT_EQ(m_gamePage->m_hintBtn.at(0)->btnMode(), OnlyPic) << "check the status after UT_GamePage_hintBtnflash()";
    EXPECT_EQ(m_gamePage->m_hintBtn.at(1)->btnMode(), OnlyPic) << "check the status after UT_GamePage_hintBtnflash()";
}

TEST_F(UT_GamePage, UT_GamePage_recoverBtnState)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    m_gamePage->recoverBtnState();
    m_gamePage->hintGame();
    m_gamePage->recoverBtnState();
    EXPECT_EQ(m_gamePage->m_hintBtn.at(0)->m_gameBtnPressd, false) << "check the status after UT_GamePage_recoverBtnState()";
    EXPECT_EQ(m_gamePage->m_hintBtn.at(1)->m_gameBtnPressd, false) << "check the status after UT_GamePage_recoverBtnState()";
}

TEST_F(UT_GamePage, UT_GamePage_judgeGame)
{
    Stub stub;
    stub.set(ADDR(GameControl, gameJudge), UT_GamePage_gameJudge);
    bool res = m_gamePage->judgeGame();
    EXPECT_EQ(res, true) << "check the status after UT_GamePage_judgeGame()";
}

TEST_F(UT_GamePage, UT_GamePage_judgeVictory)
{
    bool res = m_gamePage->judgeVictory();
    EXPECT_EQ(res, false) << "check the status after UT_GamePage_judgeVictory()";
}

TEST_F(UT_GamePage, UT_GamePage_changeDir)
{
    int res1 = m_gamePage->changeDir(DIR_RIGHT);
    EXPECT_EQ(res1, DIR_LEFT) << "check the status after UT_GamePage_changeDir()";
    int res2 = m_gamePage->changeDir(DIR_LEFT);
    EXPECT_EQ(res2, DIR_RIGHT) << "check the status after UT_GamePage_changeDir()";
    int res3 = m_gamePage->changeDir(DIR_UP);
    EXPECT_EQ(res3, DIR_DOWN) << "check the status after UT_GamePage_changeDir()";
    int res4 = m_gamePage->changeDir(DIR_DOWN);
    EXPECT_EQ(res4, DIR_UP) << "check the status after UT_GamePage_changeDir()";
}

TEST_F(UT_GamePage, UT_GamePage_dirCoord001)
{
    QPointF testPos(50, 50);
    QPointF res1 = m_gamePage->dirCoord(LineType, DIR_RIGHT, testPos);
    EXPECT_EQ(res1, QPointF(55, 50)) << "check the status after UT_GamePage_dirCoord001()";
    QPointF res2 = m_gamePage->dirCoord(LineType, DIR_LEFT, testPos);
    EXPECT_EQ(res2, QPointF(45, 50)) << "check the status after UT_GamePage_dirCoord001()";
    QPointF res3 = m_gamePage->dirCoord(LineType, DIR_UP, testPos);
    EXPECT_EQ(res3, QPointF(50, 45)) << "check the status after UT_GamePage_dirCoord001()";
    QPointF res4 = m_gamePage->dirCoord(LineType, DIR_DOWN, testPos);
    EXPECT_EQ(res4, QPointF(50, 55)) << "check the status after UT_GamePage_dirCoord001()";
}

TEST_F(UT_GamePage, UT_GamePage_dirCoord002)
{
    QPointF testPos(50, 50);
    QPointF res1 = m_gamePage->dirCoord(ExplodeType, DIR_RIGHT, testPos);
    EXPECT_EQ(res1, QPointF(100, 75)) << "check the status after UT_GamePage_dirCoord002()";
    QPointF res2 = m_gamePage->dirCoord(ExplodeType, DIR_LEFT, testPos);
    EXPECT_EQ(res2, QPointF(50, 75)) << "check the status after UT_GamePage_dirCoord002()";
    QPointF res3 = m_gamePage->dirCoord(ExplodeType, DIR_UP, testPos);
    EXPECT_EQ(res3, QPointF(75, 50)) << "check the status after UT_GamePage_dirCoord002()";
    QPointF res4 = m_gamePage->dirCoord(ExplodeType, DIR_DOWN, testPos);
    EXPECT_EQ(res4, QPointF(75, 100)) << "check the status after UT_GamePage_dirCoord002()";
}

TEST_F(UT_GamePage, UT_GamePage_mouseMoveEvent)
{
    QMouseEvent e(QEvent::Move, QPointF(m_gamePage->x(), m_gamePage->y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_gamePage->mouseMoveEvent(&e);
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_mouseMoveEvent()";
}

TEST_F(UT_GamePage, UT_GamePage_onhintPicOnTimerOut)
{
    m_gamePage->onhintPicOnTimerOut();
    m_gamePage->m_flashCount = 0;
    m_gamePage->onhintPicOnTimerOut();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_onhintPicOnTimerOut()";
}

TEST_F(UT_GamePage, UT_GamePage_onhintPicOffTimerOut)
{
    m_gamePage->onhintPicOffTimerOut();
    EXPECT_NE(m_gamePage, nullptr) << "check the status after UT_GamePage_onhintPicOffTimerOut()";
}
