#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow*mainMenu;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("天气助手");
    resize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW); // 设置窗口大小为800x600像素
}



void MainWindow::mainWindowSet(QString  _appDirPath)


{


    appDirPath=_appDirPath;

    centralWidget = new QWidget(this);
    centralWidget->resize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    // 将中心部件设置到 QMainWindow
    setCentralWidget(centralWidget);





    cityNameLabel=new QLabel(centralWidget);
    tempLabel=new QLabel(centralWidget);
    humidtyLabel=new QLabel(centralWidget);
    weatherNowLabel=new QLabel(centralWidget);
    updateDateTimeLabel=new QLabel(centralWidget);
    travelAdviceLabel=new QLabel(centralWidget);
    fxDateTime1Label=new QLabel(centralWidget);
    fxDateTime2Label=new QLabel(centralWidget);
    tempFuture1Label=new QLabel(centralWidget);
    tempFuture2Label=new QLabel(centralWidget);
    weatherFuture1Label=new QLabel(centralWidget);
    weatherFuture2Label=new QLabel(centralWidget);

    seekButton=new QPushButton(centralWidget);
    connect(seekButton, &QPushButton::clicked,this,&MainWindow::onSeekButtonClicked);
    pixmap.load(appDirPath+"/data/others/seek.png");
    QIcon icon1(pixmap);
    seekButton->setIcon(icon1);
    seekButton->setIconSize(QSize(150, 50));
    seekButton->setGeometry(25, 100, 150, 50);
    seekButton->setStyleSheet("QPushButton { "
                                "width: 150px; "
                                "height: 50px;"
                                "background: transparent;"
                                "}");

    updateButton=new QPushButton(centralWidget);
    connect(updateButton, &QPushButton::clicked,this,&MainWindow::onUpDateButtonClicked);
    pixmap.load(appDirPath+"/data/others/update.png");
    QIcon icon2(pixmap);
    updateButton->setIcon(icon2);
    updateButton->setIconSize(QSize(50, 50));
    updateButton->setGeometry(25, 25, 50, 50);
    updateButton->setStyleSheet("QPushButton { "
                         "border-radius: 25px; " // 设置边框半径为按钮高度的一半
                         "background: transparent;"
                         "}");

    searchButton=new QPushButton(centralWidget);
    connect(searchButton, &QPushButton::clicked,this,&MainWindow::onSearchButtonClicked);
    pixmap.load(appDirPath+"/data/others/search.png");
    QIcon icon3(pixmap);
    searchButton->setIcon(icon3);
    searchButton->setIconSize(QSize(50, 50));
    searchButton->setGeometry(WIDTH_OF_WINDOW/4*3+125, 25, 50, 50);
    searchButton->setStyleSheet("QPushButton { "
                                "border-radius: 25px; " // 设置边框半径为按钮高度的一半
                                "background: transparent;"
                                "}");

    selectButton=new QPushButton(centralWidget);
    connect(selectButton, &QPushButton::clicked,this,&MainWindow::onSelectedButtonClicked);

    pixmap.load(appDirPath+"/data/others/select.png");
    QIcon icon4(pixmap);
    selectButton->setIcon(icon4);
    selectButton->setIconSize(QSize(50, 50));
    selectButton->setGeometry(100, 25, 50, 50);
    selectButton->setStyleSheet("QPushButton { "
                                "border-radius: 25px; " // 设置边框半径为按钮高度的一半
                                "background: transparent;"
                                "}");

    selectedCityButton=new QPushButton(centralWidget);
    connect(selectedCityButton, &QPushButton::clicked,this,&MainWindow::onSelectedCityButtonClicked);

    pixmap.load(appDirPath+"/data/others/selectedCities.png");
    QIcon icon5(pixmap);
    selectedCityButton->setIcon(icon5);
    selectedCityButton->setIconSize(QSize(150, 50));
    selectedCityButton->setGeometry(25, 175, 150, 50);
    selectedCityButton->setStyleSheet("QPushButton { "
                                      "width: 150px; "
                                      "height: 50px;"
                                "background: transparent;"
                                "}");



    settingButton=new QPushButton(centralWidget);
    connect(settingButton, &QPushButton::clicked,this,&MainWindow::onSettingButtonClicked);
    pixmap.load(appDirPath+"/data/others/Setting.png");
    QIcon icon6(pixmap);
    settingButton->setIcon(icon6);
    settingButton->setIconSize(QSize(50, 50));
    settingButton->setGeometry(175, 25, 50, 50);
    settingButton->setStyleSheet("QPushButton { "
                                "border-radius: 25px; " // 设置边框半径为按钮高度的一半
                                "background: transparent;"
                                "}");




    exitButton=new QPushButton(centralWidget);
    connect(exitButton, &QPushButton::clicked,this,&MainWindow::onExitButtonClicked);
    pixmap.load(appDirPath+"/data/others/exit.png");
    QIcon icon7(pixmap);
    exitButton->setIcon(icon7);
    exitButton->setIconSize(QSize(50, 50));
    exitButton->setGeometry(WIDTH_OF_WINDOW/4*3+125, 100, 50, 50);
    exitButton->setStyleSheet("QPushButton { "
                                 "border-radius: 25px; " // 设置边框半径为按钮高度的一半
                                 "background: transparent;"
                                 "}");



    lineEdit=new QLineEdit(centralWidget);
    lineEdit->setPlaceholderText("请输入城市名");
    lineEdit->setStyleSheet("QLineEdit { "
                           "font-size: 20px; " // 设置字体大小
                           "background: transparent; " // 设置背景为透明
                           "border: 1px solid black; " // 设置边框为1像素黑色
                           "}");
    lineEdit->setGeometry(WIDTH_OF_WINDOW/4*3-50, 25, 150, 50);

}



