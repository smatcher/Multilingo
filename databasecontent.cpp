#include "databasecontent.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>

DatabaseContent::DatabaseContent(QObject *parent)
    : QObject{parent}
    , m_touched(false)
{

}

void DatabaseContent::touch()
{
    m_touched = true;
    emit touched();
}

void DatabaseContent::untouch()
{
    m_touched = false;
    emit untouched();
}

bool DatabaseContent::isTouched()
{
    return m_touched;
}

QList<WordCollection*>& DatabaseContent::collections()
{
    return m_collections;
}

QList<LanguageDictionary*>& DatabaseContent::languages()
{
    return m_languages;
}

QList<CommonWordEntry*>& DatabaseContent::words()
{
    return m_words;
}

void DatabaseContent::addWord(CommonWordEntry* common_word_entry)
{
    m_words.push_back(common_word_entry);
    common_word_entry->setParent(this);
    touch();
}

static const QString k_database_filename = "multilingo.json";
static const int k_current_version = 1;

void DatabaseContent::save()
{    
    QJsonObject json_object;

    json_object["version"] = k_current_version;

    QJsonArray json_words;
    QHash<const CommonWordEntry*, int> word_indices;
    for (const auto* common_word : m_words) {
        word_indices.insert(common_word, json_words.count());
        json_words.append(common_word->save());
    }
    json_object["words"] = json_words;

    QJsonArray json_collections;
    for (const auto* collection : m_collections) {
        json_collections.append(collection->save(word_indices));
    }
    json_object["collections"] = json_collections;

    QJsonArray json_dictionaries;
    for (const auto* language : m_languages) {
        json_dictionaries.append(language->save(word_indices));
    }
    json_object["dictionaries"] = json_dictionaries;

    QDir file_location = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    if (!file_location.exists()) {
        file_location.mkdir(".");
    }

    QFile file(file_location.filePath(k_database_filename));

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't save file");
        return;
    }

    QJsonDocument json_doc(json_object);
    file.write(json_doc.toJson());

    untouch();
}

void DatabaseContent::load()
{
    QDir file_location = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QFile file(file_location.filePath(k_database_filename));

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't load file");
        return;
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject json_object = json_doc.object();

    int version = json_object["version"].toInt();

    if (version == 1) {
        load_v1(json_object);
    }
}

void DatabaseContent::load_v1(QJsonObject& json_object)
{
    m_words.clear();
    m_collections.clear();
    m_languages.clear();

    QJsonArray json_words = json_object["words"].toArray();
    for (const auto& json_word : json_words) {
        m_words.append(CommonWordEntry::load_v1(json_word.toObject(), this));
    }

    QJsonArray json_collections = json_object["collections"].toArray();
    for (const auto& json_collection : json_collections) {
        m_collections.append(WordCollection::load_v1(json_collection.toObject(), this, m_words));
    }

    QJsonArray json_dictionaries = json_object["dictionaries"].toArray();
    for (const auto& json_dictionary : json_dictionaries) {
        m_languages.append(LanguageDictionary::load_v1(json_dictionary.toObject(), this, m_words));
    }
}
