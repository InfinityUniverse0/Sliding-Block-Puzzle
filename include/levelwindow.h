#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class LevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelWindow(QWidget *parent = nullptr);

signals:

public:
    QLabel *title;

    QPushButton *easyLevel;
    QPushButton *normalLevel;
    QPushButton *crazyLevel;

    QPushButton *backGame;

    //背景图片
    QLabel *backPic;


};

#endif // LEVELWINDOW_H
