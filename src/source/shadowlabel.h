// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
