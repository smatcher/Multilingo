#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "addwordwindow.h"
#include "managelanguageswindow.h"
#include "wordcollectionmodel.h"

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
    
    WordCollectionModel* collections_model = new WordCollectionModel(this, m_database_content);

    auto addCollection = [=]() {
        bool ok;
        QString collectionName = QInputDialog::getText(this, "Add collection", "Collection name:", QLineEdit::Normal, "New Collection", &ok);
        if (ok && !collectionName.isEmpty()) {
            collections_model->addCollection(collectionName);
        }
    };

    auto removeSelectedCollections = [=]() {
        auto selected_indices = ui->collectionsList->selectionModel()->selection().indexes();
        if (!selected_indices.isEmpty()) {
            QString msgbox_question = QString("Are you sure that you want to remove %1 %2?\nWords in the collection will not be removed.")
                                          .arg(selected_indices.count())
                                          .arg(selected_indices.count() == 1 ? "collection" : "collections");
            if (QMessageBox::question(this, "Remove collection", msgbox_question) == QMessageBox::StandardButton::Yes) {
                collections_model->removeCollections(selected_indices);
            }
        }
    };

    ui->collectionsList->setModel(collections_model);
    ui->addCollectionButton->setDefaultAction(ui->actionAdd_collection);
    
    QObject::connect(ui->actionAdd_collection, &QAction::triggered, this, addCollection);
    QObject::connect(ui->removeCollectionButton, &QPushButton::clicked, this, removeSelectedCollections );

    QShortcut* removeCollectionShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->collectionsList);
    QObject::connect(removeCollectionShortcut, &QShortcut::activated, this, removeSelectedCollections );

    ui->addWordButton->setDefaultAction(ui->actionAdd_word);
    QObject::connect(ui->actionAdd_word, &QAction::triggered,
                     this, [=](){
                         AddWordWindow w(this, m_database_content);
                         w.exec();
                     });

    QObject::connect(ui->actionManage_languages, &QAction::triggered,
                     this, [=](){
                        ManageLanguagesWindow w(this, m_database_content);
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
