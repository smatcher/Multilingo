#ifndef WORDSCATEGORY_H
#define WORDSCATEGORY_H

#include <QObject>
#include <QString>
#include <QSet>

class WordsCategory : public QObject
{
    Q_OBJECT
public:
    explicit WordsCategory(QObject *parent, const QString& name);

    const QString& getName() const;

private:
    QString m_name;
    QSet<qint64> m_word_ids;
};

#endif // WORDSCATEGORY_H
