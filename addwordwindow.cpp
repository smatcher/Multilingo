#include "addwordwindow.h"
#include "ui_addwordwindow.h"

AddWordWindow::AddWordWindow(QWidget *parent, DatabaseContent* database_content)
    : QDialog(parent)
    , ui(new Ui::AddWordWindow)
    , m_database_content(database_content)
{
    ui->setupUi(this);
}

AddWordWindow::~AddWordWindow()
{
    delete ui;
}
