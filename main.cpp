#include "mainwindow.h"
#include"CurrentHead.h"
#include"CityManager.h"
#include"InternetManager.h"
#include"SeekCity.h"
#include"SelectedCity.h"
#include"MySetting.h"


#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "weather_APP_v2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    QString appDirPath = a.applicationDirPath();
    ctm->cityManagerSet(appDirPath);



    mainMenu=new MainWindow;
    scw=new SeekCity;


    stw=new SelectedCity;
    stw->SelectedCitySet(appDirPath);
    stg=new Setting;



    mainMenu->mainWindowSet(appDirPath);









    return a.exec();
}
