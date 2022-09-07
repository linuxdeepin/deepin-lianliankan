// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "shadowlabel.h"

#include <QGraphicsDropShadowEffect>

ShadowLabel::ShadowLabel(QWidget *parent) : DLabel (parent)
{
    m_font.setFamily("Noto Sans CJK SC");
    m_font.setPixelSize(21);
    m_font.setWeight(580);
    setFont(m_font);
}

void ShadowLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QString text = this->text();
    QPainter painterText(this);
    painterText.setRenderHint(QPainter::Antialiasing, true);

    QFontMetrics fm(m_font);
    //设置渐变区域,参数为区域右上角和右下角。表示垂直线性渐变
    QLinearGradient lg(rect().width()/2 - fm.width(text)/2,
                       rect().y(),
                       rect().width()/2 - fm.width(text)/2,
                       rect().y() + fm.height());
    lg.setSpread(QGradient::RepeatSpread);
    if (m_result) {
        lg.setColorAt(0.12, QColor("#F2EB79"));
        lg.setColorAt(0.35, QColor("#F1EB6E"));
        lg.setColorAt(0.81, QColor("#DE8A4C"));
        lg.setColorAt(1, QColor("#D56B39"));

    } else {
        lg.setColorAt(0.12, QColor("#FFFFFF"));
        lg.setColorAt(0.46, QColor("#D4D4D4"));
        lg.setColorAt(0.81, QColor("#9A9A9A"));
        lg.setColorAt(1, QColor("#3F3F3F"));
    }
    painterText.setOpacity(1);
    QPen textcolor;
    textcolor.setBrush(lg);
    painterText.setPen(textcolor);
    painterText.drawText(QRectF(rect().width()/2 - fm.width(text)/2,
                         rect().y(),
                         fm.width(text),
                         fm.height()), text);
}
