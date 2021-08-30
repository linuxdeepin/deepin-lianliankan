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
