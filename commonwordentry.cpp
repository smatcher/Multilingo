#include "commonwordentry.h"

CommonWordEntry::CommonWordEntry(QObject *parent)
    : QObject{parent}
    , m_type(WordType::None)
{

}

void CommonWordEntry::setType(WordType type_)
{
    m_type = type_;
}

WordType CommonWordEntry::type()
{
    return m_type;
}

QJsonObject CommonWordEntry::save() const
{
    QJsonObject json_object;
    json_object["type"] = int(m_type);
    return json_object;
}
