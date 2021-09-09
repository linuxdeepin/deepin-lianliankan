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
#include "gameoverblureffectwidget.h"
#include "gamebutton.h"
#include "gamecontrol.h"

#include <QPainter>
#include <QtMath>
#include <QImageReader>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontMetrics>
#include <QGraphicsDropShadowEffect>

GameoverBlurEffectWidget::GameoverBlurEffectWidget(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    initUI();
    initConnect();
}

void GameoverBlurEffectWidget::paintEvent(QPaintEvent *event)
{

    //设置背景模糊
    DBlurEffectWidget::setMaskAlpha(0);
    DBlurEffectWidget::setRadius(35);
    DBlurEffectWidget::paintEvent(event);
    //绘制背景色
    QPainter painterBackground(this);
    painterBackground.setRenderHint(QPainter::Antialiasing, true);
    QColor color = QColor(60,72,0);
    color.setAlphaF(0.5);
    painterBackground.fillRect(rect(), color);
    //绘制居中图片
    QPainter painterImg(this);
    painterBackground.setRenderHint(QPainter::Antialiasing, true);
    QPixmap pic;
    int imgX = 0;
    int imgY = 0;
    if (m_overType) {
        pic = GameControl::m_picMap.value(qMakePair(VictoryPic, Default));
        imgX = 329;
        imgY = 108;
    } else {
        pic = GameControl::m_picMap.value(qMakePair(FailedPic, Default));
        imgX = 372;
        imgY = 108;
    }
    painterImg.drawPixmap(imgX,imgY,pic);
}

void GameoverBlurEffectWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void GameoverBlurEffectWidget::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_tipLabel = new ShadowLabel(this);
    m_OverBtnGroup = new QButtonGroup(this);
    GameButton *againButton = BtnFactory::createBtn(ButtonNormal, Over, None, tr("Play Again"));
    GameButton *restButton = BtnFactory::createBtn(ButtonNormal, Over, None, tr("Have a Rest"));
    m_OverBtnGroup->addButton(againButton,0);
    m_OverBtnGroup->addButton(restButton,1);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(againButton,Qt::AlignLeft);
    buttonLayout->addWidget(restButton,Qt::AlignRight);
    mainLayout->addWidget(m_tipLabel,Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout,Qt::AlignBottom);
    mainLayout->setContentsMargins(295,370,295,171);
}

void GameoverBlurEffectWidget::initConnect()
{
    connect(m_OverBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &GameoverBlurEffectWidget::onButtonPressed);
}

void GameoverBlurEffectWidget::updateLabel(QString text)
{
    m_Text = text;
    m_tipLabel->setText(m_Text);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(8);
    effect->setYOffset(4);
    effect->setXOffset(0);
    QColor shadowColor(108,69,25);
    shadowColor.setAlphaF(0.6);
    effect->setColor(shadowColor);

    m_tipLabel->setGraphicsEffect(effect);
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
        Q_EMIT hideBlurWindow();
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


