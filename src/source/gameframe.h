#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <DFrame>
#include <DToolButton>
#include <DBlurEffectWidget>

DGUI_USE_NAMESPACE
DWIDGET_USE_NAMESPACE
class GameFrame : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit GameFrame(int row,int column,QWidget *parent = nullptr);

signals:

public slots:

protected:
//    void paintEvent(QPaintEvent *event) override;
private:
    int m_row=0;
    int m_column=0;
    QMap<QPair<int,int>,DToolButton*>m_map;

};

#endif // GAMEFRAME_H
