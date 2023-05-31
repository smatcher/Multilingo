#include "databasecontent.h"

DatabaseContent::DatabaseContent(QObject *parent)
    : QObject{parent}
    , m_touched(false)
{

}

void DatabaseContent::touch()
{
    m_touched = true;
    emit touched();
}

void DatabaseContent::untouch()
{
    m_touched = false;
    emit untouched();
}

bool DatabaseContent::isTouched()
{
    return m_touched;
}

QList<WordCollection*>& DatabaseContent::collections()
{
    return m_collections;
}

QList<LanguageDictionary*>& DatabaseContent::languages()
{
    return m_languages;
}

QList<CommonWordEntry*>& DatabaseContent::words()
{
    return m_words;
}

void DatabaseContent::addWord(CommonWordEntry* common_word_entry)
{
    m_words.push_back(common_word_entry);
    common_word_entry->setParent(this);
    touch();
}

void DatabaseContent::save()
{
    untouch();
}
