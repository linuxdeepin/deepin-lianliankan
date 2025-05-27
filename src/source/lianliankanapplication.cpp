// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lianliankanapplication.h"
#include "mainwindow.h"

LianLianKanApplication::LianLianKanApplication(int &argc, char **argv)
    : DApplication (argc, argv)
{
    qDebug() << "Initializing LianLianKanApplication";

}

void LianLianKanApplication::handleQuitAction()
{
    qInfo() << "Handling application quit action";
    QWidget *pWgt = activeWindow();
    MainWindow *pWindow = qobject_cast<MainWindow *>(pWgt); //在对应的MainWindow操作

    // 处理点击退出事件
    if (pWindow) {
        qDebug() << "Closing main window from quit action";
        pWindow->close();
    }
}


