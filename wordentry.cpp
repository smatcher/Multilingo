#include "wordentry.h"

WordEntry::WordEntry(QObject *parent)
    : QObject{parent}
{}

bool WordEntry::hasData() const
{
    return !m_value.isEmpty() || !m_disambiguation.isEmpty() || !m_details.isEmpty();
}

void WordEntry::setValue(const QString& value_)
{
    m_value = value_;
}

const QString& WordEntry::value() const
{
    return m_value;
}

void WordEntry::setDisambiguation(const QString& disambiguation_)
{
    m_disambiguation = disambiguation_;
}

const QString& WordEntry::disambiguation() const
{
    return m_disambiguation;
}

void WordEntry::setDetails(const QString& details_)
{
    m_details = details_;
}

const QString& WordEntry::details() const
{
    return m_details;
}

QString WordEntry::toString() const
{
    if (m_disambiguation.isEmpty())
        return m_value;

    return QString("%1 (%2)").arg(m_value, m_disambiguation);
}

QJsonObject WordEntry::save() const
{
    QJsonObject json_object;
    json_object["value"] = m_value;
    json_object["disambiguation"] = m_disambiguation;
    json_object["details"] = m_details;
    return json_object;
}

WordEntry* WordEntry::load_v1(const QJsonObject& json_object, QObject* parent, const QList<CommonWordEntry*>& words)
{
    WordEntry* word_entry = new WordEntry(parent);
    word_entry->m_value = json_object["value"].toString();
    word_entry->m_disambiguation = json_object["disambiguation"].toString();
    word_entry->m_details = json_object["details"].toString();
    return word_entry;
}
