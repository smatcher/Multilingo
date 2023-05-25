#ifndef WORDCOLLECTIONMODEL_H
#define WORDCOLLECTIONMODEL_H

#include "databasecontent.h"

#include <QAbstractListModel>
#include <QAction>

class WordCollectionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WordCollectionModel(QObject *parent, DatabaseContent* database_content);

    int rowCount(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;

private:
    DatabaseContent* m_database_content;

public slots:
    void addCollection(QString collectionName);
    void removeCollections(const QModelIndexList& collectionsToRemove);
};

#endif // WORDCOLLECTIONMODEL_H
