// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gamepage.h"
#include "gamecontrol.h"
#include "closewindowdialog.h"
#include "gamelinescene.h"

#include <DGuiApplicationHelper>

#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QtMultimedia/QSound>
#include <QDebug>
#include <QTime>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QMessageBox>
#include <QList>
#include <QFrame>
#include <QTime>

const int BtnFlashCount = 3;//提示按钮闪烁次数
const unsigned int explodePicSize = 5; //爆炸图片大小

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_hintPicOnTimer = new QTimer(this);
    m_hintPicOnTimer->setInterval(200);
    m_hintPicOffTimer = new QTimer(this);
    m_hintPicOffTimer->setInterval(200);
    m_flashCount = BtnFlashCount;
    QSound *serachSuccess = new QSound(":/assets/Sound/ConnectSuccess.wav", this);
    QSound *serachFailed = new QSound(":/assets/Sound/ConnectFailed.wav", this);
    m_soundMap.insert("success", serachSuccess);
    m_soundMap.insert("failed", serachFailed);
    initUI();
    initConnect();
}

GamePage::~GamePage()
{
    if (m_mainLayout) {
        delete m_mainLayout;
        m_mainLayout = nullptr;
    }
}

void GamePage::setInitalTime(int time)
{
    m_value = time;
    m_timeRecord = time;
    m_progress->setInintalTime(time);
    m_gameStart = false;
}

void GamePage::setSoundSwitch(bool isOpen)
{
    m_soundSwitch = isOpen;
    //更改游戏页面音效图标状态
    GameButton *soundBtn = dynamic_cast<GameButton *>(m_controlGrp->button(3));
    if (!soundBtn)
        return;
    soundBtn->updatePlayIcon(GameBtnType::SoundCtl, isOpen);
}

void GamePage::restartGame(bool isFirst)
{
    GameControl::GameInterFace().gameBegin();
    //第一次游戏只需要打乱游戏地图,重新开始游戏需要刷新按钮
    if (!isFirst)
        updateBtn();
}

void GamePage::setOnOffGame(bool isBegin)
{
    if (isBegin) {
        m_gameStart = true;
        m_timer->start();
    } else {
        m_timer->stop();
    }

    //设置可点击状态
    m_gameFrame->setEnabled(isBegin);
    //改变开始状态
    m_isStart = isBegin;
    //更改开始图标状态
    GameButton *beginBtn = dynamic_cast<GameButton *>(m_controlGrp->button(0));
    if (!beginBtn)
        return;
    beginBtn->updatePlayIcon(GameBtnType::GameCtl, isBegin);

    for (QAbstractButton *btn : m_controlGrp->buttons()) {
        //开始按钮和返回主页面按钮和音效按钮保持可点击状态
        if (btn == m_controlGrp->button(0) || btn == m_controlGrp->button(4) || btn == m_controlGrp->button(3))
            continue;
        btn->setEnabled(isBegin);
    }
}

bool GamePage::onOffGame() const
{
    return m_isStart;
}

void GamePage::resetGame()
{
    GameControl::GameInterFace().gameReset();
    //消除提示效果
    m_hintPicOnTimer->stop();
    m_hintPicOffTimer->stop();
    hintBtnflash(GameBtnType::OnlyPic);
    recoverBtnState();
    updateBtn();
}

