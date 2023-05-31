#include "addwordwindow.h"
#include "ui_addwordwindow.h"

#include <algorithm>

#include "wordentrywidget.h"

AddWordWindow::AddWordWindow(QWidget *parent, DictionaryModel* dictionary_model)
    : QDialog(parent)
    , ui(new Ui::AddWordWindow)
    , m_dictionary_model(dictionary_model)
{
    ui->setupUi(this);

    const auto& database_languages = m_dictionary_model->languages();

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
    const auto& database_languages = m_dictionary_model->languages();

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
        QMap<int, WordEntry*> translated_words;
        for (int language_index = 0; language_index < database_languages.count(); ++language_index)
        {
            WordEntry* word_entry = m_word_entries[language_index];
            if (word_entry->hasData())
            {
                translated_words.insert(language_index, word_entry);
            }
        }

        m_dictionary_model->addWord(m_common_word_entry, translated_words);
    }

    QDialog::accept();
}
