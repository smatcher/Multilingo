#include "databasecontent.h"

DatabaseContent::DatabaseContent(QObject *parent)
    : QObject{parent}
    , m_next_index(0)
    , m_touched(false)
{

}

void DatabaseContent::touch()
{
    m_touched = true;
}

void DatabaseContent::untouch()
{
    m_touched = false;
}

bool DatabaseContent::isTouched()
{
    return m_touched;
}

QList<WordCollection*>& DatabaseContent::getCollections()
{
    return m_collections;
}

QList<LanguageDictionary*>& DatabaseContent::getLanguages()
{
    return m_languages;
}
