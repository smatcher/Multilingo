#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include "databasecontent.h"

#include <QAbstractTableModel>

class DictionaryModel : public QAbstractTableModel
{
    Q_OBJECT

    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public:
    explicit DictionaryModel(QObject *parent, DatabaseContent* database_content);

    const QList<LanguageDictionary*>& languages() const;
    const QList<WordCollection*>& collections() const;

    void addWord(CommonWordEntry* word_entry, const QMap<int, WordEntry*>& translated_words);

    void addLanguage(int index, const QString& language);
    void removeLanguage(LanguageDictionary* language);

private:
    DatabaseContent* m_database_content;
};

#endif // DICTIONARYMODEL_H
