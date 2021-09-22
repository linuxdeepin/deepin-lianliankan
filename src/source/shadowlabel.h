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
#ifndef SHADOWLABEL_H
#define SHADOWLABEL_H

#include <DLabel>

DWIDGET_USE_NAMESPACE
class ShadowLabel : public DLabel
{
    Q_OBJECT
public:
    explicit ShadowLabel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    /**
     * @brief setResult 提供外部设置私有变量值，获取游戏结果
     * @param res 游戏结果bool值
     */
    inline void setResult(bool res) {m_result = res;}

private:
    bool m_result = false;
    QFont m_font;
};

#endif // SHADOWLABEL_H
