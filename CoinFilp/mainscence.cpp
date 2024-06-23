#include "mainscence.h"
#include "ui_mainscence.h"
#include<QPainter>
#include<QTimer>
#include<QSound>
MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);
   // 点击开始 - 退出游戏
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });
    //设置固定大小
      this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //开始按钮的创建
        MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
        startBtn->setParent(this);
        startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

        //准备开始按钮音效
        QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
        //设置循环次数
        startSound->setLoops(-1);//如果是-1代表无限循环
   //创建出第二个界面 - 选择关卡
          chooseScence = new ChooesLevelscreen;


          //监听第二个选择关卡场景中的返回按钮的信号
          connect(chooseScence,&ChooesLevelscreen::chooseScenceBack,[=](){
              chooseScence->hide();
              //将自身的位置同步为选择关卡场景的位置
               this->setGeometry(chooseScence->geometry());
              this->show();
          });

        connect(startBtn,&MyPushButton::clicked,[=](){
            //qDebug()<<"点击了开始按钮";
            //播放开始的音效
            startSound->play();
            //设置开始按钮的点击效果
            startBtn->Jump1();
            startBtn->Jump2();
            //延时 进入到第二个界面
            QTimer::singleShot(500,this,[=](){
                //将自身隐藏调用
                this->hide();
                //进入到第二个界面 - 选择关卡

               chooseScence->setGeometry(this->geometry());
                chooseScence->show();

            });

        });
}
void MainScence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画标题图片
    pix.load(":/res/Title.png");
    //缩放原始图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);



}

MainScence::~MainScence()
{
    delete ui;
}
