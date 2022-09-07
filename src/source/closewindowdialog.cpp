// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "closewindowdialog.h"

#include <DApplicationHelper>
#include <DFontSizeManager>

#include <QApplication>
#include <QMap>
#include <QDebug>
#include <QMessageBox>


CloseWindowDialog::CloseWindowDialog(QWidget *parent)
    : DDialog(parent)
{
    initUI();

    connect(this, &CloseWindowDialog::buttonClicked, this, &CloseWindowDialog::onButtonClicked);
}

void CloseWindowDialog::initUI()
{
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
}

void CloseWindowDialog::onButtonClicked(int index, const QString &)
{
    if (index == CloseButtonType::CloseDialog) {
        setResult(QMessageBox::Ok);
    } else {
        setResult(QMessageBox::No);
    }
}





