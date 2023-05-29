#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <QObject>
#include <QString>

class WordEntry : public QObject
{
    Q_OBJECT
public:
    explicit WordEntry(QObject *parent = nullptr);

    bool hasData() const;

    void setValue(const QString& value_);
    const QString& value() const;

    void setDisambiguation(const QString& disambiguation_);
    const QString& disambiguation() const;

    void setDetails(const QString& details_);
    const QString& details() const;

    QString toString() const;

private:
    QString m_value;
    QString m_disambiguation;
    QString m_details;

signals:

};

#endif // WORDENTRY_H
