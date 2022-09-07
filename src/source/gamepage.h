// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "gameprogressbar.h"
#include "gameblureffectwidget.h"
#include "gameoverblureffectwidget.h"
#include "gamebutton.h"

#include <QGridLayout>
#include <QButtonGroup>
#include <QTimer>
#include <QVector>
#include <QtMultimedia/QSound>

class GameLineScene;
DWIDGET_USE_NAMESPACE
class GamePage : public QWidget
{
    Q_OBJECT
public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage() override;
    /**
    * @brief GamePage::  setInitalTime 设置倒计时的时间
    * @param time 倒计时时间
    */
    void setInitalTime(int time);
    /**
    * @brief  GamePage::  setSoundSwitch 设置音效开关
    * @param isOpen 设置开关的状态
    */
    void setSoundSwitch(bool isOpen);
    /**
     * @brief GamePage::setOnOffGame 开始停止按钮和最小化暂停控制游戏的开始停止
     * @param isBegin 设置开始暂停状态
     */
    void setOnOffGame(bool isBegin);
    /**
     * @brief GamePage::onOffGame 开始停止按钮和最小化暂停控制游戏的开始停止
     * @return bool 游戏开始暂停状态
     */
    bool onOffGame() const;
    /**
    * @brief  GamePage:: reStartGame 第一次进入游戏或重玩游戏
    * @param isFirst 是否为第一次
    */
    void restartGame(bool isFirst);

    /**
     * @brief getDialogState 获取当前是否有弹窗
     * @return 弹窗存在与否
     */
    inline bool getDialogState() {return m_isDialog;}
signals:
    /**
    * @brief  GamePage:: reStartGame 回到主页面的信号
    */
    void backToMainPage();
    /**
    * @brief  GamePage:: sigResult 传递游戏失败胜利的信号
    * @param res 成功或者失败
    */
    void sigResult(bool res);
    /**
    * @brief  GamePage:: setGameStated 游戏是否正在进行种的信号
    * @param state 是否正在进行游戏
    */
    void setGameStated(bool state);
    /**
     * @brief soundSync 音量同步信号
     * @param isOpen 音量开关
     */
    void soundSync(bool isOpen);

public slots:
    /**
    * @brief  GamePage::onControlBtnControl 游戏控制按钮的选择
    * @param id 选中的按钮id
    */
    void onControlBtnControl(int id);
    /**
    * @brief  GamePage::onhintPicOnTimerOut 提示时间到的处理
    */
    void onhintPicOnTimerOut();
    /**
    * @brief  GamePage::onhintPicOffTimerOut 提示闪烁定时器(隐藏)时间的处理
    */
    void onhintPicOffTimerOut();
    /**
    * @brief  GamePage::onAnimalBtnControl 游戏界面动物按钮的选中
    * @param btn 选中的游戏动物按钮
    */
    void onAnimalBtnControl(QAbstractButton *btn);
    /**
    * @brief  GamePage::onProgressChanged 游戏界面界面倒计时的变化
    * @param value 倒计时数值
    */
    void onProgressChanged(int value);
    /**
    * @brief  GamePage::reGame 游戏结果页面再玩当前的难度再玩一局
    */
    void reGame();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    /**
    * @brief  GamePage::initUI 初始化游戏界面UI
    */
    void initUI();
    /**
    * @brief  GamePage::initConnect 绑定信号槽
    */
    void initConnect();
    /**
    * @brief  GamePage::initGameBtn 初始化动物游戏按钮
    */
    void initGameBtn();
    /**
    * @brief  GamePage::resetGame 重置游戏
    */
    void resetGame();
    /**
    * @brief  GamePage::hintGame 提示游戏
    */
    void hintGame();
    /**
    * @brief  GamePage::shadowBtn 游戏按钮阴影处理
    */
    void shadowBtn(GameButton *btn);
    /**
    * @brief  GamePage::updateBtn 刷新按钮
    */
    void updateBtn();
    /**
    * @brief  GamePage::successAction 连接成功的一系列动作和设置
    * @param  prebtn 前一个点击的游戏按钮
    * @param  currentbtn 当前点击的游戏按钮
    */
    void successAction(GameButton *prebtn, GameButton *currentbtn);
    /**
    * @brief  GamePage::failedAction 连接失败的一系列动作和设置
    * @param  prebtn 前一个点击的游戏按钮
    * @param  currentbtn 当前点击的游戏按钮
    */
    void failedAction(GameButton *prebtn, GameButton *currentbtn);
    /**
    * @brief  GamePage::popDialog 弹出关闭弹窗
    */
    void popDialog();
    /**
    * @brief  GamePage::updateConnection 更新通路连线,绘制线路
    * @param  prebtn 前一个点击的游戏按钮
    * @param  currentbtn 当前点击的游戏按钮
    */
    void updateConnection(GameButton *preBtn, GameButton *currentBtn);
    /**
    * @brief  GamePage::hintBtnflash 提示按钮闪烁
    * @param  type 按钮类型
    */
    void hintBtnflash(GameBtnType type);
    /**
     * @brief recoverBtnState 恢复按钮默认状态
     */
    void recoverBtnState();
    /**
    * @brief  GamePage::judgeGame 判断游戏是否有可连接的线路
    * @return bool 是否有可连接的线路
    */
    bool judgeGame();
    /**
    * @brief  GamePage::judgeVictory 判断游戏是否胜利
    * @return bool 游戏胜利或者失败
    */
    bool judgeVictory();
    /**
    * @brief  GamePage::changeDir 获取相反的方向
    * @param  dir 原来的方向
    * @return int 相反的方向
    */
    int changeDir(int dir);
    /**
    * @brief  GamePage::dirCoord 获取方向坐标
    * @param  order 连线或者爆炸效果
    * @param  dir 方向
    * @param  pos 当前点击按钮的坐标
    * @return QPointF 得到的爆炸图或者连线的坐标
    */
    QPointF dirCoord(PosType order, int dir, QPointF pos);

private:
    QVBoxLayout *m_mainLayout = nullptr;
    GameBlurEffectWidget *m_gameFrame; //游戏区域
    GameProgressBar *m_progress; //进度条
    QGridLayout *m_gameBtngridLayout; //游戏按钮布局
    QButtonGroup *m_animalGrp; //游戏动物按钮组
    QButtonGroup *m_controlGrp; //控制按钮组
    QMap<QString, QSound *> m_soundMap; //游戏音效
    QTimer *m_timer; //定时器
    QTimer *m_hintPicOnTimer;//提示闪烁定时器(展示)
    QTimer *m_hintPicOffTimer;//提示闪烁定时器(隐藏)
    QVector<GameButton *> m_locationVec; //点击按钮容器
    QVector<QPair<int, QPoint>> m_pathVec; //通路方向坐标
    QList<QPoint> m_hintPoint; //提示按钮坐标
    GameLineScene *m_drawScene; //连线场景
    QList<GameButton *> m_hintBtn;//提示按钮
    int m_value; //进度值
    int m_flashCount;//闪烁次数
    int m_timeRecord;//记录难度时间
    int m_dir; //路径方向
    int m_btnWidth; //游戏按钮宽度
    int m_btnHeight; //游戏按钮高度
    bool m_isStart = false; //开始暂停的控制
    bool m_soundSwitch = true; //音效开关控制
    bool m_gameStart = false; //记录游戏是否正在进行,暂停也是正在行
    bool m_isDialog = false; //记录是否已有弹窗
};

#endif // GAMEPAGE_H
