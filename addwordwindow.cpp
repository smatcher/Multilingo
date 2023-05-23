#include "addwordwindow.h"
#include "ui_addwordwindow.h"

AddWordWindow::AddWordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWordWindow)
{
    ui->setupUi(this);
}

AddWordWindow::~AddWordWindow()
{
    delete ui;
}
