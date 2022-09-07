// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>
#include <stub.h>

#include <lianliankanapplication.h>

#include <QDebug>

TEST(UT_LianLianKanApplication, UT_LianLianKanApplication_handleQuitAction)
{
    int argc = 0;
    char **argv;
    LianLianKanApplication *app = new LianLianKanApplication(argc, argv);
    app->handleQuitAction();
    EXPECT_NE(app, nullptr) << "check the status after UT_LianLianKanApplication_handleQuitAction()";
    app->deleteLater();
}
