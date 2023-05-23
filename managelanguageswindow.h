#ifndef MANAGELANGUAGESWINDOW_H
#define MANAGELANGUAGESWINDOW_H

#include "databasecontent.h"

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class ManageLanguagesWindow;
}

class ManageLanguagesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManageLanguagesWindow(QWidget *parent, DatabaseContent* database_content);
    ~ManageLanguagesWindow();

public slots:
    void accept();

private:
    Ui::ManageLanguagesWindow *ui;
    DatabaseContent* m_database_content;
    QStringListModel* m_language_list_model;
};

#endif // MANAGELANGUAGESWINDOW_H
