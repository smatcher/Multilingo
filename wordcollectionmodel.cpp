#include "wordcollectionmodel.h"

#include <algorithm>

WordCollectionModel::WordCollectionModel(QObject *parent, DatabaseContent* database_content)
    : QAbstractListModel{parent}
    , m_database_content(database_content)
{

}

int WordCollectionModel::rowCount(const QModelIndex& index) const
{
    return m_database_content->getCollections().count();
}

QVariant WordCollectionModel::data(const QModelIndex& index, int role) const
{
    const auto& collections = m_database_content->getCollections();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.row() >= 0 && index.row() <= collections.count())
            return QVariant(collections.at(index.row())->getName());
    }

    return QVariant();
}

void WordCollectionModel::addCollection(QString collectionName)
{
    auto& collections = m_database_content->getCollections();

    beginInsertRows(QModelIndex(), collections.count(), collections.count() + 1);
    collections.push_back(new WordCollection(parent(), collectionName));
    endInsertRows();

    m_database_content->touch();
}

void WordCollectionModel::removeCollections(const QModelIndexList& collectionsToRemove)
{
    QList<int> indicesToRemove;
    for (const auto& collectionToRemove : collectionsToRemove) {
        if (collectionToRemove.isValid()) {
            indicesToRemove.push_back(collectionToRemove.row());
        }
    }

    if (indicesToRemove.isEmpty())
        return;
    std::sort(indicesToRemove.begin(), indicesToRemove.end());
    std::reverse(indicesToRemove.begin(), indicesToRemove.end());

    beginResetModel();
    auto& collections = m_database_content->getCollections();
    for (int index : indicesToRemove) {
        collections.removeAt(index);
    }
    endResetModel();

    m_database_content->touch();
}
