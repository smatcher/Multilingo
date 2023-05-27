#ifndef DATABASECONTENT_H
#define DATABASECONTENT_H

#include "languagedictionary.h"
#include "commonwordentry.h"
#include "wordcollection.h"

#include <QList>
#include <QMap>

class DatabaseContent : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseContent(QObject *parent = nullptr);

    void touch();
    void untouch();
    bool isTouched();

    quint64 addWord(CommonWordEntry* common_word_entry);

public:
    QList<WordCollection*>& getCollections();
    QList<LanguageDictionary*>& getLanguages();
    QMap<qint64, CommonWordEntry*>& getWords();

private:
    QList<LanguageDictionary*> m_languages;
    QList<WordCollection*> m_collections;
    QMap<qint64, CommonWordEntry*> m_words;
    qint64 m_next_index;

    bool m_touched;
};

#endif // DATABASECONTENT_H
