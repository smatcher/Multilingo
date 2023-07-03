#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class CommonWordEntry;

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

    QJsonObject save() const;
    static WordEntry* load_v1(const QJsonObject& json_object, QObject* parent, const QList<CommonWordEntry*>& words);

private:
    QString m_value;
    QString m_disambiguation;
    QString m_details;

signals:

};

#endif // WORDENTRY_H
