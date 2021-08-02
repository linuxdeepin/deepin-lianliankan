#include "mainwidnow.h"
#include "gamewindow.h"
#include "global.h"

#include <DLabel>

#include <QVBoxLayout>

MainWidnow::MainWidnow(QWidget *parent):DMainWindow (parent)
{
   initUI();
   initConnect();
}

void MainWidnow::onButtonPressed(QAbstractButton *btn)
{
    const QString btnName=btn->objectName();
    if(btnName=="element"){
        m_gameWindow=new GameWindow(ElementRow,ElementCocolumn);
        this->setHidden(true);
        m_gameWindow->show();
        qInfo()<<"element";
    }else if (btnName=="inter") {
        qInfo()<<"inter";
    }else {
        qInfo()<<"advance";
    }
    QObject::connect(m_gameWindow,&GameWindow::exitWindow,[this]{
        this->m_btnBox->update();
        this->setHidden(false);
    });
}

void MainWidnow::initUI()
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    m_btnBox=new DButtonBox(this);
    m_btnBox->setOrientation(Qt::Vertical);
    m_btnBox->setMinimumSize(200,200);
    DButtonBoxButton * elementBtn=new DButtonBoxButton(tr("easy"),m_btnBox);
    elementBtn->setObjectName("element");
    DButtonBoxButton * interBtn=new DButtonBoxButton(tr("middle"),m_btnBox);
    interBtn->setObjectName("inter");
    DButtonBoxButton * advanceBtn=new DButtonBoxButton(tr("high"),m_btnBox);
    advanceBtn->setObjectName("advance");
    QList<DButtonBoxButton*>btnList;
    btnList.append(elementBtn);
    btnList.append(interBtn);
    btnList.append(advanceBtn);
    m_btnBox->setButtonList(btnList,false);

    DLabel *diffLabel=new DLabel (tr("pelase choose"));
    mainLayout->addWidget(diffLabel,1,Qt::AlignBottom|Qt::AlignHCenter);
    mainLayout->addWidget(m_btnBox,2,Qt::AlignTop|Qt::AlignHCenter);
    auto centerWidget=new  QWidget;
    centerWidget->setLayout(mainLayout);
    setCentralWidget(centerWidget);
}

void MainWidnow::initConnect()
{
   QObject::connect(m_btnBox,&DButtonBox::buttonPressed,this,&MainWidnow::onButtonPressed);

}

void MainWidnow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/images/background.png"));
    DMainWindow::paintEvent(event);
}
