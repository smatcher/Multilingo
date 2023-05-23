#ifndef LANGUAGEDICTIONARY_H
#define LANGUAGEDICTIONARY_H

#include "wordentry.h"

#include <QMap>

class LanguageDictionary : public QObject
{
    Q_OBJECT
public:
    explicit LanguageDictionary(QObject *parent = nullptr);

private:
    QString m_language_name;
    QMap<qint64, WordEntry*> m_words;

signals:

};

#endif // LANGUAGEDICTIONARY_H
