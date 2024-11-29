#ifndef SELECTEDCITY_H
#define SELECTEDCITY_H


#include"CurrentHead.h"
#include"mainwindow.h"
#include"CityManager.h"




class SelectedCity : public QWidget {
public:

    QPushButton*buttons[8];
    QLabel* weathersNow[8];
    QHBoxLayout *oneButtonLayout[8];

    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *backButton;
    QLabel* isSeeking;
    QIcon icon;

    QHBoxLayout *backLayout;
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *paginationLayout;
    QVBoxLayout *mainLayout;



    int cityIndex=0;




    QString appDirPath;
    QPixmap pixmap;
    SelectedCity(QWidget *parent = nullptr) ;
    void SelectedCitySet(QString _appDirPath);
    void upDateSelectedCity();



public slots:
    void onButtonXClicked(int x);
    void onBackButtonClicked();
    void onPrevButtonClicked();
    void onNextButtonClicked();
    void onCityManagerInitFinished();
};


extern SelectedCity* stw;


#endif // SELECTEDCITY_H
