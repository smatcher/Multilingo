#ifndef DATABASECONTENT_H
#define DATABASECONTENT_H

#include "languagedictionary.h"
#include "wordcollection.h"

#include <QList>

class DatabaseContent : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseContent(QObject *parent = nullptr);

    void touch();
    void untouch();
    bool isTouched();

public:
    QList<WordCollection*>& getCollections();
    QList<LanguageDictionary*>& getLanguages();

private:
    QList<LanguageDictionary*> m_languages;
    QList<WordCollection*> m_collections;
    qint64 m_next_index;

    bool m_touched;
};

#endif // DATABASECONTENT_H
