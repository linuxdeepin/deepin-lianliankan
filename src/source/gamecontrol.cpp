#include "gamecontrol.h"

#include<algorithm>

#include "time.h"

GameControl::GameControl(QObject *parent) : QObject(parent)
{



}

void GameControl::gameBegin(int row,int column)
{
   m_row=row;
   m_column=column;


   for (int i=0;i<GAMEROW*GAMECOLUMN;i+=14) {
       for (int j=0;j<14;j++) {
          m_vec.append(GameBtnFlag(i/14+1));
       }
   }


   srand(static_cast<unsigned>(time(nullptr)));
   std::random_shuffle(m_vec.begin(),m_vec.begin()+GAMEROW*GAMECOLUMN);

   int k=0;
   for (int i=0;i<row+2;i++) {
       for (int j=0;j<column+2;j++) {
           if(i==0||j==0||i==row+1||j==column+1){
              m_map.insert(QPair<int,int>(i,j),GameBtnFlag(0));
           }else {
              m_map.insert(QPair<int,int>(i,j),m_vec.at(k));
              k++;
           }
       }
   }

}

void GameControl::gameReset()
{
   m_vec.clear();
   m_map.clear();
   gameBegin(m_row,m_column);
}

QMap<QPair<int, int>, GameBtnFlag>& GameControl::gameMap()
{
    return  m_map;
}
