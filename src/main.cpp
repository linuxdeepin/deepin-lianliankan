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
#if QT_VERSION_MAJOR <= 5
#include <DApplicationSettings>
#endif
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
    qDebug() << "Application starting...";
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    LianLianKanApplication a(argc, argv);

    //单例模式
    qInfo() << "Checking single instance...";
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
#if QT_VERSION_MAJOR <= 5
    DApplicationSettings saveTheme;
#endif

    //                QTime t;
    //                t.start();
    qDebug() << "Creating main window...";
    MainWindow w;
    Dtk::Widget::moveToCenter(&w);
    w.show();
    qDebug() << "Main window shown";
    //          qInfo()<<t.elapsed()<<"time";
    qDebug() << "Entering application event loop";
    return a.exec();
}
