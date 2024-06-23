#include "playscene.h"
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
PlayScene::PlayScene(int index)
{
//    QString str = QString("现在是第 %1 关").arg(index);
//    qDebug()<<str;

    this->leaveIndex = index;
    //设置固定大小
      this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币场景");
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *bar =menuBar();
    this->setMenuBar(bar);

    //创建菜单
    QMenu *startMenu = bar->addMenu("开始");

    //创建菜单项
    QAction *quitAction = startMenu->addAction("退出");

    //点击退出按钮 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //默认未胜利
    isWin = false;

    //显示具体关卡号
    QLabel *label = new QLabel;
    label->setParent(this);
    QString str = QString("level:%1").arg(this->leaveIndex);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    //让创建的label使用上面的字体
    label->setFont(font);
    label->setText(str);
    //设置位置

    label->setGeometry(QRect(30,this->height()-60,150,60));

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //金币翻转音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //游戏胜利音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //返回按钮的创建
     MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
     backBtn->setParent(this);
     backBtn->move(this->width()-backBtn->width()-5,this->height()-backBtn->height()-10);
     connect(backBtn,&MyPushButton::clicked,[=](){
           //
         backSound->play();
         QTimer::singleShot(300,this,[=](){
              emit this->chooseScenceBack();

         });

     });

     DataConfig data;
     //初始化游戏中的二维数组
     for(int i=0;i<4;i++){
         for(int j=0;j<4;j++){
            this->gameArray[i][j] = data.mData[this->leaveIndex][i][j];
         }
     }

     //创建胜利的图片
     QLabel *winLabel = new QLabel;
     QPixmap pix;
     pix.load(":/res/LevelCompletedDialogBg.png");
     winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
     winLabel->setParent(this);
     winLabel->setPixmap(pix);
     winLabel->move((this->width()-pix.width())*0.5,-pix.height());

     //创建金币的背景图片
     for(int i=0;i<4;i++){
         for(int j=0;j<4;j++){
             QLabel *bg =new QLabel(this);
             QPixmap pix;
             pix.load(":/res/BoardNode.png");
             bg->setGeometry(0,0,pix.width(),pix.height());
             bg->setPixmap(pix);
             bg->move(57+i*50,200+j*50);

             //创建金币
             QString str;
             if(this->gameArray[i][j] ==1){
                 //为1就是金币
               str=":/res/Coin0001.png";
             }else{
                 //其他情况是银币
                str=":/res/Coin0008.png";
             }
             MyCoin *coin = new MyCoin(str);
             coin->setParent(this);
             coin->posX =i;
             coin->posY = j;
             coin->flag = this->gameArray[i][j];
             coin->move(59+i*50,204+j*50);

              //将coin放入到维护的金币的二维数组
             coinBtn[i][j] = coin;
             connect(coin,&MyCoin::clicked,[=](){
                 //翻动金币音效
                 flipSound->play();
                 //在翻动金币时，禁用其他金币的点击事件
                 for(int i=0;i<4;i++){
                     for(int j=0;j<4;j++){
                       this->coinBtn[i][j]->isWin = true;
                     }}

                 coin->chageFlag();
                 gameArray[i][j] = gameArray[i][j] == 0?1:0;
                 //继续翻动周围的硬币

                 //延时翻周围的金币
                 QTimer::singleShot(200,this,[=](){
                     //检测翻右侧金币
                     if(coin->posX+1<=3){
                         coinBtn[coin->posX+1][coin->posY]->chageFlag();
                         gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                     }
                     //检测翻左侧金币
                     if(coin->posX-1>=0){
                         coinBtn[coin->posX-1][coin->posY]->chageFlag();
                         gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                     }
                     //检测翻上侧金币
                     if(coin->posY-1>=0){
                         coinBtn[coin->posX][coin->posY-1]->chageFlag();
                         gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1] ==0?1:0;
                     }
                     //检测翻下侧金币
                     if(coin->posY+1<=3){
                         coinBtn[coin->posX][coin->posY+1]->chageFlag();
                         gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1] ==0?1:0;
                     }

                      //在翻完金币后，打开其他金币的点击效果
                     for(int i=0;i<4;i++){
                         for(int j=0;j<4;j++){
                           this->coinBtn[i][j]->isWin = false;
                         }}
                     //在翻完周围金币后检测游戏是否胜利
                     this->isWin = true;
                     for(int i=0;i<4;i++){
                         for(int j=0;j<4;j++){
                             if(coinBtn[i][j]->flag == false){
                                 this->isWin = false;
                                 break;
                             }
                         }
                     }

                     if(this->isWin==true){
//                         qDebug()<<"游戏胜利";
                         winSound->play();
                         for(int i=0;i<4;i++){
                             for(int j=0;j<4;j++){
                                 coinBtn[i][j]->isWin = true;
                             }
                         }
                         //将胜利的标志显示出来
                         QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                         animation->setDuration(1000);
                         animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                         animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                         animation->setEasingCurve(QEasingCurve::OutBounce);
                         animation->start();
                     }
                 });

             });
         }
     }
}
void PlayScene::paintEvent(QPaintEvent *){
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