void MainWindow::upDateMainWindow()
{



    QString centralWidgetSheet=
        "QWidget { background-image: url("+appDirPath+"/data/backgrounds/"+ctm->cityShown.iconNow+".png"+"); background-position: center;background-repeat: no-repeat; }";
    centralWidget->setStyleSheet(centralWidgetSheet);






    cityNameLabel->setText(ctm->cityShown.cityName);
    cityNameLabel->setStyleSheet("QLabel {"
                                 "font-family: '华文细黑';" // 设置字体
                                 "font-size: 50px;"     // 设置字体大小
                                 "color: black;"          // 设置字体颜色
                                 "background: transparent;"
                                 "}");
    cityNameLabel->setGeometry(WIDTH_OF_WINDOW/2-75, HEIGHT_OF_WINDOW/2-300, 150, 50);

    tempLabel->setText(ctm->setTemp(ctm->cityShown.tempNow));
    tempLabel->setStyleSheet("QLabel {"
                             "font-family: 'Arial';" // 设置字体
                             "font-size: 100px;"     // 设置字体大小
                             "color: black;"          // 设置字体颜色
                             "background: transparent;"
                             "}");
    tempLabel->setGeometry(WIDTH_OF_WINDOW/2-125, HEIGHT_OF_WINDOW/2-175, 300, 100);

    humidtyLabel->setText("湿度："+ctm->cityShown.humidtyNow+"%");
    humidtyLabel->setStyleSheet("QLabel {"
                                "font-family: '华文细黑';" // 设置字体
                                "font-size: 25px;"     // 设置字体大小
                                "color: black;"          // 设置字体颜色
                                "background: transparent;"

                                "}");
    humidtyLabel->setGeometry(WIDTH_OF_WINDOW/2-150, HEIGHT_OF_WINDOW/2-50, 150, 25);

    pixmap.load(appDirPath+"/data/icons/"+ctm->cityShown.iconNow+".png");
    weatherNowLabel->setPixmap(pixmap);
    weatherNowLabel->setGeometry(WIDTH_OF_WINDOW/2+25, HEIGHT_OF_WINDOW/2-50,300, 25);
    weatherNowLabel->setStyleSheet("QLabel {"
                                   "background: transparent;"
                                   "}");

    updateDateTimeLabel->setText("更新时间 "+ctm->cityShown.updateDate+" "+ctm->cityShown.updateTime);
    updateDateTimeLabel->setStyleSheet("QLabel {"
                                       "font-family: '华文细黑';" // 设置字体
                                       "font-size: 20px;"     // 设置字体大小
                                       "color: black;"          // 设置字体颜色
                                       "background: transparent;"
                                       "}");
    updateDateTimeLabel->setGeometry(WIDTH_OF_WINDOW/2-125, HEIGHT_OF_WINDOW/2-235,300, 20);

    travelAdviceLabel->setText(makeAdvice(ctm->cityShown));
    travelAdviceLabel->setStyleSheet("QLabel {"
                                     "font-family: '华文细黑';" // 设置字体
                                     "font-size: 20px;"     // 设置字体大小
                                     "color: black;"          // 设置字体颜色
                                     "background: transparent;"
                                     "}");
    travelAdviceLabel->setGeometry(WIDTH_OF_WINDOW/2-50, HEIGHT_OF_WINDOW/2-210,300, 20);

    fxDateTime1Label->setText(ctm->cityShown.fxDate1+" "+ctm->cityShown.fxTime1);
    fxDateTime1Label->setStyleSheet("QLabel {"
                                    "font-family: '华文细黑';" // 设置字体
                                    "font-size: 20px;"     // 设置字体大小
                                    "color: black;"          // 设置字体颜色
                                    "background: transparent;"
                                    "}");
    fxDateTime1Label->setGeometry(WIDTH_OF_WINDOW/4-100, HEIGHT_OF_WINDOW/2,300, 20);

    fxDateTime2Label->setText(ctm->cityShown.fxDate2+" "+ctm->cityShown.fxTime2);
    fxDateTime2Label->setStyleSheet("QLabel {"
                                    "font-family: '华文细黑';" // 设置字体
                                    "font-size: 20px;"     // 设置字体大小
                                    "color: black;"          // 设置字体颜色
                                    "background: transparent;"
                                    "}");
    fxDateTime2Label->setGeometry(WIDTH_OF_WINDOW/4*3-100, HEIGHT_OF_WINDOW/2,300, 20);

    tempFuture1Label->setText(ctm->setTemp(ctm->cityShown.tempFuture1));
    tempFuture1Label->setStyleSheet("QLabel {"
                                    "font-family: '华文细黑';" // 设置字体
                                    "font-size: 50px;"     // 设置字体大小
                                    "color: black;"          // 设置字体颜色
                                    "background: transparent;"
                                    "}");
    tempFuture1Label->setGeometry(WIDTH_OF_WINDOW/4-100, HEIGHT_OF_WINDOW/2+50,300, 50);

    tempFuture2Label->setText(ctm->setTemp(ctm->cityShown.tempFuture2));
    tempFuture2Label->setStyleSheet("QLabel {"
                                    "font-family: '华文细黑';" // 设置字体
                                    "font-size: 50px;"     // 设置字体大小
                                    "color: black;"          // 设置字体颜色
                                    "background: transparent;"
                                    "}");
    tempFuture2Label->setGeometry(WIDTH_OF_WINDOW/4*3-100, HEIGHT_OF_WINDOW/2+50,300, 50);



    pixmap.load(appDirPath+"/data/icons/"+ctm->cityShown.iconFuture1+".png");
    weatherFuture1Label->setPixmap(pixmap);
    weatherFuture1Label->setStyleSheet("QLabel {"
                                   "background: transparent;"
                                   "}");
    weatherFuture1Label->setGeometry(WIDTH_OF_WINDOW/4-75, HEIGHT_OF_WINDOW/2+150,300, 25);

    pixmap.load(appDirPath+"/data/icons/"+ctm->cityShown.iconFuture2+".png");
    weatherFuture2Label->setPixmap(pixmap);
    weatherFuture2Label->setStyleSheet("QLabel {"
                                       "background: transparent;"
                                       "}");
    weatherFuture2Label->setGeometry(WIDTH_OF_WINDOW/4*3-75, HEIGHT_OF_WINDOW/2+150,300, 25);

    if(ctm->selectedCities.contains(ctm->cityShown.cityName))
    {
        pixmap.load(appDirPath+"/data/others/selected.png");
        QIcon icon(pixmap);
        selectButton->setIcon(icon);

    }
    else
    {
        pixmap.load(appDirPath+"/data/others/select.png");
        QIcon icon(pixmap);
        selectButton->setIcon(icon);
    }



    show();
}

