#include "languagedictionary.h"

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
