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
