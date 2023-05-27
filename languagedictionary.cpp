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

void LanguageDictionary::addWord(qint64 word_index, WordEntry* word_entry)
{
    m_words.insert(word_index, word_entry);
    word_entry->setParent(this);
}
