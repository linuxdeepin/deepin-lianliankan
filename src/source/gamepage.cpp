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
#include "gamepage.h"
#include "gamecontrol.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QtMultimedia/QSound>
#include <QDebug>
#include <QTime>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    QSound *serachSuccess = new QSound(":/assets/Sound/ConnectSuccess.wav", this);
    QSound *serachFailed = new QSound(":/assets/Sound/ConnectFailed.wav", this);
    m_soundMap.insert("success", serachSuccess);
    m_soundMap.insert("failed", serachFailed);
    initUI();
    initConnect();
}

void GamePage::setInitalTime(int time)
{
    m_value = time;
    m_progress->setInintalTime(time);
}

void GamePage::setSoundSwitch(bool isOpen)
{
    m_soundSwitch = isOpen;
}

bool GamePage::soundSwitch() const
{
    return m_soundSwitch;
}

void GamePage::beginGame()
{
    GameControl::GameInterFace().gameBegin();
    updateBtn();
}

void GamePage::resetGame()
{
    GameControl::GameInterFace().gameReset();
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
        }
        //设置提示效果
        for (QPoint pos : m_hintPoint) {
            //qInfo()<<pos;
            GameButton *gameBtn = dynamic_cast<GameButton *>(m_gameBtngridLayout->itemAt((pos.x() - 1) * 16 + pos.y() - 1)->widget());
            if (!gameBtn) {
                qWarning() << "Btn is Null";
                return;
            }
            gameBtn->setPressed(true);
        }
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

void GamePage::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *gameFrameLayout = new QHBoxLayout;
    QVBoxLayout *controlBtnLayout = new QVBoxLayout;
    m_gameBtngridLayout = new QGridLayout;

    m_gameFrame = new GameBlurEffectWidget(GameBtnSize::Big, this);
    m_gameFrame->setMinimumSize(835, 516);

    m_gameBtngridLayout->setContentsMargins(20, 10, 20, 35);
    m_animalGrp = new QButtonGroup(this);
    m_animalGrp->setExclusive(true);
    initGameBtn(); //初始化游戏按钮
    m_gameFrame->setLayout(m_gameBtngridLayout);

    GameBlurEffectWidget *controlFrame = new GameBlurEffectWidget(GameBtnSize::Small, this);
    controlFrame->setMinimumSize(175, 516);

    m_controlGrp = new QButtonGroup(controlFrame);
    GameButton *beginBtn = BtnFactory::createBtn(ButtonNormal, Small, None, "开始/暂停");
    GameButton *resetBtn = BtnFactory::createBtn(ButtonNormal, Small, None, "重置");
    GameButton *hintBtn = BtnFactory::createBtn(ButtonNormal, Small, None, "提示");
    GameButton *soundBtn = BtnFactory::createBtn(ButtonNormal, Small, None, "音效");
    GameButton *homeBtn = BtnFactory::createBtn(ButtonNormal, Small, None, "主页面");
    controlBtnLayout->addWidget(beginBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(resetBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(hintBtn);
    controlBtnLayout->addSpacing(-15);
    controlBtnLayout->addWidget(soundBtn);
    controlBtnLayout->addStretch();
    controlBtnLayout->addWidget(homeBtn);
    m_controlGrp->addButton(beginBtn, 0);
    m_controlGrp->addButton(resetBtn, 1);
    m_controlGrp->addButton(hintBtn, 2);
    m_controlGrp->addButton(soundBtn, 3);
    m_controlGrp->addButton(homeBtn, 4);
    controlBtnLayout->setAlignment(Qt::AlignHCenter);
    controlBtnLayout->setContentsMargins(0, 25, 0, 25);
    controlFrame->setLayout(controlBtnLayout);

    gameFrameLayout->addSpacing(-10);
    gameFrameLayout->addWidget(m_gameFrame);
    gameFrameLayout->addWidget(controlFrame);

    m_progress = new GameProgressBar(this);
    m_progress->setFixedSize(816, 49);
    mainLayout->addLayout(gameFrameLayout);
    mainLayout->addWidget(m_progress);
    mainLayout->setContentsMargins(15, 86, 15, 43);
    setBtnEnabled(false);
    this->setLayout(mainLayout);
}

void GamePage::initConnect()
{
    QObject::connect(m_controlGrp, QOverload<int>::of(&QButtonGroup::buttonPressed), this, &GamePage::onControlBtnControl);
    QObject::connect(m_animalGrp, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed), this, &GamePage::onAnimalBtnControl);
    QObject::connect(m_progress, &GameProgressBar::valueChanged, this, &GamePage::onProgressChanged);
    QObject::connect(m_timer, &QTimer::timeout, this, [&] {
        m_value--;
        m_progress->setValue(m_value);
    });
}

