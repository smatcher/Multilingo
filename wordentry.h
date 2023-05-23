#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <QObject>
#include <QString>

enum class WordType {
    None,
    Verb,
    Noun,
    Adjective,
    Adverb,
    Determiner
};

class WordEntry : public QObject
{
    Q_OBJECT
public:
    explicit WordEntry(QObject *parent = nullptr);

private:
    QString m_value;
    QString m_disambiguation;
    QString m_details;
    WordType m_type;

signals:

};

#endif // WORDENTRY_H
