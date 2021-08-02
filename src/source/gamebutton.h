#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"

#include <DToolButton>
#include <DPushButton>

DWIDGET_USE_NAMESPACE
class GameButton : public DPushButton
{
    Q_OBJECT
public:
    explicit GameButton(GameBtnFlag flag, QWidget *parent = nullptr);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
   void initIcon(GameBtnFlag flag);
private:
   GameBtnFlag m_flag;
};

#endif // GAMEBUTTON_H
