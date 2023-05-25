#include "wordcollection.h"

WordCollection::WordCollection(QObject *parent, const QString& name)
    : QObject{parent}
    , m_name(name)
{

}

const QString& WordCollection::getName() const
{
    return m_name;
}
