#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "addwordwindow.h"
#include "managelanguageswindow.h"
#include "wordcategoriesmodel.h"

#include <QCloseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_database_content = new DatabaseContent(this);

    WordCategoriesModel* categories_model = new WordCategoriesModel(this, m_database_content);

    auto addCategory = [=]() {
        bool ok;
        QString categoryName = QInputDialog::getText(this, "Add category", "Category name:", QLineEdit::Normal, "New Category", &ok);
        if (ok && !categoryName.isEmpty()) {
            categories_model->addCategory(categoryName);
        }
    };

    auto removeSelectedCategories = [=]() {
        auto selected_indices = ui->categoriesList->selectionModel()->selection().indexes();
        if (!selected_indices.isEmpty()) {
            QString msgbox_question = QString("Are you sure that you want to remove %1 %2?")
                                          .arg(selected_indices.count())
                                          .arg(selected_indices.count() == 1 ? "category" : "categories");
            if (QMessageBox::question(this, "Remove category", msgbox_question) == QMessageBox::StandardButton::Yes) {
                categories_model->removeCategories(selected_indices);
            }
        }
    };

    ui->categoriesList->setModel(categories_model);
    ui->addCategoryButton->setDefaultAction(ui->actionAdd_category);

    QObject::connect(ui->actionAdd_category, &QAction::triggered, this, addCategory);
    QObject::connect(ui->removeCategoryButton, &QPushButton::clicked, this, removeSelectedCategories);

    QShortcut* removeCategoryShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->categoriesList);
    QObject::connect(removeCategoryShortcut, &QShortcut::activated, this, removeSelectedCategories);

    ui->addWordButton->setDefaultAction(ui->actionAdd_word);
    QObject::connect(ui->actionAdd_word, &QAction::triggered,
                     this, [=](){
                         AddWordWindow w(this);
                         w.exec();
                     });

    QObject::connect(ui->actionManage_languages, &QAction::triggered,
                     this, [=](){
                        ManageLanguagesWindow w(this);
                        w.exec();
                    });

    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveDatabase);
    QObject::connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);

    if (m_database_content->getLanguages().isEmpty()) {
        ui->actionManage_languages->trigger();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDatabase()
{
    qDebug("TODO: save");
    m_database_content->untouch();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    bool bNeedsSave = m_database_content->isTouched();
    if (bNeedsSave) {
        auto reply = QMessageBox::question(this, "File not saved",
            "Do you whish to save changes to the database?",
            QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel
        );

        if (reply == QMessageBox::StandardButton::Cancel)
        {
            event->ignore();
            return;
        }
        if (reply == QMessageBox::StandardButton::Save)
        {
            saveDatabase();
        }
    }
    event->accept();
}
