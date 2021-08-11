#include "gamewindow.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>

GameWindow::GameWindow(int row,int column,QWidget *parent) : DMainWindow(parent),m_row(row),m_column(column)
{

    initUI();

}

void GameWindow::closeEvent(QCloseEvent *event)
{
    Q_EMIT exitWindow();
    return DMainWindow::closeEvent(event);
}

void GameWindow::paintEvent(QPaintEvent *event)
{
      QPainter p(this);
      p.drawPixmap(rect(),QPixmap(":/assets/images/background.png"));
      DMainWindow::paintEvent(event);
}

void GameWindow::initUI()
{
    setFixedSize(QSize(1024,718));
    QHBoxLayout *mainLayout=new QHBoxLayout;
    QVBoxLayout *configLayout=new QVBoxLayout;

    m_btnBox=new DButtonBox;
    m_btnBox->setOrientation(Qt::Vertical);
    m_btnBox->addAction(new QAction(tr("begin")));
    m_progress=new DProgressBar;
    m_progress->setRange(0,100);
    configLayout->addWidget(m_progress);
    configLayout->addWidget(m_btnBox);

    GameFrame *gameFrame=new GameFrame(m_row,m_column);


    mainLayout->addWidget(gameFrame);
    mainLayout->addLayout(configLayout);
    auto centerWidget=new QWidget;
    centerWidget->setLayout(mainLayout);
    setCentralWidget(centerWidget);
}
