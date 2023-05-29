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

    qint64 addWord(CommonWordEntry* common_word_entry);
    qint64 numWordIndices() const;

    QList<WordCollection*>& getCollections();
    QList<LanguageDictionary*>& getLanguages();
    QMap<qint64, CommonWordEntry*>& getWords();

signals:
    void touched();
    void untouched();

private:
    QList<LanguageDictionary*> m_languages;
    QList<WordCollection*> m_collections;
    QMap<qint64, CommonWordEntry*> m_words;
    qint64 m_next_index;

    bool m_touched;
};

#endif // DATABASECONTENT_H
