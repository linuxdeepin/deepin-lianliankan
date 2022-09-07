// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CLOSEWINDOWDIALOG_H
#define CLOSEWINDOWDIALOG_H

#include "global.h"

#include <DDialog>
#include <DLabel>

DWIDGET_USE_NAMESPACE
class CloseWindowDialog : public DDialog
{
    Q_OBJECT

public:
    explicit CloseWindowDialog(QWidget *parent = nullptr);
    /**
     * @brief result Get standard button enum result
     * @return Standard button enum result
     */
    inline int result() { return m_result; }
    /**
     * @brief setResult Set standard button enum result
     * @param r Standard button enum result
     */
    inline void setResult(int r) { m_result = r; }
private:
    void initUI();

private:
    DLabel *m_detailLabel;
    int m_result {0};

public slots:
    void onButtonClicked(int index, const QString &text);

};

#endif // CLOSEWINDOWDIALOG_H
