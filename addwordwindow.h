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

private:
    Ui::AddWordWindow *ui;
    DatabaseContent* m_database_content;
};

#endif // ADDWORDWINDOW_H