void MainWindow::onUpDateButtonClicked()
{
    bool found;
    ctm->cityTemp=City();
    ctm->callToCityShown=true;
    ctm->requestCityData(cityNameLabel->text(),found);
}
void MainWindow::onSearchButtonClicked()
{
    bool found;
    ctm->cityTemp=City();
    ctm->callToCityShown=true;
    ctm->requestCityData(lineEdit->text(),found);
    if(!found)
    {
        mainMenu->lineEdit->setText("未能找到该城市");
        mainMenu->upDateMainWindow();
    }
}
void MainWindow::onSeekButtonClicked()
{
    scw->upDateSeekCity();
    scw->show();
    close();

}
void MainWindow::onSelectedCityButtonClicked()
{
    stw->upDateSelectedCity();
    stw->show();
    close();
}
void MainWindow::onSelectedButtonClicked()
{
    if(ctm->selectedCities.contains(ctm->cityShown.cityName))
    {
        ctm->selectedCities.remove(ctm->cityShown.cityName);
    }
    else
    {
        ctm->selectedCityName.append(ctm->cityShown.cityName);
        ctm->callToSelectCity=true;
        bool found;
        ctm->requestCityData(ctm->selectedCityName[0],found);
        ctm->selectedCityName.removeAt(0);
    }
    upDateMainWindow();
}
void MainWindow::onSettingButtonClicked()
{
    stg->show();
    close();

}
void MainWindow::onExitButtonClicked()
{
    ctm->writeInFiles();
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;

}
