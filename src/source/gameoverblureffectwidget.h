// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GAMEOVERBLUREFFECTWIDGET_H
#define GAMEOVERBLUREFFECTWIDGET_H

#include "global.h"
#include "shadowlabel.h"

#include <DBlurEffectWidget>
#include <DLabel>

#include <QButtonGroup>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE
class GameoverBlurEffectWidget : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit GameoverBlurEffectWidget(QWidget *parent = nullptr);
    ~GameoverBlurEffectWidget() override;

protected:
    void paintEvent(QPaintEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;

private:
    void initUI();
    void initConnect();

public:
    void updateLabel(QString text);

    /**
     * @brief setResult 外部通知游戏结果
     * @param res 游戏结果
     */
    void setResult(bool res);

private slots:
    void onButtonPressed(int id);

signals:
    void backToMainPage();//点击休息一下，返回主界面
    void reGame();//再玩一次
private:
    QVBoxLayout *m_mainLayout = nullptr;
    ShadowLabel *m_tipLabel;//提示语
    QButtonGroup *m_OverBtnGroup;
    bool m_overType = false;//游戏结果
    QPixmap m_pic;
};

#endif // GAMEOVERBLUREFFECTWIDGET_H
