// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "closewindowdialog.h"

#include <DFontSizeManager>

#include <QApplication>
#include <QMap>
#include <QDebug>
#include <QMessageBox>


CloseWindowDialog::CloseWindowDialog(QWidget *parent)
    : DDialog(parent)
{
    qDebug() << "Enter CloseWindowDialog constructor";
    initUI();

    connect(this, &CloseWindowDialog::buttonClicked, this, &CloseWindowDialog::onButtonClicked);
    qDebug() << "Exit CloseWindowDialog constructor";
}

void CloseWindowDialog::initUI()
{
    qDebug() << "Enter initUI";
    //set icon
    setIcon(QIcon::fromTheme("com.deepin.lianliankan"));
    m_detailLabel = new DLabel(this);
    m_detailLabel->setWordWrap(true);
    m_detailLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_detailLabel->setText(tr("Are you sure you want to exit the game?"));
    QFont tipFont;
    tipFont.setFamily("Noto Sans CJK SC");
    tipFont.setWeight(QFont::DemiBold);
    tipFont.setPointSize(10);
    m_detailLabel->setFont(tipFont);
    addContent(m_detailLabel, Qt::AlignCenter);
    addSpacing(10);
    addButton(tr("Keep Playing"), true, ButtonNormal);
    addButton(tr("Exit"), true, ButtonNormal);
    qDebug() << "Exit initUI";
}

void CloseWindowDialog::onButtonClicked(int index, const QString &)
{
    qDebug() << "Enter onButtonClicked, index:" << index;
    if (index == CloseButtonType::CloseDialog) {
        qDebug() << "User chose to exit the game";
        setResult(QMessageBox::Ok);
    } else {
        qDebug() << "User chose to keep playing";
        setResult(QMessageBox::No);
    }
    qDebug() << "Exit onButtonClicked";
}





