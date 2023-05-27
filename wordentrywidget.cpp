#include "wordentrywidget.h"
#include "./ui_wordentrywidget.h"

WordEntryWidget::WordEntryWidget(QWidget *parent, WordEntry* word_entry)
    : QWidget{parent}
    , ui(new Ui::WordEntryWidget)
    , m_word_entry(word_entry)
{
    ui->setupUi(this);

    ui->valueEdit->setText(m_word_entry->value());
    ui->disambiguationEdit->setText(m_word_entry->disambiguation());
    ui->detailsEdit->setPlainText(m_word_entry->details());
}

WordEntryWidget::~WordEntryWidget()
{
    delete ui;
}

void WordEntryWidget::apply_changes()
{
    m_word_entry->setValue(ui->valueEdit->text());
    m_word_entry->setDisambiguation(ui->disambiguationEdit->text());
    m_word_entry->setDetails(ui->detailsEdit->toPlainText());
}
