#include "chooeslevelscreen.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QSound>
#include"mypushbutton.h"
ChooesLevelscreen::ChooesLevelscreen(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
      this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *bar =menuBar();
    this->setMenuBar(bar);

    //创建菜单
    QMenu *startMenu = bar->addMenu("开始");

    //创建菜单项
    QAction *quitAction = startMenu->addAction("退出");

    //创建选择关卡的音效
    QSound *chooesSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //点击退出按钮 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

   //返回按钮的创建
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-5,this->height()-backBtn->height()-10);
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
          //
        QTimer::singleShot(300,this,[=](){
             emit this->chooseScenceBack();

        });

    });

    playScene = NULL;



    //选择关卡按钮
    for(int i=0;i<20;i++){
       MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
       menuBtn->setParent(this);
       menuBtn->move(25+(i%4)*70,130+(i/4)*70);

       connect(menuBtn,&MyPushButton::clicked,[=](){
//          QString str =QString("你选择的是 %1 关").arg(i+1);
//          qDebug()<<str;

           //点击选择的关卡触发音效
           chooesSound->play();
           //隐藏掉自身
           this->hide();
           playScene = new PlayScene(i+1);
           playScene->setGeometry(this->geometry());
           playScene->show();

           connect(playScene,&PlayScene::chooseScenceBack,[=](){
               //选择关卡的场景
               playScene->hide();
               this->setGeometry(playScene->geometry());
               QTimer::singleShot(300,this,[=](){
                    delete playScene;
                   playScene = NULL;
                   this->show();
               });
           });
       });

       QLabel *label = new QLabel(this);
       //设置大小
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       //设置文本内容
       label->setText(QString::number(i+1));
       //设置位置
       label->move(25+(i%4)*70,130+(i/4)*70);
       //设置居中效果
       label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       //设置鼠标穿透
       label->setAttribute(Qt::WA_TransparentForMouseEvents);//51 鼠标穿透

    }

}

void ChooesLevelscreen::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画标题图片
    pix.load(":/res/Title.png");
    //缩放原始图片
    pix = pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(10,30,pix);
}
