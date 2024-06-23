#include "mycoin.h"
#include<QMessageBox>
#include<QPixmap>
#include<QString>
MyCoin::MyCoin(QString coinImg)
{
  QPixmap pix;
  bool ret = pix.load(coinImg);

  if(!ret){
      QString str = QString("图片加载失败 %1").arg(coinImg);
      QMessageBox::critical(this,"加载失败",str);
      return;
  }

  this->setFixedSize(pix.width(),pix.height());
  this->setStyleSheet("QPushButton{border:0px;}");
  this->setIcon(pix);
  this->setIconSize(QSize(pix.width(),pix.height()));
  timer1 = new QTimer(this);
  timer2 = new QTimer(this);
  isAnimation = false;

  isWin = false;
  //监听定时器
  connect(timer1,&QTimer::timeout,[=](){
      QPixmap pix;
      QString str = QString(":res/Coin000%1.png").arg(this->min++);
      pix.load(str);
      this->setFixedSize(pix.width(),pix.height());
      this->setStyleSheet("QPushButton{border:0px;}");
      this->setIcon(pix);
      this->setIconSize(QSize(pix.width(),pix.height()));
      //如果显示到了最后一张，停止定时器
      if(this->min>this->max){
          this->min =1;
          timer1->stop();
          isAnimation = false;
      }
  });
  //监听定时器
  connect(timer2,&QTimer::timeout,[=](){
      QPixmap pix;
      QString str = QString(":res/Coin000%1.png").arg(this->max--);
      pix.load(str);
      this->setFixedSize(pix.width(),pix.height());
      this->setStyleSheet("QPushButton{border:0px;}");
      this->setIcon(pix);
      this->setIconSize(QSize(pix.width(),pix.height()));
      //如果显示到了最后一张，停止定时器
      if(this->max < this->min){
          this->max =8;
          timer2->stop();
          isAnimation = false;//动画结束后，还原动画标志
      }
  });
}

//改变标志，执行翻转效果
void MyCoin::chageFlag(){
    isAnimation = true;
    if(this->flag){
        //开启正面 翻 反面 的定时器
        timer1->start(30);
        this->flag = false;
    }
    else{
        timer2->start(30);
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation|| this->isWin){
        //如果正在做动画，直接返回
        return;
    }
    else{
        //如果是其他情况，则直接交给父类去处理
       QPushButton::mousePressEvent(e);
    }
}
