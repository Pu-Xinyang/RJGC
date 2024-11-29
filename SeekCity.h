#ifndef SEEKCITY_H
#define SEEKCITY_H

#include"CurrentHead.h"
#include"mainwindow.h"
#include"CityManager.h"



class SeekCity : public QWidget {
public:

    QPushButton*buttons[8];
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *backButton;
    QLabel* nowProDist;
    QLabel* isSeeking;
    QIcon icon;

    QHBoxLayout *backLayout;
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *paginationLayout;
    QVBoxLayout *mainLayout;


    QString nowDistric="undefined";
    QString nowProvince="undefined";

    int provinceIndex=0;
    int districIndex=0;
    int cityIndex=0;





    QPixmap pixmap;
    SeekCity(QWidget *parent = nullptr) ;
   //void SeekCitySet();
    void upDateSeekCity();



public slots:
    void onButtonXClicked(int x);
    void onBackButtonClicked();
    void onPrevButtonClicked();
    void onNextButtonClicked();
};

extern SeekCity* scw;



#endif // SEEKCITY_H
