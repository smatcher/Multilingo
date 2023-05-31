#include "dictionarymodel.h"

DictionaryModel::DictionaryModel(QObject *parent, DatabaseContent* database_content)
    : QAbstractTableModel{parent}
    , m_database_content(database_content)
{

}

int DictionaryModel::rowCount(const QModelIndex& index) const
{
    return m_database_content->words().count();
}

int DictionaryModel::columnCount(const QModelIndex& index) const
{
    return m_database_content->languages().count();
}

QVariant DictionaryModel::data(const QModelIndex& index, int role) const
{
    const auto& languages = m_database_content->languages();
    const auto& words = m_database_content->words();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() >= 0 && index.column() < languages.count() && index.row() >= 0 && index.row() < words.count())
        {
            CommonWordEntry* common_word_entry = words.at(index.row());
            WordEntry* word_entry = languages.at(index.column())->findWord(common_word_entry);
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
        const auto& languages = m_database_content->languages();
        if (section >= 0 && section < languages.count())
        {
            return QVariant(languages.at(section)->getLanguageName());
        }
    }

    return QVariant();
}

const QList<LanguageDictionary*>& DictionaryModel::languages() const
{
    return m_database_content->languages();
}

const QList<WordCollection*>& DictionaryModel::collections() const
{
    return m_database_content->collections();
}

void DictionaryModel::addWord(CommonWordEntry* word_entry, const QMap<int, WordEntry*>& translated_words)
{
    int count_before = m_database_content->words().count();
    beginInsertRows(QModelIndex(), count_before, count_before);
    m_database_content->addWord(word_entry);
    for (auto it = translated_words.cbegin(), end = translated_words.cend(); it != end; ++it)
    {
        m_database_content->languages()[it.key()]->addWord(word_entry, it.value());
    }
    endInsertRows();
}

void DictionaryModel::addLanguage(int index, const QString& language)
{
    // TODO: check that the index makes sense
    auto& languages = m_database_content->languages();
    beginInsertColumns(QModelIndex(), index, index);
    languages.insert(index, new LanguageDictionary(m_database_content, language));
    endInsertColumns();
    m_database_content->touch();
}

void DictionaryModel::removeLanguage(LanguageDictionary* language_to_remove)
{
    // TODO: using LanguageDictionary is a bit too low level, it would probably be better to pass a QString instead and resolve here.
    auto& languages = m_database_content->languages();
    int language_index = languages.indexOf(language_to_remove);
    beginRemoveColumns(QModelIndex(), language_index, language_index);
    languages.removeAll(language_to_remove);
    delete language_to_remove;
    endRemoveColumns();
    m_database_content->touch();
}
