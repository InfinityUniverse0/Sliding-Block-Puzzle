#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //从此处开始
    N = 16;//滑块个数
    //滑块规格参数
    const int a=75;
    const int b=100;
    const int side=100;

    //获取1 - N-1的随机数
    int *p = new int[N-1]; //用于存储随机数
    for(int i=0;i<N-1;i++)
        p[i]=i+1;

    //序列随机排序
    using std::random_shuffle;
    std::srand(QTime::currentTime().msec()+QTime::currentTime().second()*1000);//使得每次均不同
    random_shuffle(p, p + N - 1); //注意范围

    Block = new QPushButton[N];
    for(int i=0;i<sqrt(N);i++){
        for(int j=0;j<sqrt(N);j++){
            Block[(int)(sqrt(N))*i+j].setParent(this);
            Block[(int)(sqrt(N))*i+j].setGeometry(a+side*j,b+side*i,side,side);
            connect(&Block[(int)(sqrt(N))*i+j],&QPushButton::clicked,this,[=](){
                this->update(i,j);
            });
            Block[(int)(sqrt(N))*i+j].setFont(QFont("HGB8X_CNKI",18));
            Block[(int)(sqrt(N)*i+j)].setStyleSheet("background-image: url(:/image/image/block.jpg);");
            Block[(int)(sqrt(N))*i+j].setFocusPolicy(Qt::NoFocus);//NoFocus
            if(!(i == sqrt(N)-1 && j == sqrt(N)-1))
                Block[(int)(sqrt(N))*i+j].setText(QString::number(p[(int)(sqrt(N))*i+j]));
        }
    }

    //回收
    delete[] p;

    //存储空滑块下标
    Void = new Coordinate(sqrt(N));



    //记步数
    step = new QLabel(this);
    step->setGeometry(650,200,400,50);
    step->setText("Steps:  "+QString::number(totalSteps));
    step->setFont(QFont("HGB8X_CNKI",18));

    //记时间
    time = new QLabel(this);
    time->setGeometry(650,300,400,50);
    time->setText("Time:   "+QString::number(0));
    time->setFont(QFont("HGB8X_CNKI",18));

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::timeoutShow);


    //准备开始计时工作
    isBegin = false;
    startTime = new QDateTime;//先分配内存


    //重新开始模块
    QPushButton *restart = new QPushButton(this);
    restart->setGeometry(575,400,150,50);
    restart->setText("重新开始");
    restart->setFont(QFont("方正楷体",14));
    connect(restart,&QPushButton::clicked,this,&MainWindow::restartGame);
    //设置边框
    restart->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    restart->setFocusPolicy(Qt::NoFocus);//NoFocus

    //难度选项模块
    QPushButton *level = new QPushButton(this);
    level->setGeometry(745,400,150,50);
    level->setText("难度设置");
    level->setFont(QFont("方正楷体",14));
    //设置边框
    level->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    level->setFocusPolicy(Qt::NoFocus);//NoFocus

    LevelWindow *levelWindow = new LevelWindow(nullptr);//必须是nullptr
    connect(level,&QPushButton::clicked,levelWindow,&LevelWindow::show);
    connect(level,&QPushButton::clicked,this,&MainWindow::hide);

    //以下，每对中connect顺序不可换
    connect(levelWindow->easyLevel,&QPushButton::clicked,this,[&](){
        this->restartGame(3);
    });
    connect(levelWindow->easyLevel,&QPushButton::clicked,this,&MainWindow::show);

    connect(levelWindow->normalLevel,&QPushButton::clicked,this,[&](){
        this->restartGame(4);
    });
    connect(levelWindow->normalLevel,&QPushButton::clicked,this,&MainWindow::show);

    connect(levelWindow->crazyLevel,&QPushButton::clicked,this,[&](){
        this->restartGame(5);
    });
    connect(levelWindow->crazyLevel,&QPushButton::clicked,this,&MainWindow::show);

    //返回按钮
    connect(levelWindow->backGame,&QPushButton::clicked,this,&MainWindow::show);



    //添加背景
    QImage *backImg = new QImage();
    backImg->load(":/image/image/background.png");
    QLabel *back = new QLabel(this);
    back->setFixedSize(1000,618);
    back->setPixmap(QPixmap::fromImage(*backImg));
    back->lower();


    //添加标题
    QImage *titleImg = new QImage();
    titleImg->load(":/image/image/title.png");

    QLabel *title = new QLabel(this);
    title->setGeometry(540,50,800,100);
    title->setPixmap(QPixmap::fromImage(*titleImg));


    //添加滑块音效
    blockAudio = new QSound(":/audio/audio/BlockAudio.wav");

    //添加背景音乐列表
    musicList = new QMediaPlaylist(this);
    musicList->addMedia(QUrl("qrc:/audio/audio/PureMusic.mp3"));
    musicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    musicPlayer = new QMediaPlayer(this);
    musicPlayer->setPlaylist(musicList);
    musicPlayer->setVolume(30);
    //musicPlayer->play();置于开场提示之后


    //背景音乐开关
    //音乐：开
    pureMusic1 = new QPushButton(this);
    pureMusic1->setGeometry(575,475,150,50);
    pureMusic1->setFont(QFont("方正楷体",14));
    pureMusic1->setText("音乐：开");
    pureMusic1->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    pureMusic1->setFocusPolicy(Qt::NoFocus);//NoFocus
    //音乐：关
    pureMusic0 = new QPushButton(this);
    pureMusic0->setGeometry(575,475,150,50);
    pureMusic0->setFont(QFont("方正楷体",14));
    pureMusic0->setText("音乐：关");
    pureMusic0->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    pureMusic0->setFocusPolicy(Qt::NoFocus);//NoFocus
    pureMusic0->hide();
    //connect
    connect(pureMusic1,&QPushButton::clicked,this,[&](){
        musicPlayer->stop();
        pureMusic1->hide();
        pureMusic0->show();
    });
    connect(pureMusic0,&QPushButton::clicked,this,[&](){
        musicPlayer->play();
        pureMusic0->hide();
        pureMusic1->show();
    });


    //音效开关
    audioOn = true;
    //音效：开
    audioBtn1 = new QPushButton(this);
    audioBtn1->setGeometry(745,475,150,50);
    audioBtn1->setFont(QFont("方正楷体",14));
    audioBtn1->setText("音效：开");
    audioBtn1->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    audioBtn1->setFocusPolicy(Qt::NoFocus);//NoFocus
    //音效：关
    audioBtn0 = new QPushButton(this);
    audioBtn0->setGeometry(745,475,150,50);
    audioBtn0->setFont(QFont("方正楷体",14));
    audioBtn0->setText("音效：关");
    audioBtn0->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    audioBtn0->setFocusPolicy(Qt::NoFocus);//NoFocus
    audioBtn0->hide();
    //connect
    connect(audioBtn1,&QPushButton::clicked,this,[&](){
        audioOn = false;
        audioBtn1->hide();
        audioBtn0->show();
    });
    connect(audioBtn0,&QPushButton::clicked,this,[&](){
       audioOn = true;
       audioBtn0->hide();
       audioBtn1->show();
    });

    //键盘事件
    setFocusPolicy(Qt::StrongFocus);

    //开场提示
    QMessageBox::information(nullptr,"游戏说明","本游戏为数字华容道，玩法为将数字滑块按照顺序依次排列即可获胜.\n"
                                           "操作说明：\n"
                                           "可以使用鼠标点击空滑块周围滑块来互换它们的位置\n"
                                           "也可以使用W、A、S、D或者↑、↓、←、→方向键来互换空滑块和其周围滑块\n"
                                           "祝：玩得开心(｡･ω･｡)ﾉ♡");

    musicPlayer->play();//播放背景音乐

    QPushButton *helper = new QPushButton(this);
    helper->setGeometry(10,8,100,40);
    helper->setFont(QFont("方正楷体",14));
    helper->setText("帮助");
    helper->setStyleSheet("border: 4px inset rgb(255,255,255);""border-radius:10px;");
    helper->setFocusPolicy(Qt::NoFocus);//NoFocus
    connect(helper,&QPushButton::clicked,this,[&](){
        QMessageBox::information(this,"游戏说明","本游戏为数字华容道，玩法为将数字滑块按照顺序依次排列即可获胜.\n"
                                               "操作说明：\n"
                                               "可以使用鼠标点击空滑块周围滑块来互换它们的位置\n"
                                               "也可以使用W、A、S、D或者↑、↓、←、→方向键来互换空滑块和其周围滑块\n"
                                               "祝：玩得开心(｡･ω･｡)ﾉ♡");
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update(int a, int b)//参数a,b仅用于 被单击滑块坐标
{
    //相邻滑块坐标
    Coordinate *Up = new Coordinate(Void->X()-1,Void->Y(),sqrt(Void->N()));
    Coordinate *Down = new Coordinate(Void->X()+1,Void->Y(),sqrt(Void->N()));
    Coordinate *Left = new Coordinate(Void->X(),Void->Y()-1,sqrt(Void->N()));
    Coordinate *Right = new Coordinate(Void->X(),Void->Y()+1,sqrt(Void->N()));

    int n = sqrt(Void->N()) * a + b; //被点击滑块的 单 坐标

    if(n==Up->retIndex()&&Up->valid()){
        Block[Void->retIndex()].setText(Block[Up->retIndex()].text());
        Block[Up->retIndex()].setText("");
        Void->setIndex(Up->X(),Up->Y());
        totalSteps++;
        step->setText("Steps:  "+QString::number(totalSteps));
        if(!isBegin){
            timer->start();
            *startTime = QDateTime::currentDateTime();
            isBegin = true;
        }
        if(audioOn)
            blockAudio->play();
        QWidget::update();//可不加
    }
    if(n==Down->retIndex()&&Down->valid()){
        Block[Void->retIndex()].setText(Block[Down->retIndex()].text());
        Block[Down->retIndex()].setText("");
        Void->setIndex(Down->X(),Down->Y());
        totalSteps++;
        step->setText("Steps:  "+QString::number(totalSteps));
        if(!isBegin){
            timer->start();
            *startTime = QDateTime::currentDateTime();
            isBegin = true;
        }
        if(audioOn)
            blockAudio->play();
        QWidget::update();//可不加
    }
    if(n==Left->retIndex()&&Left->valid()){
        Block[Void->retIndex()].setText(Block[Left->retIndex()].text());
        Block[Left->retIndex()].setText("");
        Void->setIndex(Left->X(),Left->Y());
        totalSteps++;
        step->setText("Steps:  "+QString::number(totalSteps));
        if(!isBegin){
            timer->start();
            *startTime = QDateTime::currentDateTime();
            isBegin = true;
        }
        if(audioOn)
            blockAudio->play();
        QWidget::update();//可不加
    }
    if(n==Right->retIndex()&&Right->valid()){
        Block[Void->retIndex()].setText(Block[Right->retIndex()].text());
        Block[Right->retIndex()].setText("");
        Void->setIndex(Right->X(),Right->Y());
        totalSteps++;
        step->setText("Steps:  "+QString::number(totalSteps));
        if(!isBegin){
            timer->start();
            *startTime = QDateTime::currentDateTime();
            isBegin = true;
        }
        if(audioOn)
            blockAudio->play();
        QWidget::update();//可不加
    }


    //判断游戏结束
    bool isOver = true;
    for(int i=0;i<Void->N()-1;i++){//除去最后一个滑块
        if(Block[i].text()!=QString::number(i+1)){
            isOver = false;
            break;
        }
    }
    if(isOver){

        //时间计时停止
        timer->stop();

        QMessageBox overWindow;
        overWindow.setText("恭喜你！(≧∇≦)/你赢了~\n总步数："+QString::number(totalSteps)+"\n用    时："+QString::number(interval)+"s");
        overWindow.setWindowTitle("游戏胜利(^o^)");
        overWindow.setFixedSize(100,65);

        overWindow.addButton("太棒了！",QMessageBox::AcceptRole);

        QPushButton *btn = new QPushButton(&overWindow);
        btn->setText("再玩一局");
        btn->setGeometry(10,95,90,30);
        connect(btn,&QPushButton::clicked,&overWindow,&QMessageBox::close);
        connect(btn,&QPushButton::clicked,this,&MainWindow::restartGame);

        overWindow.exec();
    }
}

void MainWindow::timeoutShow()
{
    QDateTime endTime = QDateTime::currentDateTime();
    interval = (long long int) startTime->secsTo(endTime);
    time->setText("Time:   "+QString::number(interval)+" s");
}

void MainWindow::restartGame(int X)
{
    timer->stop();//停止计时 //未start()貌似也可
    totalSteps = 0;
    isBegin = false;
    step->setText("Steps:  "+QString::number(totalSteps));
    time->setText("Time:   "+QString::number(0));


    if(X == 0){
        //获取1 - N-1的随机数
        int *p = new int[N-1]; //用于存储随机数
        for(int i=0;i<N-1;i++)
            p[i]=i+1;

        //序列随机排序
        using std::random_shuffle;
        std::srand(QTime::currentTime().msec()+QTime::currentTime().second()*1000);//使得每次均不同
        random_shuffle(p, p + N - 1); //注意范围

        for(int i=0;i<sqrt(N);i++){
            for(int j=0;j<sqrt(N);j++){
                Block[(int)(sqrt(N))*i+j].setFocusPolicy(Qt::NoFocus);//NoFocus
                if(!(i == sqrt(N)-1 && j == sqrt(N)-1))
                    Block[(int)(sqrt(N))*i+j].setText(QString::number(p[(int)(sqrt(N))*i+j]));
                else
                    Block[(int)(sqrt(N))*i+j].setText("");
            }
        }

        //回收
        delete[] p;

        //存储空滑块下标
        Void->setIndex(sqrt(N)-1,sqrt(N)-1);

        //结束函数
        return;
    }
    else{
        //滑块个数
        N = X*X;
        //滑块规格参数
        int a;
        int b;
        int side;
        switch(X){
        case 3:
            a = 100;
            b = 100;
            side = 125;
            break;
        case 4:
            a = 75;
            b = 100;
            side = 100;
            break;
        case 5:
            a = 30;
            b = 50;
            side = 100;
            break;
        }

        //获取1 - N-1的随机数
        int *p = new int[N-1]; //用于存储随机数
        for(int i=0;i<N-1;i++)
            p[i]=i+1;

        //序列随机排序
        using std::random_shuffle;
        std::srand(QTime::currentTime().msec()+QTime::currentTime().second()*1000);//使得每次均不同
        random_shuffle(p, p + N - 1); //注意范围

        delete[] Block;//回收
        Block = new QPushButton[N];
        for(int i=0;i<sqrt(N);i++){
            for(int j=0;j<sqrt(N);j++){
                Block[(int)(sqrt(N))*i+j].setParent(this);
                Block[(int)(sqrt(N))*i+j].setGeometry(a+side*j,b+side*i,side,side);
                connect(&Block[(int)(sqrt(N))*i+j],&QPushButton::clicked,this,[=](){
                    this->update(i,j);
                });
                Block[(int)(sqrt(N))*i+j].setFont(QFont("HGB8X_CNKI",18));
                Block[(int)(sqrt(N)*i+j)].setStyleSheet("background-image: url(:/image/image/block.jpg);");
                Block[(int)(sqrt(N))*i+j].setFocusPolicy(Qt::NoFocus);//NoFocus
                if(!(i == sqrt(N)-1 && j == sqrt(N)-1))
                    Block[(int)(sqrt(N))*i+j].setText(QString::number(p[(int)(sqrt(N))*i+j]));
            }
        }

        //回收
        delete[] p;

        //存储空滑块下标
        delete[] Void;//回收
        Void = new Coordinate(sqrt(N));

        //结束函数
        return;
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //相邻滑块坐标
    Coordinate *Up = new Coordinate(Void->X()-1,Void->Y(),sqrt(Void->N()));
    Coordinate *Down = new Coordinate(Void->X()+1,Void->Y(),sqrt(Void->N()));
    Coordinate *Left = new Coordinate(Void->X(),Void->Y()-1,sqrt(Void->N()));
    Coordinate *Right = new Coordinate(Void->X(),Void->Y()+1,sqrt(Void->N()));

    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:{
        if(Up->valid()){
            Block[Void->retIndex()].setText(Block[Up->retIndex()].text());
            Block[Up->retIndex()].setText("");
            Void->setIndex(Up->X(),Up->Y());
            totalSteps++;
            step->setText("Steps:  "+QString::number(totalSteps));
            if(!isBegin){
                timer->start();
                *startTime = QDateTime::currentDateTime();
                isBegin = true;
            }
            if(audioOn)
                blockAudio->play();
            QWidget::update();//可不加
        }
        break;
    }
    case Qt::Key_S:
    case Qt::Key_Down:{
        if(Down->valid()){
            Block[Void->retIndex()].setText(Block[Down->retIndex()].text());
            Block[Down->retIndex()].setText("");
            Void->setIndex(Down->X(),Down->Y());
            totalSteps++;
            step->setText("Steps:  "+QString::number(totalSteps));
            if(!isBegin){
                timer->start();
                *startTime = QDateTime::currentDateTime();
                isBegin = true;
            }
            if(audioOn)
                blockAudio->play();
            QWidget::update();//可不加
        }
        break;
    }
    case Qt::Key_A:
    case Qt::Key_Left:{
        if(Left->valid()){
            Block[Void->retIndex()].setText(Block[Left->retIndex()].text());
            Block[Left->retIndex()].setText("");
            Void->setIndex(Left->X(),Left->Y());
            totalSteps++;
            step->setText("Steps:  "+QString::number(totalSteps));
            if(!isBegin){
                timer->start();
                *startTime = QDateTime::currentDateTime();
                isBegin = true;
            }
            if(audioOn)
                blockAudio->play();
            QWidget::update();//可不加
        }
        break;
    }
    case Qt::Key_D:
    case Qt::Key_Right:{
        if(Right->valid()){
            Block[Void->retIndex()].setText(Block[Right->retIndex()].text());
            Block[Right->retIndex()].setText("");
            Void->setIndex(Right->X(),Right->Y());
            totalSteps++;
            step->setText("Steps:  "+QString::number(totalSteps));
            if(!isBegin){
                timer->start();
                *startTime = QDateTime::currentDateTime();
                isBegin = true;
            }
            if(audioOn)
                blockAudio->play();
            QWidget::update();//可不加
        }
        break;
    }
    default:;
    }
}
