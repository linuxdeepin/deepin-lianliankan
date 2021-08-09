#include "gameframe.h"
#include "gamecontrol.h"

#include <DPalette>
#include <DApplicationHelper>
#include <DWindowManagerHelper>

#include <QGridLayout>
#include <QPainter>
#include <QStyleOptionFrame>
#include <QRgba64>


GameFrame::GameFrame(int row,int column,QWidget *parent) : DBlurEffectWidget(parent),m_row(row),m_column(column)
{
    QGridLayout *mainLayout=new QGridLayout;


    GameControl::GameInterFace().gameBegin(m_row,m_column);
    QMap<QPair<int, int>, GameBtnFlag> &gameMap=GameControl::GameInterFace().gameMap();
//    for (int i=0;i<gameMap.size();i++) {
//       GameButton *btn=new GameButton ((gameMap.begin()+i).value());
//       mainLayout->addWidget(btn,(gameMap.begin()+i).key().first,(gameMap.begin()+i).key().second);
//    }
    qInfo()<<DWindowManagerHelper::instance()->hasComposite();
    this->setMaskColor(QColor(Qt::blue));
    this->setBlendMode(InWindowBlend);
    this->setFull(true);
    this->setBlurRectXRadius(9);
    this->setBlurRectYRadius(9);
    this->setMaskAlpha(10);
    this->setLayout(mainLayout);
}
