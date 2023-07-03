#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H

#include "commonwordentry.h"

#include <QObject>
#include <QString>
#include <QSet>
#include <QJsonObject>

class WordCollection : public QObject
{
    Q_OBJECT
public:
    explicit WordCollection(QObject *parent, const QString& name);

    const QString& getName() const;

    QJsonObject save(const QHash<const CommonWordEntry*, int>& word_indices) const;
    static WordCollection* load_v1(const QJsonObject& json_object, QObject* parent, const QList<CommonWordEntry*>& words);

private:
    QString m_name;
    QSet<CommonWordEntry*> m_words;
};

#endif // WORDCOLLECTION_H
