#ifndef ADDWORDWINDOW_H
#define ADDWORDWINDOW_H

#include "dictionarymodel.h"

#include <QDialog>

namespace Ui {
class AddWordWindow;
}

class AddWordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWordWindow(QWidget *parent, DictionaryModel* dictionary_model);
    ~AddWordWindow();

public slots:
    void accept();

private:
    Ui::AddWordWindow *ui;
    DictionaryModel* m_dictionary_model;
    QList<WordEntry*> m_word_entries;
    CommonWordEntry* m_common_word_entry;
};

#endif // ADDWORDWINDOW_H
