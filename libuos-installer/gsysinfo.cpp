#include "gsysinfo.h"

#include "gjsonitem.h"

GSysInfo::GSysInfo(const QString &filename) : GJson(filename)
{
}

GSysInfo::~GSysInfo()
{
}

bool GSysInfo::commitData()
{
    return GJson::commitData(m_info);
}

void GSysInfo::appendItem(const QString &key, GJsonItem *item)
{
    m_info.insert(key, item->tojson());
}


