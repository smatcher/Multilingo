#include "addwordwindow.h"
#include "ui_addwordwindow.h"

#include <algorithm>

#include "wordentrywidget.h"

AddWordWindow::AddWordWindow(QWidget *parent, DatabaseContent* database_content)
    : QDialog(parent)
    , ui(new Ui::AddWordWindow)
    , m_database_content(database_content)
{
    ui->setupUi(this);

    auto& database_languages = m_database_content->getLanguages();

    m_word_entries.reserve(database_languages.count());
    m_common_word_entry = new CommonWordEntry(this);

    for (auto& language : database_languages)
    {
        WordEntry* entry_for_language = new WordEntry(this);
        WordEntryWidget* entry_widget = new WordEntryWidget(ui->languageTabs, entry_for_language);

        ui->languageTabs->addTab(entry_widget, language->getLanguageName());

        m_word_entries.append(entry_for_language);
    }
}

AddWordWindow::~AddWordWindow()
{
    delete ui;
}

void AddWordWindow::accept()
{
    auto& database_languages = m_database_content->getLanguages();

    bool has_any_data = false;
    for (int language_index = 0; language_index < database_languages.count(); ++language_index)
    {
        WordEntryWidget* language_widget = static_cast<WordEntryWidget*>(ui->languageTabs->widget(language_index));
        language_widget->apply_changes();

        if (m_word_entries[language_index]->hasData()) {
            has_any_data = true;
        }
    }

    m_common_word_entry->setType(static_cast<WordType>(ui->wordTypeCombo->currentIndex()));

    if (has_any_data)
    {
        qint64 word_index = m_database_content->addWord(m_common_word_entry);
        for (int language_index = 0; language_index < database_languages.count(); ++language_index)
        {
            WordEntry* word_entry = m_word_entries[language_index];

            if (!word_entry->hasData())
                continue;

            m_database_content->getLanguages()[language_index]->addWord(word_index, word_entry);
        }

        m_database_content->touch();
    }

    QDialog::accept();
}
