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

LanguageDictionary* LanguageDictionary::load_v1(const QJsonObject& json_object, QObject* parent, const QList<CommonWordEntry*>& words)
{
    LanguageDictionary* language_dictionary = new LanguageDictionary(parent, json_object["name"].toString());
    QJsonArray json_words = json_object["words"].toArray();
    for (int word_index=0; word_index<json_words.count(); ++word_index) {
        const auto& json_word = json_words[word_index];
        if (json_word.isObject()) {
            language_dictionary->m_words.insert(words[word_index], WordEntry::load_v1(json_word.toObject(), parent, words));
        }
    }
    return language_dictionary;
}
