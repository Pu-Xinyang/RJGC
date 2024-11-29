#include"InternetManager.h"
#include"CurrentHead.h"


InternetManagerForecast *itnf=new InternetManagerForecast;
InternetManagerNow* itnn=new InternetManagerNow;


InternetManagerForecast::InternetManagerForecast(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &InternetManagerForecast::onReplyFinished);
}

void InternetManagerForecast::getWeatherData(const QString &apiUrl)//当有一个URL的时候从该URL请求数据
{
    QUrl url(apiUrl);
    QNetworkRequest request(url);

    manager->get(request);
    //qDebug()<<apiUrl;
    return;
}



void InternetManagerForecast::onReplyFinished(QNetworkReply *reply)//响应请求完成的事件，对获得的JSON数据进行处理
{
    if (reply->error() == QNetworkReply::NoError)//在网络无异常的情况下
    {
        QByteArray array = reply->readAll();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(array,&error);//获得的所有数据暂存在jsonDoc中


        if (!jsonDoc.isNull())
        {
            QJsonObject jsonObject = jsonDoc.object();
            QJsonArray hourlyArray = jsonObject["hourly"].toArray();

            QString weatherData1;
            QString weatherData2;
            int count=0;
            for (const QJsonValue &value : hourlyArray)
            {
                QJsonObject hourlyObject = value.toObject();
                QString temp = hourlyObject["temp"].toString();
                QString icon = hourlyObject["icon"].toString();

                QStringList fxTimeparts = hourlyObject["fxTime"].toString().split('T', Qt::SkipEmptyParts);
                QString fxDate =fxTimeparts[0];
                QString fxTime = fxTimeparts[1].split('+', Qt::SkipEmptyParts)[0];
                // 以此类推，添加其他需要的字段
                if(count==1)
                {
                    weatherData1 = fxDate + " " +fxTime + " " + temp + " " + icon + '\n';
                    fxDate1=fxDate;
                    fxTime1=fxTime;
                    temp1=temp;
                    icon1=icon;
                }
                if(count==2)
                {
                    weatherData2 = fxDate + " " +fxTime + " " + temp + " " + icon + '\n';
                    fxDate2=fxDate;
                    fxTime2=fxTime;
                    temp2=temp;
                    icon2=icon;
                }
                ++count;

            }

            qDebug()<<weatherData1;
            qDebug()<<weatherData2;

        }
        else
        {
            qDebug("json error");
            return ;

        }
    }
    else
    {
           qDebug()<<"Network error"; // 处理网络错误
    }


    emit InternetRespond();


    reply->deleteLater();
}


InternetManagerNow::InternetManagerNow(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &InternetManagerNow::onReplyFinished);
}

void InternetManagerNow::getWeatherData(const QString &apiUrl)//当有一个URL的时候从该URL请求数据
{
    QUrl url(apiUrl);
    QNetworkRequest request(url);
    manager->get(request);
    return;
}



void InternetManagerNow::onReplyFinished(QNetworkReply *reply)//响应请求完成的事件，对获得的JSON数据进行处理
{
    if (reply->error() == QNetworkReply::NoError)//在网络无异常的情况下
    {
        QByteArray array = reply->readAll();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(array,&error);//获得的所有数据暂存在jsonDoc中


        if (!jsonDoc.isNull())
        {
            QJsonObject jsonObject = jsonDoc.object();
            QJsonObject nowObject = jsonObject["now"].toObject();
            QString weatherData;

                temp = nowObject["temp"].toString();
                icon = nowObject["icon"].toString();
                humidity = nowObject["humidity"].toString();
                QStringList updateTimeparts = jsonObject["updateTime"].toString().split('T', Qt::SkipEmptyParts);
                updateDate =updateTimeparts[0];
                updateTime = updateTimeparts[1].split('+', Qt::SkipEmptyParts)[0];


                weatherData =updateDate+ " " +  updateTime + " " + temp + " " + icon +" "+humidity+ '\n';
                qDebug()<<weatherData;



            // 假设我们有一个函数来处理这个QString
            // processWeatherData(weatherData);
        }
        else
        {
            qDebug("json error");
            return ;

        }
    }
    else
    {
        // 处理网络错误
    }


    emit InternetRespond();


    reply->deleteLater();
}





