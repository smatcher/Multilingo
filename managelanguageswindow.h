#ifndef MANAGELANGUAGESWINDOW_H
#define MANAGELANGUAGESWINDOW_H

#include "dictionarymodel.h"

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class ManageLanguagesWindow;
}

class ManageLanguagesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManageLanguagesWindow(QWidget *parent, DictionaryModel* dictionary_model);
    ~ManageLanguagesWindow();

public slots:
    void accept();

private:
    Ui::ManageLanguagesWindow *ui;
    DictionaryModel* m_dictionary_model;
    QStringListModel* m_language_list_model;
};

#endif // MANAGELANGUAGESWINDOW_H
