// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIANLIANKANAPPLICATION_H
#define LIANLIANKANAPPLICATION_H

#include <DApplication>

DWIDGET_USE_NAMESPACE
class LianLianKanApplication: public DApplication
{
    Q_OBJECT
public:
    explicit LianLianKanApplication(int &argc, char **argv);

protected:
    void handleQuitAction() override; //重写菜单退出事件
};

#endif // LIANLIANKANAPPLICATION_H
