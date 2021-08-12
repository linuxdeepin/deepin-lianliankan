#include "gamewindow.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAction>
#include <DFrame>

GameWindow::GameWindow(int row,int column,QWidget *parent) : QWidget(parent),m_row(row),m_column(column)
{

    initUI();

}

//void GameWindow::closeEvent(QCloseEvent *event)
//{
//    Q_EMIT exitWindow();
//    return QWidget::closeEvent(event);
//}

//void GameWindow::paintEvent(QPaintEvent *event)
//{
//      QPainter p(this);
//      p.drawPixmap(rect(),QPixmap(":/assets/images/background.png"));
//      QWidget::paintEvent(event);
//}

void GameWindow::initUI()
{
    setFixedSize(QSize(1024,718));
    setContentsMargins(0,71,15,43);
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);

    //游戏操作区域
    DFrame *gameControlFrame = new DFrame(this);
    gameControlFrame->setContentsMargins(0,0,0,0);
//    gameControlFrame->setMinimumSize(1009,546);
    gameControlFrame->setFrameRounded(false);
    gameControlFrame->setFrameShape(QFrame::NoFrame);
    QHBoxLayout *controlLayout=new QHBoxLayout();
    gameControlFrame->setLayout(controlLayout);
    //左侧网格操作区
    GridBlurEffectWidget *gridFrame = new GridBlurEffectWidget(15,15,816,516,this);
    gridFrame->setContentsMargins(0,0,0,0);
//    gridFrame->setMinimumSize(846,546);
//    QGridLayout *gridControlLayout = new QGridLayout(this);
//    gridFrame->setLayout(gridControlLayout);
    controlLayout->addWidget(gridFrame);
    //右侧按钮区
    GridBlurEffectWidget *btnFrame = new GridBlurEffectWidget(846,15,163,516,this);
    btnFrame->setContentsMargins(0,0,0,0);
    btnFrame->setMinimumSize(163,546);
    controlLayout->addWidget(btnFrame);


    mainLayout->addWidget(gameControlFrame);
    mainLayout->addStretch();



//    QVBoxLayout *btnLayout=new QVBoxLayout;

//    m_btnBox=new DButtonBox;
//    m_btnBox->setOrientation(Qt::Vertical);
//    m_btnBox->addAction(new QAction(tr("begin")));
//    m_progress=new DProgressBar;
//    m_progress->setRange(0,100);


//    GameFrame *gameFrame=new GameFrame(m_row,m_column);


//    mainLayout->addWidget(gameFrame);
//    auto centerWidget=new QWidget;
//    centerWidget->setLayout(mainLayout);
//    setCentralWidget(centerWidget);
}
