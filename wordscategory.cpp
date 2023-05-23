#include "wordscategory.h"

WordsCategory::WordsCategory(QObject *parent, const QString& name)
    : QObject{parent}
    , m_name(name)
{

}

const QString& WordsCategory::getName() const
{
    return m_name;
}
