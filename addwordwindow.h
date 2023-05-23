#ifndef ADDWORDWINDOW_H
#define ADDWORDWINDOW_H

#include <QDialog>

namespace Ui {
class AddWordWindow;
}

class AddWordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWordWindow(QWidget *parent = nullptr);
    ~AddWordWindow();

private:
    Ui::AddWordWindow *ui;
};

#endif // ADDWORDWINDOW_H
