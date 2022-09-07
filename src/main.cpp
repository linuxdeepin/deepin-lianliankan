// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "environments.h"
#include "source/mainwindow.h"
#include "source/lianliankanapplication.h"

#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>
#include <DLog>

#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QButtonGroup>
#include <QTime>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    LianLianKanApplication a(argc, argv);

    //单例模式
    if (!DGuiApplicationHelper::instance()->setSingleInstance(a.applicationName(), DGuiApplicationHelper::UserScope)) {
        a.activeWindow();
        return 0;
    }
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAutoActivateWindows(true);
    a.loadTranslator();
    a.setApplicationVersion(VERSION);
    a.setOrganizationName("deepin");
    a.setApplicationName("deepin-lianliankan");
    a.setProductIcon(QIcon::fromTheme("com.deepin.lianliankan"));
    a.setProductName(DApplication::translate("Main", "LianLianKan"));
    a.setApplicationDescription(DApplication::translate("Main", "Lianliankan is a puzzle game."));
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "LianLianKan"));
    a.setProductName(QCoreApplication::translate("Main", "LianLianKan"));

    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();
    DApplicationSettings saveTheme;

    //                QTime t;
    //                t.start();
    MainWindow w;
    Dtk::Widget::moveToCenter(&w);
    w.show();
    //          qInfo()<<t.elapsed()<<"time";
    return a.exec();
}
