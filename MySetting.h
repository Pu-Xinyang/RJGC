#ifndef MYSETTING_H
#define MYSETTING_H


#include"CurrentHead.h"
#include"mainwindow.h"
#include"CityManager.h"


class Setting:public QWidget
{
public:
    QHBoxLayout *backLayout;
    QVBoxLayout *mainLayout;
    QPushButton *backButton;
    QPushButton *settingButton;
    QLabel* isSeeking;
    QLabel* _composerMessage;
    Setting(QWidget *parent = nullptr);
public slots:
    void onBackButtonClicked();
    void onSettingButtonClicked();

};
extern Setting* stg;
#endif // MYSETTING_H
