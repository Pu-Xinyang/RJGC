#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"CurrentHead.h"
#include"CityManager.h"
#include"SeekCity.h"
#include"TravelAdvice.h"
#include"SelectedCity.h"
#include"MySetting.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString  appDirPath;

    QWidget *centralWidget;
    QLabel* cityNameLabel;
    QLabel* tempLabel;
    QLabel* humidtyLabel;
    QLabel* weatherNowLabel;
    QLabel* updateDateTimeLabel;
    QLabel* travelAdviceLabel;

    QLabel* tempFuture1Label;
    QLabel* weatherFuture1Label;
    QLabel* fxDateTime1Label;

    QLabel* tempFuture2Label;
    QLabel* weatherFuture2Label;
    QLabel* fxDateTime2Label;

    QPushButton* updateButton;
    QPushButton *searchButton;
    QPushButton *seekButton;
    QPushButton *selectButton;
    QPushButton *selectedCityButton;
    QPushButton *settingButton;
    QPushButton *exitButton;


    QLineEdit *lineEdit;

    QPixmap pixmap;



    void mainWindowSet(QString  _appDirPath);

    void upDateMainWindow();




    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    void onUpDateButtonClicked();
    void onSearchButtonClicked();
    void onSeekButtonClicked();
    void onSelectedButtonClicked();
    void onSelectedCityButtonClicked();
    void onSettingButtonClicked();
    void onExitButtonClicked();

};

extern MainWindow*mainMenu;

#endif // MAINWINDOW_H
