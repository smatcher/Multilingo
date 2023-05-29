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

public slots:
    void tempInvalidate();

private:
    DatabaseContent* m_database_content;
};

#endif // DICTIONARYMODEL_H
