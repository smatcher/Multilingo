#include "managelanguageswindow.h"
#include "ui_managelanguageswindow.h"

#include <algorithm>

#include <QInputDialog>
#include <QMessageBox>
#include <QShortcut>

ManageLanguagesWindow::ManageLanguagesWindow(QWidget *parent, DatabaseContent* database_content)
    : QDialog(parent)
    , ui(new Ui::ManageLanguagesWindow)
    , m_database_content(database_content)
{
    ui->setupUi(this);

    const QList<LanguageDictionary*>& database_languages = m_database_content->getLanguages();

    m_language_list_model = new QStringListModel(this);
    QStringList initial_languages;
    if (database_languages.isEmpty())
    {
        initial_languages.push_back(QLocale::languageToString(QLocale::system().language()));
    }
    else
    {
        for (const auto& language : database_languages)
        {
            if (language) {
                initial_languages.push_back(language->getLanguageName());
            }
        }
    }
    m_language_list_model->setStringList(initial_languages);
    ui->languagesList->setModel(m_language_list_model);

    QStringList known_languages;
    {
        QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
        QSet<QString> iso639Languages;
        for(const QLocale &locale : allLocales) {
            iso639Languages.insert(QLocale::languageToString(locale.language()));
        }
        known_languages = QStringList(iso639Languages.begin(), iso639Languages.end());
        std::sort(known_languages.begin(), known_languages.end());
    }

    auto addLanguage = [=]() {
        bool ok;
        QString languageName = QInputDialog::getItem(this, "Add language", "Language name:", known_languages, 0, true, &ok);
        if (ok && !languageName.isEmpty() && !m_language_list_model->stringList().contains(languageName)) {
            if (m_language_list_model->insertRow(m_language_list_model->rowCount())) {
                QModelIndex index = m_language_list_model->index(m_language_list_model->rowCount() - 1);
                m_language_list_model->setData(index, languageName);
            }
        }
    };

    auto removeLanguage = [=]() {
        if (ui->languagesList->selectionModel()->hasSelection()) {
            QModelIndex selected = ui->languagesList->selectionModel()->currentIndex();
            m_language_list_model->removeRow(selected.row());
        }
    };

    QObject::connect(ui->addButton, &QPushButton::clicked, this, addLanguage);
    QObject::connect(ui->removeButton, &QPushButton::clicked, this, removeLanguage);

    QShortcut* removeShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->languagesList);
    QObject::connect(removeShortcut, &QShortcut::activated, this, removeLanguage);
}

ManageLanguagesWindow::~ManageLanguagesWindow()
{
    delete ui;
}

void ManageLanguagesWindow::accept()
{
    QList<LanguageDictionary*>& database_languages = m_database_content->getLanguages();

    QStringList new_language_list = m_language_list_model->stringList();
    QStringList added_languages;
    for (const auto& language : new_language_list)
    {
        auto matching_it = std::find_if(
            database_languages.begin(),
            database_languages.end(),
            [language](LanguageDictionary* cmp_language) {
                return cmp_language && cmp_language->getLanguageName() == language;
            }
        );
        if (matching_it == database_languages.end())
        {
            added_languages.push_back(language);
        }
    }

    QList<LanguageDictionary*> removed_languages;
    for (const auto& language : database_languages)
    {
        if (language)
        {
            const QString& language_name = language->getLanguageName();
            auto matching_it = std::find_if(
                new_language_list.begin(),
                new_language_list.end(),
                [language_name](QString& cmp_language) {
                    return cmp_language == language_name;
                }
                );
            if (matching_it == new_language_list.end())
            {
                removed_languages.push_back(language);
            }
        }
    }

    bool touch_db = false;
    if (!removed_languages.isEmpty())
    {
        QString question = "You are about to delete the following languages:";
        for (const auto& language : removed_languages) {
            question += QString("\n - %1").arg(language->getLanguageName());
        }
        question += "\n\nThis will also remove any translation for words in these languages. Are you sure?";
        auto reply = QMessageBox::question(this, "Confirm modification",
                                           question,
                                           QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No
                                           );

        if (reply == QMessageBox::StandardButton::No)
        {
            return;
        }
        // follow through, let's remove things
        for (const auto& language_to_remove : removed_languages)
        {
            database_languages.removeAll(language_to_remove);
            delete language_to_remove;
        }
        touch_db = true;
    }

    for (const auto& language : added_languages)
    {
        int index = new_language_list.indexOf(language);
        database_languages.insert(index, new LanguageDictionary(m_database_content, language));
        touch_db = true;
    }

    if (touch_db) {
        m_database_content->touch();
    }

    QDialog::accept();
}
