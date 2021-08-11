#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "gamebutton.h"

#include <QObject>
#include <QMap>
#include <QImageReader>

class BtnFactory{
public:
    static GameButton * createBtn(const GameBtnFlag &flag,const GameBtnSize &btnSize ,const GameIconType &iconType,const QString &text=" ",QWidget *parent=nullptr){
        GameButton *btn=nullptr;
        QImageReader imageReader;
        QSize scaledSize;
        QPixmap *btnIcon=nullptr;
        switch (iconType) {
           case Sound:
            break;
           case Begin:
            break;
           case Reset:
            break;
           case Hint:
            break;
           case Home:
            break;
           default:
            break;
        }


        switch (btnSize) {
        case Big:
            scaledSize=QSize(250,135);
            break;
        case Mid:
            scaledSize=QSize(200,115);
            break;
        case Small:
            scaledSize=QSize(140,80);
            break;
        default:
            scaledSize=QSize(50,50);
        }

        if(flag==ButtonNormal){
            imageReader.setFileName(":/assets/images/normal.svg");
            imageReader.setScaledSize(scaledSize);

            if(!btnIcon){
                btn=new GameButton(QPixmap::fromImageReader(&imageReader),text,parent);
            }else {
                btn=new GameButton(QPixmap::fromImageReader(&imageReader),*btnIcon,parent);
            }

        }else {
            imageReader.setFileName(":/assets/images/normal.svg");
            imageReader.setScaledSize(scaledSize);
            btn=new GameButton (QPixmap::fromImageReader(&imageReader),parent);
        }

        btn->setFixedSize(scaledSize);
        btn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
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
