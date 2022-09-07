// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gameoverblureffectwidget.h"
#include "gamebutton.h"
#include "gamecontrol.h"

#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

GameoverBlurEffectWidget::GameoverBlurEffectWidget(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    initUI();
    initConnect();
}

GameoverBlurEffectWidget::~GameoverBlurEffectWidget()
{
    if (m_mainLayout) {
        delete m_mainLayout;
        m_mainLayout = nullptr;
    }
}

void GameoverBlurEffectWidget::paintEvent(QPaintEvent *event)
{
    QString fileName;
    QSize scaledSize;
    if (m_overType) {
        scaledSize = QSize(370, 300);
        fileName = ":/assets/images/victory.png";
    } else {
        scaledSize = QSize(280, 300);
        fileName = ":/assets/images/failed.png";
    }
    m_pic = Utils::getDpiPixmap(scaledSize, fileName, this);

    //设置背景模糊
    DBlurEffectWidget::paintEvent(event);
    //绘制背景色
    QPainter painterBackground(this);
    painterBackground.setRenderHint(QPainter::Antialiasing, true);
    QColor color = QColor(60, 72, 0);
    color.setAlphaF(0.5);
    painterBackground.fillRect(rect(), color);
    //绘制居中图片
    painterBackground.save();
    int imgX = 0;
    int imgY = 0;
    if (m_overType) {
        imgX = 329;
        imgY = 108;
    } else {
        imgX = 372;
        imgY = 108;
    }
    painterBackground.drawPixmap(imgX, imgY, m_pic);
    painterBackground.restore();
}

void GameoverBlurEffectWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void GameoverBlurEffectWidget::initUI()
{
    setMaskAlpha(0);
    setRadius(35);
    m_mainLayout = new QVBoxLayout(this);

    m_tipLabel = new ShadowLabel(this);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    //设置阴影模糊半径为8
    effect->setBlurRadius(8);
    //设置阴影位置Y轴偏移4px
    effect->setYOffset(4);
    QColor shadowColor(108, 69, 25);
    //设置透明度
    shadowColor.setAlphaF(0.6);
    effect->setColor(shadowColor);
    m_tipLabel->setGraphicsEffect(effect);

    m_OverBtnGroup = new QButtonGroup(this);
    GameButton *againButton = BtnFactory::createBtn(ButtonNormal, Over, None, tr("Play Again"));
    GameButton *restButton = BtnFactory::createBtn(ButtonNormal, Over, None, tr("Have a Rest"));
    QLocale l;
    if (l.name() == "bo_CN") {
        QFont font;
        font.setPointSize(13);
        font.setFamily("Noto Sans CJK SC");
        font.setWeight(QFont::DemiBold);
        againButton->setFont(font);
        restButton->setFont(font);
    }
    m_OverBtnGroup->addButton(againButton, 0);
    m_OverBtnGroup->addButton(restButton, 1);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(againButton, Qt::AlignLeft);
    buttonLayout->addWidget(restButton, Qt::AlignRight);
    m_mainLayout->addWidget(m_tipLabel, Qt::AlignCenter);
    m_mainLayout->addLayout(buttonLayout, Qt::AlignBottom);
    m_mainLayout->setContentsMargins(295, 370, 295, 171);
}

void GameoverBlurEffectWidget::initConnect()
{
    connect(m_OverBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &GameoverBlurEffectWidget::onButtonPressed);
}

void GameoverBlurEffectWidget::updateLabel(QString text)
{
    m_tipLabel->setText(text);
}

void GameoverBlurEffectWidget::setResult(bool res)
{
    m_tipLabel->setResult(res);
    m_overType = res;
}

void GameoverBlurEffectWidget::onButtonPressed(int id)
{
    switch (id) {
    case 0: {
        Q_EMIT reGame();
        break;
    }
    default: {
        //返回主页面
        Q_EMIT backToMainPage();
        break;
    }
    }
}


