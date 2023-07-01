#include "languagedictionary.h"

#include <QJsonArray>

LanguageDictionary::LanguageDictionary(QObject *parent, const QString& name)
    : QObject{parent}
    , m_language_name(name)
{

}

const QString& LanguageDictionary::getLanguageName() const
{
    return m_language_name;
}

void LanguageDictionary::addWord(CommonWordEntry* word_common_entry, WordEntry* word_entry)
{
    m_words.insert(word_common_entry, word_entry);
    word_entry->setParent(this);
}

WordEntry* LanguageDictionary::findWord(CommonWordEntry* word_common_entry)
{
    auto it = m_words.find(word_common_entry);
    if (it != m_words.end())
    {
        return it.value();
    }
    return nullptr;
}

QJsonObject LanguageDictionary::save(const QHash<const CommonWordEntry*, int>& word_indices) const
{
    QJsonObject json_object;
    json_object["name"] = m_language_name;

    QList<const CommonWordEntry*> common_words;
    common_words.resize(word_indices.count());
    for (auto i = word_indices.cbegin(), end = word_indices.cend(); i != end ; ++i) {
        common_words[i.value()] = i.key();
    }

    QJsonArray json_words;
    for (const auto* common_word : common_words) {
        const auto* translated_word = m_words.value(const_cast<CommonWordEntry*>(common_word), nullptr);
        if (translated_word) {
            json_words.append(translated_word->save());
        } else {
            json_words.append(QJsonValue::Null);
        }
    }
    json_object["words"] = json_words;

    return json_object;
}
