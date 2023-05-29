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
