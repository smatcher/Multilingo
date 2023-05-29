#include "dictionarymodel.h"

DictionaryModel::DictionaryModel(QObject *parent, DatabaseContent* database_content)
    : QAbstractTableModel{parent}
    , m_database_content(database_content)
{

}

int DictionaryModel::rowCount(const QModelIndex& index) const
{
    return m_database_content->numWordIndices();
}

int DictionaryModel::columnCount(const QModelIndex& index) const
{
    return m_database_content->getLanguages().count();
}

QVariant DictionaryModel::data(const QModelIndex& index, int role) const
{
    const auto& languages = m_database_content->getLanguages();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() >= 0 && index.column() <= languages.count())
        {
            qint64 word_index = static_cast<qint64>(index.row());
            WordEntry* word_entry = languages.at(index.column())->findWord(word_index);
            if (word_entry != nullptr)
            {
                return QVariant(word_entry->toString());
            }
        }
    }

    return QVariant();
}

QVariant DictionaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Orientation::Horizontal)
    {
        const auto& languages = m_database_content->getLanguages();
        if (section >= 0 && section <= languages.count())
        {
            return QVariant(languages.at(section)->getLanguageName());
        }
    }

    return QVariant();
}

void DictionaryModel::tempInvalidate()
{
    beginResetModel();
    // TODO: we should not rely on this but instead changes to the data should pass through the model
    endResetModel();
}
