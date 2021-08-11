#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gameframe.h"

#include <DMainWindow>
#include <DProgressBar>
#include <DButtonBox>

DWIDGET_USE_NAMESPACE
class GameWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(int row,int column,QWidget *parent = nullptr);

signals:
    void exitWindow();
protected:
    void closeEvent(QCloseEvent *event)override;
    void paintEvent(QPaintEvent *event) override;
public slots:

private:
    void initUI();
private:
    DProgressBar *m_progress;
    DButtonBox  *m_btnBox;
    int m_row;
    int m_column;
};

#endif // GAMEWINDOW_H
