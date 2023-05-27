#ifndef ADDWORDWINDOW_H
#define ADDWORDWINDOW_H

#include "databasecontent.h"

#include <QDialog>

namespace Ui {
class AddWordWindow;
}

class AddWordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWordWindow(QWidget *parent, DatabaseContent* database_content);
    ~AddWordWindow();

public slots:
    void accept();

private:
    Ui::AddWordWindow *ui;
    DatabaseContent* m_database_content;
    QList<WordEntry*> m_word_entries;
    CommonWordEntry* m_common_word_entry;
};

#endif // ADDWORDWINDOW_H
