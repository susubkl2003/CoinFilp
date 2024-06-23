#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImg = normalImg;
    this->pressImg = pressImg;

    QPixmap pix;
    bool ret = pix.load(this->normalImg);
    if(!ret){
        QString str = QString("%1 图片加载失败").arg(this->normalImg);
        qDebug()<<str;
        return;
    }

    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图片
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
//向下跳跃
void MyPushButton::Jump1(){
 QPropertyAnimation *animation =new QPropertyAnimation(this,"geometry");

 //设置时间间隔
  animation->setDuration(200);
 //设置动画对象的起始位置
 animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
 //设置动画对象的终止位置
 animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
 //执行动画
 animation->start();

}
//向上跳跃
void MyPushButton::Jump2(){
    QPropertyAnimation *animation =new QPropertyAnimation(this,"geometry");

    //设置时间间隔
     animation->setDuration(200);
    //设置动画对象的起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画对象的终止位置
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    //执行动画
    animation->start();
}

//鼠标按下的事件
void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImg != ""){
        QPixmap pix;
        bool ret = pix.load(this->pressImg);
        if(!ret){
            qDebug()<<"加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //其他的事件，父类会处理
    QPushButton::mousePressEvent(e);

}

//鼠标释放的事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImg != ""){
        QPixmap pix;
        bool ret = pix.load(this->normalImg);
        if(!ret){
            qDebug()<<"加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    QPushButton::mouseReleaseEvent(e);
}
