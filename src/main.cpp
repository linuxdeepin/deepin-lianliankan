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
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAutoActivateWindows(true);
    a.loadTranslator();
    a.setApplicationVersion(VERSION);
    a.setOrganizationName("deepin");
    a.setApplicationName("com.deepin.lianliankan");
    a.setProductIcon(QIcon(":/assets/images/deepin-lianliankan.svg"));
    a.setProductName(DApplication::translate("Main", "LianLianKan"));
    a.setApplicationDescription(DApplication::translate("Main", "Lianliankan is a puzzle game."));
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "LianLianKan"));
    a.setProductName(QCoreApplication::translate("Main", "LianLianKan"));

    //单例模式
    if (!a.setSingleInstance(a.applicationName()))
        exit(-1);

    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();
    DApplicationSettings saveTheme;

    //            QTime t;
    //            t.start();
    MainWindow w;
    w.titlebar()->setIcon(QIcon(":/assets/images/com.deepin.lianliankan.svg"));
    // 设置标题，宽度不够会隐藏标题文字
    w.setFixedSize(QSize(1024,768));
    Dtk::Widget::moveToCenter(&w);
    w.show();
    //            qInfo()<<t.elapsed()<<"time";
    return a.exec();
}
