#include "wordcategoriesmodel.h"

#include <algorithm>

WordCategoriesModel::WordCategoriesModel(QObject *parent, DatabaseContent* database_content)
    : QAbstractListModel{parent}
    , m_database_content(database_content)
{

}

int WordCategoriesModel::rowCount(const QModelIndex& index) const
{
    return 1 + m_database_content->getCategories().count();
}

QVariant WordCategoriesModel::data(const QModelIndex& index, int role) const
{
    const auto& categories = m_database_content->getCategories();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
            return QVariant("All");
        else if (index.row() <= categories.count())
            return QVariant(categories.at(index.row() - 1)->getName());
    }

    return QVariant();
}

void WordCategoriesModel::addCategory(QString categoryName)
{
    auto& categories = m_database_content->getCategories();

    beginInsertRows(QModelIndex(), categories.count() + 1, categories.count() + 2);
    categories.push_back(new WordsCategory(parent(), categoryName));
    endInsertRows();

    m_database_content->touch();
}

void WordCategoriesModel::removeCategories(const QModelIndexList& categoriesToRemove)
{
    QList<int> indicesToRemove;
    for (const auto& categoryToRemove : categoriesToRemove) {
        if (categoryToRemove.isValid() && categoryToRemove.row() > 0) {
            indicesToRemove.push_back(categoryToRemove.row() - 1);
        }
    }

    if (indicesToRemove.isEmpty())
        return;
    std::sort(indicesToRemove.begin(), indicesToRemove.end());
    std::reverse(indicesToRemove.begin(), indicesToRemove.end());

    beginResetModel();
    auto& categories = m_database_content->getCategories();
    for (int index : indicesToRemove) {
        categories.removeAt(index);
    }
    endResetModel();

    m_database_content->touch();
}
