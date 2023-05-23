#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasecontent.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;

    DatabaseContent* m_database_content;

public slots:
    void saveDatabase();
};
#endif // MAINWINDOW_H
