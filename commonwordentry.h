#ifndef COMMONWORDENTRY_H
#define COMMONWORDENTRY_H

#include <QObject>
#include <QJsonObject>

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

    QJsonObject save() const;
    static CommonWordEntry* load_v1(const QJsonObject& json_object, QObject* parent);

private:
    WordType m_type;

signals:

};

#endif // COMMONWORDENTRY_H
