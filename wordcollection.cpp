#include "wordcollection.h"

#include <QJsonArray>

WordCollection::WordCollection(QObject *parent, const QString& name)
    : QObject{parent}
    , m_name(name)
{

}

const QString& WordCollection::getName() const
{
    return m_name;
}

QJsonObject WordCollection::save(const QHash<const CommonWordEntry*, int>& word_indices) const
{
    QJsonObject json_object;
    json_object["name"] = m_name;

    QJsonArray json_words;
    for (auto* common_word : m_words) {
        json_words.append(word_indices.value(common_word));
    }
    json_object["words"] = json_words;

    return json_object;
}
