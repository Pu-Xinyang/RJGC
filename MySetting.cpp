#include "MySetting.h"
Setting* stg;
Setting::Setting(QWidget *parent ):QWidget(parent)
{
    setWindowTitle("天气助手");
    resize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW); // 设置窗口大小为800x600像素

    // 创建返回按钮
    backLayout=new QHBoxLayout();
    isSeeking= new QLabel("设置", this);
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
    connect(backButton,&QPushButton::clicked,this,&Setting::onBackButtonClicked);

    settingButton = new QPushButton(ctm->tempForm=="C"?"切换华氏度":"切换摄氏度",this);
    settingButton->setStyleSheet("QPushButton { "
                              "width: 100px; "
                              "height: 50px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");
    connect(settingButton,&QPushButton::clicked,this,&Setting::onSettingButtonClicked);

    _composerMessage=new QLabel(ctm->composerMessage);
    _composerMessage->setStyleSheet("QLabel { "
                              "width: 200px; "
                              "height: 200px;"
                              "font-size: 20px; " // 设置字体大小
                              "background: transparent; " // 设置背景为透明
                              "border: 1px solid black; " // 设置边框为1像素黑色
                              "}");


    backLayout->addWidget(isSeeking);
    backLayout->addWidget(backButton);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(backLayout); // 添加返回按钮
    mainLayout->addWidget(_composerMessage);
    mainLayout->addWidget(settingButton);
}

void Setting::onBackButtonClicked()
{
    mainMenu->show();
    close();
}
void Setting::onSettingButtonClicked()
{
    ctm->tempForm=ctm->tempForm=="C"?"F":"C";
    settingButton->setText(ctm->tempForm=="C"?"切换华氏度":"切换摄氏度");
}
