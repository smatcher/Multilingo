#ifndef DATABASECONTENT_H
#define DATABASECONTENT_H

#include "languagedictionary.h"
#include "wordscategory.h"

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
    QList<WordsCategory*>& getCategories();
    QList<LanguageDictionary*>& getLanguages();

private:
    QList<LanguageDictionary*> m_languages;
    QList<WordsCategory*> m_categories;
    qint64 m_next_index;

    bool m_touched;
};

#endif // DATABASECONTENT_H