void GamePage::hintGame()
{
    //judge判断
    //如果判断有可以连接成功的按钮
    if (judgeGame()) {
        //获取游戏提示坐标,设置按钮提示状态
        //取消已选中按钮的选中状态
        if (!m_locationVec.isEmpty()) {
            int rowIndex = m_locationVec.first()->location().x();
            int columnIndex = m_locationVec.first()->location().y();
            GameButton *gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((rowIndex - 1) * 16 + columnIndex - 1)->widget());
            if (!gameBtn) {
                qWarning() << "Btn is Null";
                return;
            }
            gameBtn->setPressed(false);
            m_locationVec.clear();
        }
        //设置提示效果
        QList<GameButton *> gameBtnList;
        for (QPoint pos : m_hintPoint) {
            //qInfo()<<pos;
            GameButton *gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((pos.x() - 1) * 16 + pos.y() - 1)->widget());
            if (!gameBtn) {
                qWarning() << "Btn is Null";
                return;
            }
            gameBtnList.append(gameBtn);
            gameBtn->setPressed(true);
            gameBtn->setEnabled(false);
        }
        m_hintBtn = gameBtnList;
        //设置提示按钮闪烁
        hintBtnflash(GameBtnType::NoneType);
        m_flashCount = BtnFlashCount;
        m_hintPicOnTimer->start();
    }
}

bool GamePage::judgeGame()
{
    QPair<bool, QList<QPoint>> res = GameControl::GameInterFace().gameJudge();
    if (res.first) {
        m_hintPoint = res.second;
        return true;
    }
    return false;
}

bool GamePage::judgeVictory()
{
    return GameControl::GameInterFace().gameJudgeVictory();
}

void GamePage::initUI()
{
    m_mainLayout = new QVBoxLayout(this);
    QHBoxLayout *gameFrameLayout = new QHBoxLayout;
    QVBoxLayout *controlBtnLayout = new QVBoxLayout;
    m_gameBtngridLayout = new QGridLayout;

    m_gameFrame = new GameBlurEffectWidget(GameBtnSize::Big, this);
    m_gameFrame->setFixedSize(835, 542);

    m_gameBtngridLayout->setContentsMargins(20, 10, 20, 35);
    m_animalGrp = new QButtonGroup(this);
    m_animalGrp->setExclusive(true);
    initGameBtn(); //初始化游戏按钮和状态
    m_gameFrame->setLayout(m_gameBtngridLayout);

    GameBlurEffectWidget *controlFrame = new GameBlurEffectWidget(GameBtnSize::Small, this);
    controlFrame->setFixedSize(175, 542);

    m_controlGrp = new QButtonGroup(controlFrame);
    GameButton *beginBtn = BtnFactory::createBtn(ButtonSmall, Small, Begin);
    GameButton *resetBtn = BtnFactory::createBtn(ButtonSmall, Small, Reset);
    GameButton *hintBtn = BtnFactory::createBtn(ButtonSmall, Small, Hint);
    GameButton *soundBtn = BtnFactory::createBtn(ButtonSmall, Small, Sound);
    GameButton *homeBtn = BtnFactory::createBtn(ButtonSmall, Small, Home);
    controlBtnLayout->addWidget(beginBtn);
    controlBtnLayout->addSpacing(-23);
    controlBtnLayout->addWidget(resetBtn);
    controlBtnLayout->addSpacing(-22);
    controlBtnLayout->addWidget(hintBtn);
    controlBtnLayout->addSpacing(-21);
    controlBtnLayout->addWidget(soundBtn);
    controlBtnLayout->addStretch();
    controlBtnLayout->addWidget(homeBtn);

    m_controlGrp->addButton(beginBtn, 0);
    m_controlGrp->addButton(resetBtn, 1);
    m_controlGrp->addButton(hintBtn, 2);
    m_controlGrp->addButton(soundBtn, 3);
    m_controlGrp->addButton(homeBtn, 4);
    //设置状态为暂停状态
    setOnOffGame(false);
    controlBtnLayout->setAlignment(Qt::AlignHCenter);
    controlBtnLayout->setContentsMargins(0, 25, 0, 25);
    controlFrame->setLayout(controlBtnLayout);

    gameFrameLayout->addSpacing(-10);
    gameFrameLayout->addWidget(m_gameFrame);
    gameFrameLayout->addWidget(controlFrame);

    m_progress = new GameProgressBar(this);
    m_progress->setFixedSize(816, 54);
    m_mainLayout->addLayout(gameFrameLayout);
    m_mainLayout->addWidget(m_progress);
    m_mainLayout->setContentsMargins(15, 86, 15, 25);
    this->setLayout(m_mainLayout);
    m_drawScene = new GameLineScene(this);
    m_drawScene->setFixedSize(this->parent()->property("size").value<QSize>());
}


