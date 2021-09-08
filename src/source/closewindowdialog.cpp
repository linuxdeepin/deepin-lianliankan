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
    setIcon(QIcon::fromTheme("dialog-warning"));
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

    if (index == CloseButtonType::close) {
        setResult(QMessageBox::Ok);
    } else {
        setResult(QMessageBox::No);
    }
}





