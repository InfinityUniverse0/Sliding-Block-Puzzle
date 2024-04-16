#include "levelwindow.h"

LevelWindow::LevelWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(400,500);
    this->setWindowTitle("难度设置");
    easyLevel = new QPushButton(this);
    normalLevel = new QPushButton(this);
    crazyLevel = new QPushButton(this);
    title = new QLabel(this);
    backGame = new QPushButton(this);

    easyLevel->setGeometry(75,100,250,75);
    normalLevel->setGeometry(75,200,250,75);
    crazyLevel->setGeometry(75,300,250,75);
    title->setGeometry(135,20,250,75);
    backGame->setGeometry(125,400,150,60);


    title->setFont(QFont("方正楷体",18));
    title->setText("难度设置");
    easyLevel->setFont(QFont("方正楷体",16));
    normalLevel->setFont(QFont("方正楷体",16));
    crazyLevel->setFont(QFont("方正楷体",16));
    easyLevel->setText("初级 3×3");
    normalLevel->setText("中级 4×4");
    crazyLevel->setText("高级 5×5");
    backGame->setFont(QFont("方正楷体",16));
    backGame->setText("返回");

    connect(easyLevel,&QPushButton::clicked,this,&LevelWindow::close);
    connect(normalLevel,&QPushButton::clicked,this,&LevelWindow::close);
    connect(crazyLevel,&QPushButton::clicked,this,&LevelWindow::close);
    connect(backGame,&QPushButton::clicked,this,&LevelWindow::close);


    //设置按钮透明度
    easyLevel->setStyleSheet("background-color:rgba(255,255,255,150)");
    normalLevel->setStyleSheet("background-color:rgba(255,255,255,150)");
    crazyLevel->setStyleSheet("background-color:rgba(255,255,255,150)");
    backGame->setStyleSheet("background-color:rgba(255,255,255,150)");
    //设置背景
    QImage *backImg = new QImage();
    backImg->load(":/image/image/level_background.jpg");
    backPic = new QLabel(this);
    backPic->setFixedSize(400,500);
    backPic->setPixmap(QPixmap::fromImage(*backImg));
    backPic->setScaledContents(true);
    backPic->lower();

}
