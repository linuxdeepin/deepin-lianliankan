// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
