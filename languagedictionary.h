#ifndef LANGUAGEDICTIONARY_H
#define LANGUAGEDICTIONARY_H

#include "commonwordentry.h"
#include "wordentry.h"

#include <QHash>

class LanguageDictionary : public QObject
{
    Q_OBJECT
public:
    explicit LanguageDictionary(QObject *parent, const QString& name);

    const QString& getLanguageName() const;
    void addWord(CommonWordEntry* word_common_entry, WordEntry* word_entry);
    WordEntry* findWord(CommonWordEntry* word_common_entry);

    QJsonObject save(const QHash<const CommonWordEntry*, int>& word_indices) const;

private:
    QString m_language_name;
    QHash<CommonWordEntry*, WordEntry*> m_words;

signals:

};

#endif // LANGUAGEDICTIONARY_H
