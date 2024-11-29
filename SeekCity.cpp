#include "SeekCity.h"

SeekCity* scw;




 SeekCity::SeekCity(QWidget *parent) : QWidget(parent)
{
     setWindowTitle("天气助手");
     resize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW); // 设置窗口大小为800x600像素


    // 创建返回按钮
    backLayout=new QHBoxLayout();
    isSeeking= new QLabel("正在查找", this);
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
    connect(backButton,&QPushButton::clicked,this,&SeekCity::onBackButtonClicked);

    backLayout->addWidget(isSeeking);
    backLayout->addWidget(backButton);

    nowProDist=new QLabel("中国");
    nowProDist->setStyleSheet("QLabel { "
                              "width: 100px; "
                              "height: 50px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");


    // 创建九个并排的按钮
    buttonsLayout = new QVBoxLayout();
    for(int i=0;i<8;++i)
    {
        buttons[i]= new QPushButton(QString("北京市"), this);
        buttons[i]->setStyleSheet("QPushButton { "
                               "width: 100px; "
                               "height: 50px;"
                               "font-size: 20px; " // 设置字体大小
                               "background: transparent; " // 设置背景为透明
                               "border: 1px solid black; " // 设置边框为1像素黑色
                               "}");
        buttonsLayout->addWidget(buttons[i]);

        connect(buttons[i],&QPushButton::clicked,this,[this, i]() { this->onButtonXClicked(i); });

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

    connect(prevButton,&QPushButton::clicked,this,&SeekCity::onPrevButtonClicked);
    connect(nextButton,&QPushButton::clicked,this,&SeekCity::onNextButtonClicked);


    // 创建水平布局管理器用于翻页按钮
    paginationLayout = new QHBoxLayout();
    paginationLayout->addWidget(prevButton);
    paginationLayout->addWidget(nextButton);

    // 创建垂直布局管理器，将所有部分添加进去
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(backLayout); // 添加返回按钮
    mainLayout->addWidget(nowProDist);
    mainLayout->addLayout(buttonsLayout); // 添加八个并排按钮
    mainLayout->addLayout(paginationLayout); // 添加翻页按钮

    // 设置布局
    setLayout(mainLayout);
}


void SeekCity::upDateSeekCity()
{

    if(nowProvince=="undefined")
    {
        nowProDist->setText("中国");
        auto it1=ctm->provinces.constBegin();
        it1+=provinceIndex;
        auto it2=ctm->provinces.constEnd();
        if(provinceIndex==0)
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
                buttons[i]->setText(it1.key());
                ++it1;
            }
            else
            {
                buttons[i]->setText("");
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
    else if(nowDistric=="undefined")
    {
        nowProDist->setText("中国 "+nowProvince);
        auto it1=ctm->provinces.find(nowProvince).value().constBegin();
        it1+=districIndex;
        auto it2=ctm->provinces.find(nowProvince).value().constEnd();
        if(districIndex==0)
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
                buttons[i]->setText(it1.key());
                ++it1;
            }
            else
            {
                buttons[i]->setText("");
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
    else
    {
        nowProDist->setText("中国 "+nowProvince+" "+nowDistric);
        auto it1=ctm->provinces.find(nowProvince).value().find(nowDistric).value().constBegin();
        it1+=cityIndex;
        auto it2=ctm->provinces.find(nowProvince).value().find(nowDistric).value().constEnd();
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
                buttons[i]->setText(*it1);
                ++it1;
            }
            else
            {
                buttons[i]->setText("");
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

}


void SeekCity::onButtonXClicked(int x)
{
    if(buttons[x]->text()!="")
    {
        if(nowProvince=="undefined")
        {
            nowProvince=buttons[x]->text();
            upDateSeekCity();

        }
        else if(nowDistric=="undefined")
        {

            nowDistric=buttons[x]->text();
            upDateSeekCity();
        }
        else
        {
            nowDistric="undefined";
            nowProvince="undefined";

            provinceIndex=0;
            districIndex=0;
            cityIndex=0;

            bool found;
            ctm->cityTemp=City();
            ctm->callToCityShown=true;
            mainMenu->show();
            close();
            ctm->requestCityData(buttons[x]->text(),found);

        }
    }
}

void SeekCity::onBackButtonClicked()
{
    if(nowProvince=="undefined")
    {
        provinceIndex=0;
        mainMenu->show();
        close();
    }
    else if(nowDistric=="undefined")
    {
        provinceIndex=0;
        districIndex=0;
        nowProvince="undefined";
        upDateSeekCity();
    }
    else
    {
        provinceIndex=0;
        districIndex=0;
        cityIndex=0;
        nowDistric="undefined";
        upDateSeekCity();
    }

}
void SeekCity::onPrevButtonClicked()
{
    if(prevButton->isVisible())
    {
        if(nowProvince=="undefined")
        {
            provinceIndex-=8;
            upDateSeekCity();
        }
        else if(nowDistric=="undefined")
        {
            districIndex-=8;
            upDateSeekCity();
        }
        else
        {
            cityIndex-=8;
            upDateSeekCity();
        }
    }
}
void SeekCity::onNextButtonClicked()
{
    if(nextButton->isVisible())
    {
        if(nowProvince=="undefined")
        {
            provinceIndex+=8;
            upDateSeekCity();
        }
        else if(nowDistric=="undefined")
        {
            districIndex+=8;
            upDateSeekCity();
        }
        else
        {
            cityIndex+=8;
            upDateSeekCity();
        }
    }
}
