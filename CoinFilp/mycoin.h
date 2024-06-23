#ifndef MYCOIN_H
#define MYCOIN_H
#include<QString>
#include<QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);

    //位置与正反标志
    int posX;
    int posY;
    bool flag;

    //改变标志 计时器 和图片拼接尾
    void chageFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min =1;
    int max = 8;

    //是否在执行动画的标识
    bool isAnimation;
    bool isWin;//是否胜利的标志

    void mousePressEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYCOIN_H
