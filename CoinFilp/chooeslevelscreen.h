#ifndef CHOOESLEVELSCREEN_H
#define CHOOESLEVELSCREEN_H

#include <QMainWindow>
#include"playscene.h"
class ChooesLevelscreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooesLevelscreen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    //维护游戏场景的指针
    PlayScene *playScene;
signals:
    //自定义的信号，只需要声明，不需要实现
     void chooseScenceBack();
public slots:
};

#endif // CHOOESLEVELSCREEN_H