void GamePage::initConnect()
{
    QObject::connect(m_controlGrp, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &GamePage::onControlBtnControl);
    QObject::connect(m_animalGrp, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed), this, &GamePage::onAnimalBtnControl);
    QObject::connect(m_progress, &GameProgressBar::valueChanged, this, &GamePage::onProgressChanged);
    QObject::connect(m_hintPicOnTimer, &QTimer::timeout, this, &GamePage::onhintPicOnTimerOut);
    QObject::connect(m_hintPicOffTimer, &QTimer::timeout, this, &GamePage::onhintPicOffTimerOut);
    QObject::connect(m_timer, &QTimer::timeout, this, [&] {
        m_value--;
        m_progress->setValue(m_value);
    });

}

void GamePage::initGameBtn()
{
    //初始化游戏按钮
    restartGame(true);
    for (int i = 0; i < GAMEROW; i++) {
        for (int j = 0; j < GAMECOLUMN; j++) {
            GameButton *gameBtn = BtnFactory::createBtn(GameControl::m_map[i + 1][j + 1], Default, None);
            //游戏按钮阴影处理
            shadowBtn(gameBtn);
            gameBtn->setLocation(i + 1, j + 1);
            m_btnWidth = gameBtn->width();
            m_btnHeight = gameBtn->height();
            m_animalGrp->addButton(gameBtn);
            m_gameBtngridLayout->addWidget(gameBtn, i, j);
        }
    }

}

void GamePage::shadowBtn(GameButton *btn)
{
    //按钮阴影处理
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 2);
    QColor shadowColor(0, 0, 0);
    shadowColor.setAlphaF(0.5);
    shadowEffect->setColor(shadowColor);
    shadowEffect->setBlurRadius(4);
    btn->setGraphicsEffect(shadowEffect);
}

void GamePage::updateBtn()
{
    int index = 0;
    //遍历更新打乱后按钮的状态
    for (int i = 0; i < GAMEROW; i++) {
        for (int j = 0; j < GAMECOLUMN; j++) {
            GameButton *gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt(index)->widget());
            if (!gameBtn) {
                qWarning() << "Btn is Null";
                return;
            }
            //qInfo() << GameControl::m_map[i + 1][j + 1] << "row" << i + 1 << "column" << j + 1;
            //更新完按钮图片需要更新按钮的类型
            GameBtnFlag btnFlag = GameControl::m_map[i + 1][j + 1];
            if (btnFlag == ButtonBlank) {
                gameBtn->setBtnMode(NoneType);
            } else {
                gameBtn->setBtnMode(OnlyPic);
            }

            gameBtn->updatePic(GameControl::m_picMap.value(qMakePair(btnFlag, Default)));
            index++;
        }
    }
}