void GamePage::initGameBtn()
{
    GameControl::GameInterFace().gameBegin();
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            GameButton *gameBtn = BtnFactory::createBtn(GameControl::m_map[i + 1][j + 1], Default, None);
            //游戏按钮阴影处理
            shadowBtn(gameBtn);
            gameBtn->setLocation(i + 1, j + 1);
            m_animalGrp->addButton(gameBtn);
            m_gameBtngridLayout->addWidget(gameBtn, i, j);
        }
    }
}

void GamePage::setBtnEnabled(bool isEnabled)
{
    //设置可点击状态
    m_gameFrame->setEnabled(isEnabled);
    m_isStart = isEnabled;
    for (QAbstractButton *btn : m_controlGrp->buttons()) {
        //开始按钮和返回主页面按钮保持可点击状态
        if (btn == m_controlGrp->button(0) || btn == m_controlGrp->button(4))
            continue;
        btn->setEnabled(isEnabled);
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
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
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
    int rowIndex = endX;
    int columnIndex = endY;
    //保存通路路径,为了绘制通路路线
    while (rowIndex != startX || columnIndex != startY) {
        QPoint index = GameControl::m_pathMap[rowIndex][columnIndex];
        m_pathVec.append(index);
        rowIndex = index.x();
        columnIndex = index.y();
    }
    // qInfo()<<m_pathVec;
    //清除通路容器
    m_pathVec.clear();
    //连线成功音效
    if (m_soundSwitch)
        m_soundMap.value("success")->play();
    //更新地图
    GameControl::m_map[currentBtn->location().x()][currentBtn->location().y()] = GameBtnFlag::ButtonBlank;
    GameControl::m_map[preBtn->location().x()][preBtn->location().y()] = GameBtnFlag::ButtonBlank;
    //将成功图标消失
    currentBtn->setBtnMode(GameBtnType::NoneType);
    preBtn->setBtnMode(GameBtnType::NoneType);
    //清除按钮容器
    m_locationVec.clear();
    //如果当前是死局,打乱布局,重新生成
    if (!judgeGame())
        resetGame();
}

void GamePage::failedAction(GameButton *preBtn, GameButton *currentBtn)
{
    //连线失败音效
    if (m_soundSwitch)
        m_soundMap.value("failed")->play();
    //如果不成功,取消按钮选中状态
    preBtn->setPressed(false);
    //添加当前选中按钮,pop前一个按钮
    m_locationVec.append(currentBtn);
    m_locationVec.pop_front();
}

void GamePage::onControlBtnControl(int id)
{
    switch (id) {
    case 0: {
        if (!m_isStart) {
            //点击开始后,设置相关按钮可点击,定时器开始
            setBtnEnabled(true);
            m_timer->start();
            //更改图标状态
        } else {
            //点击暂停后,设置相关按钮不可点击,定时器暂停
            setBtnEnabled(false);
            m_timer->stop();
            //更改图标状态
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
        break;
    }
    default: {
        //返回主页面
        Q_EMIT backToMainPage();
        setBtnEnabled(false);
        m_timer->stop();
        break;
    }
    }
}

void GamePage::onAnimalBtnControl(QAbstractButton *btn)
{
    QTime time;
    time.start();
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
        bool res = GameControl::GameInterFace().gameSearch(firstBtn->location(), gameBtn->location());
        //如果符合规则
        if (res) {
            successAction(firstBtn, gameBtn);
        } else {
            failedAction(firstBtn, gameBtn);
        }

    } else {
        //点击第一个按钮,增加一个按钮
        m_locationVec.append(gameBtn);
    }
    //    qInfo() << time.elapsed();
}

void GamePage::onProgressChanged(int value)
{
    if (value == 0) {
        m_timer->stop();
        //显示失败结果
    }
}

void GamePage::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
