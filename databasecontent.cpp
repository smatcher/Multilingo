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

void DatabaseContent::save()
{    
    QJsonObject json_object;

    json_object["version"] = 1;

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

    QFile file(file_location.filePath("multilingo.json"));

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

}

void DatabaseContent::load_v1(QJsonObject& json_object)
{

}
