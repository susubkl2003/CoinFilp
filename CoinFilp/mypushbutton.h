#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImg;
    QString pressImg;

    //向下跳跃
    void Jump1();
    //向上跳跃
    void Jump2();

    //鼠标按下
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
