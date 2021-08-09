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
#include "llkstyle.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QApplication>

static QWindow *qt_getWindow(const QWidget *widget)
{
    return widget ? widget->window()->windowHandle() : nullptr;
}

LLKStyle::LLKStyle()
{

}

void LLKStyle::drawControl(QStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *widget) const
{
        if(ce==QStyle::CE_PushButtonLabel){
            if (const QStyleOptionButton *button = qstyleoption_cast<const QStyleOptionButton *>(opt)) {
                QRect textRect = button->rect;
                uint tf = Qt::AlignVCenter | Qt::TextShowMnemonic;
                if (! proxy()->styleHint(SH_UnderlineShortcut, button, widget))
                    tf |= Qt::TextHideMnemonic;

                if (!button->icon.isNull()) {
                    //Center both icon and text
                    QRect iconRect;
                    QIcon::Mode mode = button->state & State_Enabled ? QIcon::Normal : QIcon::Disabled;
                    if (mode == QIcon::Normal && button->state & State_HasFocus)
                        mode = QIcon::Active;
                    QIcon::State state = QIcon::Off;
                    if (button->state & State_On)
                        state = QIcon::On;

                    QPixmap pixmap = button->icon.pixmap(qt_getWindow(widget), button->iconSize, mode, state);

                    int pixmapWidth = pixmap.width() / pixmap.devicePixelRatio();
                    int pixmapHeight = pixmap.height() / pixmap.devicePixelRatio();
                    int labelWidth = pixmapWidth;
                    int labelHeight = pixmapHeight;
                    int iconSpacing = 4;//### 4 is currently hardcoded in QPushButton::sizeHint()
                    int textWidth = button->fontMetrics.boundingRect(opt->rect, tf, button->text).width();
                    if (!button->text.isEmpty())
                        labelWidth += (textWidth + iconSpacing);

                    iconRect = QRect(textRect.x() + (textRect.width() - labelWidth) / 2,
                                     textRect.y() + (textRect.height() - labelHeight) / 2,
                                     pixmapWidth, pixmapHeight);

                    iconRect = visualRect(button->direction, textRect, iconRect);

                    tf |= Qt::AlignLeft; //left align, we adjust the text-rect instead

                    if (button->direction == Qt::RightToLeft)
                        textRect.setRight(iconRect.left() - iconSpacing);
                    else
                        textRect.setLeft(iconRect.left() + iconRect.width() + iconSpacing);

                    if (button->state & (State_On | State_Sunken))
                        iconRect.translate(proxy()->pixelMetric(PM_ButtonShiftHorizontal, opt, widget),
                                           proxy()->pixelMetric(PM_ButtonShiftVertical, opt, widget));
                    p->drawPixmap(iconRect, pixmap);
                } else {
                    tf |= Qt::AlignHCenter;
                }
                if (button->state & (State_On | State_Sunken))
                    textRect.translate(proxy()->pixelMetric(PM_ButtonShiftHorizontal, opt, widget),
                                 proxy()->pixelMetric(PM_ButtonShiftVertical, opt, widget));

                if (button->features & QStyleOptionButton::HasMenu) {
                    int indicatorSize = proxy()->pixelMetric(PM_MenuButtonIndicator, button, widget);
                    if (button->direction == Qt::LeftToRight)
                        textRect = textRect.adjusted(0, 0, -indicatorSize, 0);
                    else
                        textRect = textRect.adjusted(indicatorSize, 0, 0, 0);
                }
                proxy()->drawItemText(p, textRect, tf, button->palette, (button->state & State_Enabled),
                             button->text, QPalette::ButtonText);
            }
        }else {
            DStyle::drawControl(this,static_cast<DStyle::ControlElement>(ce) , opt, p, widget);
        }
}

