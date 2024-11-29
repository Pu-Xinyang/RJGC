#include "TravelAdvice.h"
bool goodWeather(QString icon)
{
return icon=="100"||icon=="101"||icon=="102"||icon=="103"||icon=="104"
           ||icon=="150"||icon=="151"||icon=="152"||icon=="153";

}
QString makeAdvice(City city)
{
    if(goodWeather(city.iconNow)&&goodWeather(city.iconFuture1)&&goodWeather(city.iconFuture2))
        return"出行：宜";
    else
        return"出行：不宜";

}
