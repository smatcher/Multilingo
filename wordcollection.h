#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H

#include "commonwordentry.h"

#include <QObject>
#include <QString>
#include <QSet>

class WordCollection : public QObject
{
    Q_OBJECT
public:
    explicit WordCollection(QObject *parent, const QString& name);

    const QString& getName() const;

private:
    QString m_name;
    QSet<CommonWordEntry*> m_words;
};

#endif // WORDCOLLECTION_H
