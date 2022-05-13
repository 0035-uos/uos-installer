#include "gpartedinfo.h"
#include "gjsonitem.h"


GPartedInfo::GPartedInfo(const QString &filename)
    : GJson(filename)
{
}

GPartedInfo::~GPartedInfo()
{
}

bool GPartedInfo::commitData()
{
    GJson::commitData(m_info);
    return true;
}

void GPartedInfo::appendItem(GJsonItem *item)
{
    m_info.append(item->tojson());
}
