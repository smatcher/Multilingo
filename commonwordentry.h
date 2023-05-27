#ifndef COMMONWORDENTRY_H
#define COMMONWORDENTRY_H

#include <QObject>

enum class WordType {
    None,
    Verb,
    Noun,
    Adjective,
    Adverb,
    Determiner
};

class CommonWordEntry : public QObject
{
    Q_OBJECT
public:
    explicit CommonWordEntry(QObject *parent = nullptr);

    void setType(WordType type_);
    WordType type();

private:
    WordType m_type;

signals:

};

#endif // COMMONWORDENTRY_H
