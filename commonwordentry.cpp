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

CommonWordEntry* CommonWordEntry::load_v1(const QJsonObject& json_object, QObject* parent)
{
    CommonWordEntry* word_entry = new CommonWordEntry(parent);
    word_entry->m_type = static_cast<WordType>(json_object["type"].toInt());
    return word_entry;
}
