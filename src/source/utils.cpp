/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     linxun <linxun@uniontech.com>
*
* Maintainer: linxun <linxun@uniontech.com>
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
#include "utils.h"

#include <QImageReader>
#include <QApplication>
#include <QIcon>

QPixmap Utils::getDpiPixmap(QSize size, const QString &filename, DWidget *w)
{
    QPixmap pixmap;
    qreal devicePixelRatio = qApp->devicePixelRatio();
    if (w) {
        devicePixelRatio = w->devicePixelRatioF();
    }

    qreal ratio = 1.0;
    QImageReader reader;
    reader.setFileName(qt_findAtNxFile(filename, devicePixelRatio, &ratio));

    if (!qFuzzyCompare(ratio, devicePixelRatio)) {
        if (reader.canRead()) {
            QSize picSize;
            if (size != QSize(0, 0)) {
                picSize = size;
            } else {
                picSize = reader.size();
            }

            reader.setScaledSize(picSize * (devicePixelRatio / ratio));
            pixmap = QPixmap::fromImage(reader.read());
            pixmap.setDevicePixelRatio(devicePixelRatio);
        }
    } else {
        if (size != QSize(0, 0)) {
            reader.setScaledSize(size * (devicePixelRatio / ratio));
            pixmap = QPixmap::fromImage(reader.read());
        } else {
            pixmap.load(filename);
        }
    }
    return pixmap;
}
