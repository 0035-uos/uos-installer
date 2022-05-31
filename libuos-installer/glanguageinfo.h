#ifndef GLANGUAGEINFO_H
#define GLANGUAGEINFO_H

#include "garrayjson.h"

class GLanguageInfo : public GArrayJson
{
public:
    explicit GLanguageInfo(const QJsonArray& array);
    explicit GLanguageInfo();

};

#endif // GLANGUAGEINFO_H
