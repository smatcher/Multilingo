#ifndef LANGUAGEDICTIONARY_H
#define LANGUAGEDICTIONARY_H

#include "commonwordentry.h"
#include "wordentry.h"

#include <QMap>

class LanguageDictionary : public QObject
{
    Q_OBJECT
public:
    explicit LanguageDictionary(QObject *parent, const QString& name);

    const QString& getLanguageName() const;
    void addWord(CommonWordEntry* word_common_entry, WordEntry* word_entry);
    WordEntry* findWord(CommonWordEntry* word_common_entry);

private:
    QString m_language_name;
    QMap<CommonWordEntry*, WordEntry*> m_words;

signals:

};

#endif // LANGUAGEDICTIONARY_H