void GamePage::successAction(GameButton *preBtn, GameButton *currentBtn)
{
    int endX = currentBtn->location().x();
    int endY = currentBtn->location().y();
    int startX = preBtn->location().x();
    int startY = preBtn->location().y();
    //    qInfo()<<startX<<startY<<endX<<endY;
    int rowIndex = endX;
    int columnIndex = endY;
    //保存通路路径,为了绘制通路路线
    while (rowIndex != startX || columnIndex != startY) {
        const QPoint index = GameControl::m_pathMap[rowIndex][columnIndex];
        int trun = GameControl::m_dir[rowIndex][columnIndex];
        m_pathVec.append(qMakePair(trun, index));
        rowIndex = index.x();
        columnIndex = index.y();
    }
    //qInfo()<<m_pathVec<<m_locationVec;
    //清除通路容器
    m_locationVec.append(currentBtn);

    updateConnection(preBtn, currentBtn);

    //连线成功音效
    if (m_soundSwitch)
        m_soundMap.value("success")->play();
    //更新地图
    GameControl::m_map[currentBtn->location().x()][currentBtn->location().y()] = GameBtnFlag::ButtonBlank;
    GameControl::m_map[preBtn->location().x()][preBtn->location().y()] = GameBtnFlag::ButtonBlank;

    //定义一个新的事件循环,等待200ms
    QEventLoop loop;
    QTimer::singleShot(200, &loop, SLOT(quit()));
    loop.exec();

    //将成功图标消失
    currentBtn->setBtnMode(GameBtnType::NoneType);
    preBtn->setBtnMode(GameBtnType::NoneType);

    m_drawScene->setMissing();
    //清除按钮容器
    m_locationVec.clear();
    //清楚路径
    m_pathVec.clear();
    //判断游戏是否胜利,如果胜利,发送成功信号
    if (judgeVictory()) {
        //游戏胜利啦!
        //将游戏状态暂停
        setOnOffGame(false);
        Q_EMIT sigResult(true);
    }

    //如果当前是死局,打乱布局,重新生成
    if (!judgeGame())
        resetGame();
}

void GamePage::failedAction(GameButton *preBtn, GameButton *currentBtn)
{
    //连线失败音效
    if (m_soundSwitch)
        m_soundMap.value("failed")->play();
    //添加当前选中按钮,pop前一个按钮
    m_locationVec.append(currentBtn);
    m_locationVec.pop_front();
}

void GamePage::popDialog()
{
    CloseWindowDialog *dialog = new CloseWindowDialog(this);
    //保留弹出窗口前的开始暂停状态
    bool preOnOff = onOffGame();
    //弹出阻塞窗口暂停游戏
    setOnOffGame(false);
    dialog->setMinimumWidth(390);

    //wayland下只能使用模态窗口去让弹窗存在的情况下不退出，x11情况下需要让弹窗与应用dock栏缩小时保持一致，故不使用模态窗口。
    if (qApp->platformName() == "dwayland" || qApp->property("_d_isDwayland").toBool()) {
        dialog->exec();
    } else {
        this->parentWidget()->parentWidget()->setEnabled(false);
        dialog->setEnabled(true);
        dialog->show();
        //添加时间循环，直到获取按钮信息退出循环
        QEventLoop loop;
        connect(dialog, &CloseWindowDialog::buttonClicked, &loop, &QEventLoop::quit);
        connect(dialog, &CloseWindowDialog::finished, &loop, &QEventLoop::quit);
        m_isDialog = true;
        loop.exec();
        this->parentWidget()->parentWidget()->setEnabled(true);
    }

    if (dialog->result() == QMessageBox::Ok) {
        //返回主页面
        Q_EMIT backToMainPage();
        Q_EMIT setGameStated(false);
    } else {
        //点击继续游戏,游戏回到弹出阻塞窗口前的状态
        setOnOffGame(preOnOff);
    }


    GameButton *btn = dynamic_cast<GameButton *>(m_controlGrp->button(4));
    if (!btn) {
        return;
    }
    btn->setControlBtnPressed(false);
    dialog->done(0);
    m_isDialog = false;
}

