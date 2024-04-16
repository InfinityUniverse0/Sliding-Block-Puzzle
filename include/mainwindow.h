#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//从此处开始
#include <QPushButton>
#include <cmath>
#include <algorithm>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QLabel>
#include <QImage>
#include <QKeyEvent>

#include <QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QSound>

#include "coordinate.h"
#include "levelwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //从这里开始
public:
    void update(int a,int b); // 滑动滑块操作 更新
    void timeoutShow(); //游戏计时模块
    void restartGame(int X = 0); //重新开始游戏
    void keyPressEvent(QKeyEvent *event);


private:
    int N; //滑块个数

    Coordinate *Void;

    QPushButton *Block;

    static long long int totalSteps;
    QLabel *step;
    QLabel *time;
    bool isBegin;
    QTimer *timer;
    QDateTime *startTime;
    long long int interval;//记录游戏用时

    QSound *blockAudio;
    QMediaPlaylist *musicList;
    QMediaPlayer *musicPlayer;

    //背景音乐开关
    QPushButton *pureMusic1;//音乐：开
    QPushButton *pureMusic0;//音乐：关
    //音效开关
    bool audioOn;
    QPushButton *audioBtn1;//音效：开
    QPushButton *audioBtn0;//音效：关

};
#endif // MAINWINDOW_H
