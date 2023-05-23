#ifndef MANAGELANGUAGESWINDOW_H
#define MANAGELANGUAGESWINDOW_H

#include <QDialog>

namespace Ui {
class ManageLanguagesWindow;
}

class ManageLanguagesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManageLanguagesWindow(QWidget *parent = nullptr);
    ~ManageLanguagesWindow();

private:
    Ui::ManageLanguagesWindow *ui;
};

#endif // MANAGELANGUAGESWINDOW_H