void GamePage::updateConnection(GameButton *preBtn, GameButton *currentBtn)
{
    QVector<QPair<int, QPoint>>::iterator iter;
    QList<QPointF> pointList;

    //游戏区域原点坐标
    int framePosX = m_gameFrame->pos().x();
    int framePosY = m_gameFrame->pos().y();
    //    qInfo()<<framePosX<<framePosY;
    //        qInfo()<<m_pathVec;
    if (m_pathVec.isEmpty())
        return;

    //获取两个点击按钮的坐标
    //    GameButton *gameStartBtn = m_locationVec.first();
    //    GameButton *gameEndBtn = m_locationVec.last();
    GameButton *gameBtn = nullptr;
    qreal btnStartX = preBtn->pos().x();
    qreal btnStartY = preBtn->pos().y();
    qreal btnEndX = currentBtn->pos().x();
    qreal btnEndY = currentBtn->pos().y();

    //    qInfo() << btnStartX << btnStartY << btnEndX << btnEndY;
    //如果路径容器种只有一个位置,那就代表两个按钮靠在一起,故单独处理
    if (m_pathVec.count() == 1) {
        QPointF posStart(btnStartX + m_btnWidth / 2 + framePosX, btnStartY + m_btnHeight / 2 + framePosY);
        //连线开始坐标
        QPointF lineStart = dirCoord(LineType, m_pathVec.first().first, posStart);
        //获取第二个点击按钮的坐标
        QPointF posEnd(btnEndX + m_btnWidth / 2 + framePosX, btnEndY + m_btnHeight / 2 + framePosY);
        //连线结束绘制坐标
        QPointF lineEnd = dirCoord(LineType, changeDir(m_pathVec.first().first), posEnd);

        pointList.append(posStart);
        pointList.append(lineStart);
        pointList.append(lineEnd);
        pointList.append(posEnd);
    } else {
        //如果两个按钮不相邻,根据通路组求具体坐标,绘制通路路线
        //        qInfo()<<m_pathVec<<(m_pathVec.end()-1)->second;
        for (iter = m_pathVec.end() - 1; iter >= m_pathVec.begin(); --iter) {
            QPointF pos;
            int rowIndex = iter->second.x();
            int columnIndex = iter->second.y();
            //qInfo()<<rowIndex<<columnIndex<<iter->first;

            //求通路起点位置
            if (iter == m_pathVec.end() - 1) {
                //保存当前转向方向
                m_dir = iter->first;
                QPointF startPos = dirCoord(ExplodeType, iter->first, preBtn->pos());
                QPointF lineStartPos = dirCoord(LineType, iter->first, startPos);
                //添加爆炸图起点和连线起点
                pointList.append(startPos);
                pointList.append(lineStartPos);
            } else {
                //记录方向与前面方向不同的转向点
                if (m_dir != iter->first) {
                    if (rowIndex < 1) {
                        //当超越游戏行上边界时,取第一行按钮的坐标
                        gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt(columnIndex - 1)->widget());
                        if (!gameBtn) {
                            qWarning() << "Btn is Illgel";
                            return;
                        }
                        pos = QPointF(gameBtn->pos().x() + m_btnWidth / 2 + framePosX, gameBtn->pos().y() - m_btnHeight / 2 + framePosY);
                    } else if (rowIndex > GAMEROW) {
                        //当超越游戏行下边界时,取最后一行按钮的坐标
                        gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((GAMEROW - 1) * GAMECOLUMN + columnIndex - 1)->widget());
                        if (!gameBtn) {
                            qWarning() << "Btn is Illgel";
                            return;
                        }
                        pos = QPointF(gameBtn->pos().x() + m_btnWidth / 2 + framePosX, gameBtn->pos().y() + m_btnHeight + m_btnHeight / 2 + framePosY);
                    } else if (columnIndex < 1) {
                        //当超越游戏列左边界时,取第一列按钮的坐标
                        gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((rowIndex - 1) * GAMECOLUMN + columnIndex)->widget());
                        if (!gameBtn) {
                            qWarning() << "Btn is Illgel";
                            return;
                        }
                        pos = QPointF(gameBtn->pos().x() - m_btnWidth / 3 + framePosX, gameBtn->pos().y() + m_btnHeight / 2 + framePosY);
                    } else if (columnIndex > GAMECOLUMN) {
                        //当超越游戏列右边界时,取最后一列按钮的坐标
                        gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((rowIndex - 1) * GAMECOLUMN + columnIndex - 2)->widget());
                        if (!gameBtn) {
                            qWarning() << "Btn is Illgel";
                            return;
                        }
                        pos = QPointF(gameBtn->pos().x() + m_btnWidth + m_btnWidth / 3 + framePosX, gameBtn->pos().y() + m_btnHeight / 2 + framePosY);
                    } else {
                        //正常游戏区域按钮的坐标
                        gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((rowIndex - 1) * GAMECOLUMN + columnIndex - 1)->widget());
                        if (!gameBtn) {
                            qWarning() << "Btn is Illgel";
                            return;
                        }
                        pos = QPointF(gameBtn->pos().x() + m_btnWidth / 2 + framePosX, gameBtn->pos().y() + m_btnHeight / 2 + framePosY);
                    }
                    m_dir = iter->first;
                    pointList.append(pos);
                }
            }
        }
        QPointF endPos = dirCoord(ExplodeType, changeDir(m_dir), currentBtn->pos());
        QPointF lineEndPos = dirCoord(LineType, changeDir(m_dir), endPos);
        pointList.append(lineEndPos);
        pointList.append(endPos);
    }

    m_drawScene->setDrawPath(pointList);
    pointList.clear();
}

