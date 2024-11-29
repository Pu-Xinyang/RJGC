#include"CurrentHead.h"
#include"CityManager.h"
#include"InternetManager.h"
#include"mainwindow.h"


CityManager*ctm=new CityManager;

void CityManager:: oninitFinished()
{

}



void CityManager::onInternetRespondFuture()
{
    cityTemp.fxDate1=itnf->fxDate1;
    cityTemp.fxTime1=itnf->fxTime1;
    cityTemp.tempFuture1=itnf->temp1;
    cityTemp.iconFuture1=itnf->icon1;

    cityTemp.fxDate2=itnf->fxDate2;
    cityTemp.fxTime2=itnf->fxTime2;
    cityTemp.tempFuture2=itnf->temp2;
    cityTemp.iconFuture2=itnf->icon2;

    if(cityTemp.iconNow!="")
    {
        emit getCityFinished();
    }
}
void CityManager::onInternetRespondNow()
{
    cityTemp.updateDate=itnn->updateDate;
    cityTemp.updateTime=itnn->updateTime;
    cityTemp.tempNow=itnn->temp;
    cityTemp.iconNow=itnn->icon;
    cityTemp.humidtyNow=itnn->humidity;
    if(cityTemp.iconFuture1!="")
    {
        emit getCityFinished();
    }
}
void CityManager::onGetCityFinished()
{
    qDebug()<<"finish"<<cityTemp.cityName<<callToCityShown<<callToSelectCity;

    if(callToSelectCity)
    {
        qDebug()<<"?"<<cityTemp.cityName;
        if(cityTemp.cityName!="")
        {
            selectedCities.insert(cityTemp.cityName,cityTemp);
            bool found;
            if(!selectedCityName.isEmpty())
            {
                cityTemp=City();
                requestCityData(selectedCityName[0],found);
                selectedCityName.removeAt(0);
            }
            else
            {
                callToSelectCity=false;
                callToCityShown=true;
                bool found;
                cityTemp=City();
                requestCityData(cityShown.cityName,found);
                emit initFinished();
            }
        }
    }
    else if(callToCityShown)
    {
        qDebug()<<"!"<<cityTemp.cityName;
        cityShown=cityTemp;
        cityTemp=City();
        callToCityShown=false;
        mainMenu->upDateMainWindow();

    }


}

CityManager::CityManager(QObject *parent):QObject(parent)
{
    connect(itnf, &InternetManagerForecast::InternetRespond, this, &CityManager::onInternetRespondFuture);
    connect(itnn, &InternetManagerNow::InternetRespond, this, &CityManager::onInternetRespondNow);

    connect(this,&CityManager::getCityFinished,this,&CityManager::onGetCityFinished);

    connect(this,&CityManager::initFinished,this,&CityManager::oninitFinished);
}



void CityManager::requestCityData(QString cityName,bool& found)
{


    auto it =cityCodes.find(cityName);
    if (it != cityCodes.end())
    {

        found=true;

        itnf->getWeatherData(URL_FUTURE_P1+it.value());
        itnn->getWeatherData(URL_NOW_P1+it.value());
        cityTemp.cityName=cityName;
    }
    else
    {
        found=false;
        qDebug()<<cityName<<" 找不到";

    }

}



void CityManager::cityManagerSet(QString _appDirPath)
{





    appDirPath=_appDirPath;
    QString filePath1 = _appDirPath + "/data/China-City-List-latest.txt";
    QString filePath2 = _appDirPath + "/data/Selected-City.txt";
    QString filePath3 = _appDirPath + "/data/Setting.txt";

    QFile file1(filePath1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file1.";

    }
    QFile file2(filePath2);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file2.";

    }
    QFile file3(filePath3);
    if (!file3.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file3.";

    }


    QTextStream in1(&file1);
    QString line1;
    QTextStream in2(&file2);
    QString line2= in2.readLine();

    selectedCityName=line2.split(',');

    QString in3=file3.readAll();
    QStringList line3=in3.split(",");


    QString nowDistric="undefined";
    QString nowProvince="undefined";
    // 读取每一行
    while (!in1.atEnd()) {
        line1 = in1.readLine();
        QStringList fields = line1.split(',', Qt::SkipEmptyParts); // 使用逗号分隔

        if (fields.size() >= 0) {
            QString value0 = fields[0]; //  "101110300"
            QString value2 = fields[2]; // "延安"
            QString value7 = fields[7]; // "陕西省"
            QString value9 = fields[9]; // "延安市"

           /* qDebug() << "Value 0:" << value0;
            qDebug() << "Value 2:" << value2;
            qDebug() << "Value 7:" << value7;
            qDebug() << "Value 9:" << value9;*/


            cityCodes.insert(value2,value0);
            if(nowProvince!=value7)
            {
                provinces.insert(value7,QMap<QString,QList<QString>>());
               // qDebug()<<"新建省份"<<value7;
            }
            if(nowDistric!=value9)
            {
                auto it = provinces.find(value7);
                if (it != provinces.end())
                {
                    it.value().insert(value9,QList<QString>());
                   // qDebug()<<value9<<"->"<<value7;
                }
                else
                {
                    qDebug() << "Key not found";
                }
            }
                auto it = provinces.find(value7);
                if (it != provinces.end())
                {
                    auto it2=it.value().find(value9);
                    if (it2 != it.value().end())
                    {
                        it2.value().append(value2);
                       // qDebug()<<value2<<"->"<<value9;
                    }
                    else
                    {
                        qDebug() << "Key not found";
                    }
                }
                else
                {
                    qDebug() << "Key not found";
                }



            nowProvince=value7;
            nowDistric=value9;


        }
    }

    file1.close();
    file2.close();
    file3.close();

    cityShown.cityName=line3[0];
    tempForm=line3[1];
    composerMessage=line3[2];

    callToSelectCity=true;
    bool found;
    requestCityData(selectedCityName[0],found);
    selectedCityName.removeAt(0);



//大理州,天津,延安


}

void CityManager::writeInFiles()
{
    QString filePath2 = appDirPath + "/data/Selected-City.txt";
    QString filePath3 = appDirPath + "/data/Setting.txt";
    QFile file2(filePath2);
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file2.";

    }
    QFile file3(filePath3);
    if (!file3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file2.";

    }
    QTextStream out2(&file2);
    QTextStream out3(&file3);
    if(selectedCities.isEmpty())
    {
        out2 <<"北京";
    }
    else
    {
        for (auto it = selectedCities.constBegin(); it != selectedCities.constEnd(); ++it)
        {
            out2 << it.key();
            if(it+1!= selectedCities.constEnd())
                out2 << ",";
        }
    }
    out3<<cityShown.cityName<<","<<tempForm<<","<<composerMessage;
    qDebug()<<cityShown.cityName<<","<<tempForm;
    file2.close();
    file3.close();
}

QString CityManager::setTemp(const QString &celsiusStr)
{
    if(tempForm=="F")
    {
    bool ok;
    // 从QString中提取整数
    int tempCelsius = celsiusStr.toInt(&ok);
    if (!ok) {
        // 如果转换失败，返回错误信息
        return "Invalid input";
    }

    // 转换公式：F = C * 9/5 + 32
    int tempFahrenheit = static_cast<int>((tempCelsius * 9.0 / 5.0) + 32);

    // 将整数结果转换为QString

    QString result=QString::number(tempFahrenheit);
    return result+"°F";
    }
    else
        return celsiusStr+"°C";
}

