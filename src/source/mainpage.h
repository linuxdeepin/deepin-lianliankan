// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <DWidget>
#include <QButtonGroup>

class GameButton;
DWIDGET_USE_NAMESPACE
class MainPage: public DWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
signals:
    void buttonPress(int id); //难度按钮选择
    void soundSwitch(); //音效按钮点击

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void initUI();
    void initConnect();
public:
    /**
     * @brief soundSync 设置音效按钮状态
     * @param state 音效开关状态
     */
    void setSoundState(bool state);
    /**
     * @brief soundState 音效按钮状态
     * @return bool 音效开关状态
     */
    bool soundState() const;

private:
    QButtonGroup *m_btnGrp;
    GameButton *m_soundBtn;
    bool m_soundState = true; //音效开关状态
};

#endif // MAINPAGE_H