QPointF GamePage::dirCoord(PosType order, int dir, QPointF pos)
{
    qreal btnX = pos.x();
    qreal btnY = pos.y();
    //游戏区域原点坐标
    int framePosX = m_gameFrame->pos().x();
    int framePosY = m_gameFrame->pos().y();

    QPointF dirPos;

    //如果是绘制开始爆炸效果,求爆炸效果图之后的连线开始坐标
    if (order == LineType) {
        switch (dir) {
        //如果为向右方向,右侧坐标
        case DIR_RIGHT:
            dirPos = QPointF(btnX + explodePicSize, btnY);
            break;
        //如果为向左方向,左侧坐标
        case DIR_LEFT:
            dirPos = QPointF(btnX - explodePicSize, btnY);
            break;
        //如果为向上方向,上方坐标
        case DIR_UP:
            dirPos = QPointF(btnX, btnY - explodePicSize);
            break;
        //如果为向下方向,下方坐标
        default:
            dirPos = QPointF(btnX, btnY + explodePicSize);
            break;
        }
    } else {
        //如果不是相邻的两个按钮,需要判断绘制爆炸效果的点
        switch (dir) {
        //如果为向右方向,右侧坐标
        case DIR_RIGHT:
            dirPos = QPointF(btnX + framePosX + m_btnWidth, btnY + framePosY + m_btnHeight / 2);
            break;
        //如果为向左方向,左侧坐标
        case DIR_LEFT:
            dirPos = QPointF(btnX + framePosX, btnY + framePosY + m_btnHeight / 2);
            break;
        //如果为向上方向,上方坐标
        case DIR_UP:
            dirPos = QPointF(btnX + framePosX + m_btnWidth / 2, btnY + framePosY);
            break;
        //如果为向下方向,下方坐标
        default:
            dirPos = QPointF(btnX + framePosX + m_btnWidth / 2, btnY + m_btnHeight + framePosY);
            break;
        }
    }

    return dirPos;
}

int GamePage::changeDir(int dir)
{
    switch (dir) {
    //如果为向右方向,左侧坐标
    case DIR_RIGHT:
        dir = DIR_LEFT;
        break;
    //如果为向左方向,右侧坐标
    case DIR_LEFT:
        dir = DIR_RIGHT;
        break;
    //如果为向上方向,下方坐标
    case DIR_UP:
        dir = DIR_DOWN;
        break;
    //如果为向下方向,上方坐标
    default:
        dir = DIR_UP;
        break;
    }
    return dir;
}

void GamePage::hintBtnflash(GameBtnType type)
{
    if (!m_hintBtn.isEmpty()) {
        m_hintBtn.at(0)->setBtnMode(type);
        m_hintBtn.at(1)->setBtnMode(type);
    }
}

