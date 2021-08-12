#ifndef GRIDBLUREFFECTWIDGET_H
#define GRIDBLUREFFECTWIDGET_H

#include <DBlurEffectWidget>

DWIDGET_USE_NAMESPACE
class GridBlurEffectWidget : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit GridBlurEffectWidget(int x, int y, int width, int height, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event)override;
signals:

public slots:

private:
    int m_x = 0;
    int m_y = 0;
    int m_width = 0;
    int m_height = 0;
};


#endif // GRIDBLUREFFECTWIDGET_H
