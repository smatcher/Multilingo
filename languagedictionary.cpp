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
