#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "gamebutton.h"

#include <QObject>
#include <QMap>

class BtnFactory{
public:
    static GameButton * createBtn(const GameBtnFlag &flag,const QString &text,QWidget *parent=nullptr){
        GameButton *btn=nullptr;
        switch (flag) {
             case control:{
                btn=new GameButton(QIcon(QPixmap::fromImage(QImage(":/images/big.svg"))),text,parent);
                btn->setGeometry(100,100,230,120);
             }
        }
        return  btn;
    }
};


class GameControl : public QObject
{
    Q_OBJECT
public:
    static GameControl& GameInterFace(){
        static GameControl control;
        return  control;
    }
    //
    void gameBegin(int row,int column);//游戏开始
    void gameReset();//游戏重置
//    bool bfs();//搜索
//    bool judge();//判断是否为死局
    QMap<QPair<int,int>,GameBtnFlag>&gameMap();//游戏地图
signals:

public slots:

private:
    explicit GameControl(QObject *parent = nullptr);
private:
    int m_row=0;
    int m_column=0;
    QMap<QPair<int,int>,GameBtnFlag>m_map;
    QVector<GameBtnFlag>m_vec;
};

#endif // GAMECONTROL_H
