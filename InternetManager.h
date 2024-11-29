#ifndef INTERNETMANAGER_H
#define INTERNETMANAGER_H
#include"CurrentHead.h"



class InternetManagerForecast : public QObject//此类通过输入城市名字生成url,获取未来2小时天气对应JSON数据，最终以City数据结构输出
{
    Q_OBJECT

public:
    explicit InternetManagerForecast(QObject *parent = nullptr);//初始化函数，将manager的完成关联到onReplyFinished槽函数
    void getWeatherData(const QString &apiUrl);
    QString fxDate1;
    QString fxTime1;
    QString temp1;
    QString icon1;
    QString fxDate2;
    QString fxTime2;
    QString temp2;
    QString icon2;


signals:
    void InternetRespond();


private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

class InternetManagerNow : public QObject//此类通过输入城市名字生成url,获取当前天气对应JSON数据，最终以City数据结构输出
{
    Q_OBJECT

public:
    explicit InternetManagerNow(QObject *parent = nullptr);//初始化函数，将manager的完成关联到onReplyFinished槽函数
    void getWeatherData(const QString &apiUrl);
    QString updateDate;
    QString updateTime;
    QString temp;
    QString icon;
    QString humidity;


signals:
    void InternetRespond();


private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};
extern InternetManagerForecast* itnf;
extern InternetManagerNow* itnn;
#endif // INTERNETMANAGER_H
