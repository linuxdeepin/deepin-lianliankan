#ifndef MAINWIDNOW_H
#define MAINWIDNOW_H

#include <DMainWindow>
#include <DButtonBox>

DWIDGET_USE_NAMESPACE

class GameWindow;
class MainWidnow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWidnow(QWidget *parent = nullptr);

signals:

public slots:
   void onButtonPressed(QAbstractButton *btn);
private:
   void initUI();
   void initConnect();
protected:
   void paintEvent(QPaintEvent *event) override;
private:
    DButtonBox *m_btnBox;
    GameWindow *m_gameWindow;

};

#endif // MAINWIDNOW_H
