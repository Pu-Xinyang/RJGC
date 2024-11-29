#include "SelectedCity.h"

SelectedCity* stw;




SelectedCity::SelectedCity(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("天气助手");
    resize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW); // 设置窗口大小为800x600像素

}
void SelectedCity::SelectedCitySet(QString _appDirPath)
{

    connect(ctm,&CityManager::initFinished,this,&SelectedCity::onCityManagerInitFinished);

    appDirPath=_appDirPath;

    // 创建返回按钮
    backLayout=new QHBoxLayout();
    isSeeking= new QLabel("正在浏览收藏", this);
    isSeeking->setStyleSheet("QLabel { "
                             "width: 100px; "
                             "height: 50px;"
                             "font-size: 20px; " // 设置字体大小
                             "background: transparent; " // 设置背景为透明
                             "border: 1px solid black; " // 设置边框为1像素黑色
                             "text-align: center; "
                             "alignment: center; "
                             "}");

    backButton = new QPushButton("返回", this);
    backButton->setStyleSheet("QPushButton { "
                              "width: 100px; "
                              "height: 50px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");
    connect(backButton,&QPushButton::clicked,this,&SelectedCity::onBackButtonClicked);

    backLayout->addWidget(isSeeking);
    backLayout->addWidget(backButton);



    // 创建八个并排的按钮
    buttonsLayout = new QVBoxLayout();
    for(int i=0;i<8;++i)
    {
        buttons[i]= new QPushButton(QString("北京市"), this);
        buttons[i]->setStyleSheet("QPushButton { "
                                  "width: 200px; "
                                  "height: 50px;"
                                  "font-size: 20px; " // 设置字体大小
                                  "background: transparent; " // 设置背景为透明
                                  "border: 1px solid black; " // 设置边框为1像素黑色
                                  "}");


        connect(buttons[i],&QPushButton::clicked,this,[this, i]() { this->onButtonXClicked(i); });


        weathersNow[i]=new QLabel;
        pixmap.load(appDirPath+"/data/icons/"+"318"+".png");
        weathersNow[i]->setPixmap(pixmap);
        weathersNow[i]->setStyleSheet("QLabel { "
                                  "width: 150px; "
                                  "height: 50px;"
                                  "alignment: center; "
                                  "background: transparent; " // 设置背景为透明
                                  "}");
        oneButtonLayout[i]=new QHBoxLayout;
        oneButtonLayout[i]->addWidget(buttons[i]);
        oneButtonLayout[i]->addWidget(weathersNow[i]);
        buttonsLayout->addLayout(oneButtonLayout[i]);

    }



    // 创建两个翻页按钮
    prevButton = new QPushButton("上一页", this);
    prevButton->setStyleSheet("QPushButton { "
                              "width: 100px; "
                              "height: 50px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");
    nextButton = new QPushButton("下一页", this);
    nextButton->setStyleSheet("QPushButton { "
                              "width: 100px; "
                              "height: 50px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");

    connect(prevButton,&QPushButton::clicked,this,&SelectedCity::onPrevButtonClicked);
    connect(nextButton,&QPushButton::clicked,this,&SelectedCity::onNextButtonClicked);


    // 创建水平布局管理器用于翻页按钮
    paginationLayout = new QHBoxLayout();
    paginationLayout->addWidget(prevButton);
    paginationLayout->addWidget(nextButton);

    // 创建垂直布局管理器，将所有部分添加进去
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(backLayout); // 添加返回按钮
    mainLayout->addLayout(buttonsLayout); // 添加八个并排按钮
    mainLayout->addLayout(paginationLayout); // 添加翻页按钮

    // 设置布局
    setLayout(mainLayout);
}


void SelectedCity::upDateSelectedCity()
{

        auto it1=ctm->selectedCities.constBegin();
        it1+=cityIndex;
        auto it2=ctm->selectedCities.constEnd();
        if(cityIndex==0)
        {
            prevButton->hide();
        }
        else
        {
            prevButton->show();
        }
        for(int i=0;i<8;++i)
        {
            if(it1!=it2)
            {
                buttons[i]->setText(it1.value().cityName+" "+ctm->setTemp(it1.value().tempNow));
                pixmap.load(appDirPath+"/data/icons/"+it1.value().iconNow+".png");
                weathersNow[i]->setPixmap(pixmap);
                ++it1;
            }
            else
            {
                buttons[i]->setText("");
                pixmap=QPixmap();
                weathersNow[i]->setPixmap(pixmap);
            }
        }
        if(it1==it2)
        {
            nextButton->hide();
        }
        else
        {
            nextButton->show();
        }

}


void SelectedCity::onButtonXClicked(int x)
{

            cityIndex=0;

            bool found;
            ctm->cityTemp=City();
            ctm->callToCityShown=true;
            mainMenu->show();
            close();
            ctm->requestCityData(buttons[x]->text().split(" ")[0],found);


}

void SelectedCity::onBackButtonClicked()
{

        cityIndex=0;
        mainMenu->show();
        close();


}
void SelectedCity::onPrevButtonClicked()
{
    if(prevButton->isVisible())
    {
            cityIndex-=8;
            upDateSelectedCity();
    }
}
void SelectedCity::onNextButtonClicked()
{
    if(nextButton->isVisible())
    {

            cityIndex+=8;
            upDateSelectedCity();
    }
}

void SelectedCity:: onCityManagerInitFinished()
{

    upDateSelectedCity();
}
