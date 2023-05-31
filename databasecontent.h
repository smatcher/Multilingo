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

    void save();

private:
    friend class DictionaryModel;
    friend class WordCollectionModel;

    void addWord(CommonWordEntry* common_word_entry);

    QList<WordCollection*>& collections();
    QList<LanguageDictionary*>& languages();
    QList<CommonWordEntry*>& words();

signals:
    void touched();
    void untouched();

private:
    QList<LanguageDictionary*> m_languages;
    QList<WordCollection*> m_collections;
    QList<CommonWordEntry*> m_words;

    bool m_touched;
};

#endif // DATABASECONTENT_H
