#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include"mypushbutton.h"
#include"chooeslevelscreen.h"
namespace Ui {
class MainScence;
}

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScence(QWidget *parent = 0);
    ~MainScence();
    void paintEvent(QPaintEvent *);
    ChooesLevelscreen *chooseScence;

private:
    Ui::MainScence *ui;
};

#endif // MAINSCENCE_H