void GamePage::recoverBtnState()
{
    if (m_hintBtn.isEmpty()) {
        return;
    }
    if (m_hintBtn.at(0)) {
        m_hintBtn.at(0)->setPressed(false);
        m_hintBtn.at(0)->setEnabled(true);
    }
    if (m_hintBtn.at(1)) {
        m_hintBtn.at(1)->setPressed(false);
        m_hintBtn.at(1)->setEnabled(true);
    }
}

void GamePage::onControlBtnControl(int id)
{
    switch (id) {
    case 0: {
        if (!m_isStart) {
            //点击开始后,设置相关按钮可点击,定时器开始
            setOnOffGame(true);
            Q_EMIT setGameStated(true);
        } else {
            //点击暂停后,设置相关按钮不可点击,定时器暂停
            setOnOffGame(false);
        }
        break;
    }
    case 1: {
        //重置游戏
        resetGame();
        break;
    }
    case 2: {
        //游戏提示
        hintGame();
        break;
    }
    case 3: {
        //音效开关
        setSoundSwitch(!m_soundSwitch);
        //音量状态同步到主页面
        Q_EMIT soundSync(m_soundSwitch);
        break;
    }
    default: {
        //弹出关闭弹窗
        if (m_gameStart) {
            popDialog();
        } else {
            Q_EMIT backToMainPage();
        }
        break;
    }
    }
}

void GamePage::onhintPicOnTimerOut()
{
    m_hintPicOnTimer->stop();
    m_flashCount--;
    this->hintBtnflash(GameBtnType::OnlyPic);

    if (m_flashCount != 0) {
        m_hintPicOffTimer->start();
    } else {
        this->hintBtnflash(GameBtnType::OnlyPic);
        this->recoverBtnState();
    }
}

void GamePage::onhintPicOffTimerOut()
{
    m_hintPicOffTimer->stop();
    this->hintBtnflash(GameBtnType::NoneType);
    m_hintPicOnTimer->start();
}

void GamePage::onAnimalBtnControl(QAbstractButton *btn)
{
    GameButton *gameBtn = dynamic_cast<GameButton *>(btn);
    if (!gameBtn || gameBtn->btnMode() == GameBtnType::NoneType) {
        qWarning() << "btn is illegal";
        return;
    }

    int vecCount = m_locationVec.count();
    //count为1,点击第第二按钮
    if (vecCount == 1) {
        GameButton *firstBtn = m_locationVec.first();
        //如果两个按钮坐标相同,不做任何操作
        if (gameBtn->pos() == firstBtn->pos())
            return;
        //判断搜索结果
        // qInfo()<<firstBtn->location()<<gameBtn->location();
        GameSearchResult res = GameControl::GameInterFace().gameSearch(firstBtn->location(), gameBtn->location());
        //如果符合规则
        switch (res) {
        case PositiveSuccess:
            successAction(firstBtn, gameBtn);
            break;
        case ReverseSuccess:
            successAction(gameBtn, firstBtn);
            break;
        default:
            failedAction(firstBtn, gameBtn);
            break;
        }

    } else {
        //点击第一个按钮,增加一个按钮
        m_locationVec.append(gameBtn);
    }
    //fix---消除点击太快偶现选中效果无法消失的问题,故对除了空白按钮和当前按钮的所有按钮进行刷新----
    for (QAbstractButton *btn : m_animalGrp->buttons()) {
        GameButton *gameBtn = dynamic_cast<GameButton *>(btn);
        if (!gameBtn || gameBtn->btnMode() == NoneType)
            continue;
        if (!m_locationVec.isEmpty()) {
            if (gameBtn != m_locationVec.last()) {
                gameBtn->setPressed(false);
            }
        }
    }
}

void GamePage::onProgressChanged(int value)
{
    if (value == 0) {
        //无了!
        //显示失败结果,发送失败信号
        //将游戏暂停
        setOnOffGame(false);
        Q_EMIT sigResult(false);
    }
}

void GamePage::reGame()
{
    setInitalTime(m_timeRecord);
    restartGame(false);
}

void GamePage::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
