#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QDebug>
#include<QMenu>
#include<QAction>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
    //记录当前本关的关卡号
    int leaveIndex;
    void paintEvent(QPaintEvent *);

    //游戏二维数组 维护里面金币或银币优势
    int gameArray[4][4];

    //存放金币的二维数组
    MyCoin *coinBtn[4][4];

    //是否胜利的标志
    bool isWin;

signals:
   void chooseScenceBack();
public slots:
};

#endif // PLAYSCENE_H
