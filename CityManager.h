#ifndef CITYMANAGER_H
#define CITYMANAGER_H


#include"CurrentHead.h"



struct City//City数据结构储存一个城市对应的信息
{
    QString cityName;//城市名
    QString tempNow;//当前温度
    QString humidtyNow;//当前湿度
    QString iconNow;//当前天气对应图标代码
    QString updateDate;//当前天气状况更新日期
    QString updateTime;//当前天气状况更新时间
    QString tempFuture1;//未来一小时温度
    QString iconFuture1;//未来一小时天气图标
    QString fxTime1;//未来一小时预报天气状况对应日期
    QString fxDate1;//未来一小时预报天气状况对应时间
    QString tempFuture2;//未来二小时温度
    QString iconFuture2;//未来二小时天气图标
    QString fxTime2;//未来二小时预报天气状况对应日期
    QString fxDate2;//未来二小时预报天气状况对应时间


};

class CityManager: public QObject
{

    Q_OBJECT

public:
    City cityShown;
    QString tempForm;
    QString composerMessage;
    QString cityShownName;
    City cityTemp;
    QString appDirPath;
    QStringList selectedCityName;
    bool callToSelectCity=false;
    bool callToCityShown=false;

    QMap<QString,City> selectedCities;
    QMap<QString,QMap<QString,QList<QString>>>  provinces;
    QMap<QString,QString>cityCodes;//城市对应代码


    void cityManagerSet(QString appDirPath);
    explicit CityManager(QObject *parent = nullptr);
    void  requestCityData(QString cityName,bool& found);
    void  writeInFiles();
    QString setTemp(const QString &celsiusStr);

signals:
    void getCityFinished();
    void initFinished();


private slots:
    void onInternetRespondFuture();
    void onInternetRespondNow();

    void onGetCityFinished();

    void oninitFinished();

};


extern CityManager* ctm;

#endif // CITYMANAGER_H
