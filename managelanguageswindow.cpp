#include "managelanguageswindow.h"
#include "ui_managelanguageswindow.h"

#include <algorithm>

#include <QInputDialog>
#include <QShortcut>
#include <QStringListModel>

ManageLanguagesWindow::ManageLanguagesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageLanguagesWindow)
{
    ui->setupUi(this);

    QStringListModel* languages_model = new QStringListModel(this);
    QStringList default_languages;
    default_languages.push_back(QLocale::languageToString(QLocale::system().language()));
    languages_model->setStringList(default_languages);
    ui->languagesList->setModel(languages_model);

    QStringList known_languages;
    {
        QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
        QSet<QString> iso639Languages;
        for(const QLocale &locale : allLocales) {
            iso639Languages.insert(QLocale::languageToString(locale.language()));
        }
        known_languages = QStringList(iso639Languages.begin(), iso639Languages.end());
        std::sort(known_languages.begin(), known_languages.end());
    }

    auto addLanguage = [=]() {
        bool ok;
        QString languageName = QInputDialog::getItem(this, "Add language", "Language name:", known_languages, 0, true, &ok);
        if (ok && !languageName.isEmpty() && !languages_model->stringList().contains(languageName)) {
            if (languages_model->insertRow(languages_model->rowCount())) {
                QModelIndex index = languages_model->index(languages_model->rowCount() - 1);
                languages_model->setData(index, languageName);
            }
        }
    };

    auto removeLanguage = [=]() {
        if (ui->languagesList->selectionModel()->hasSelection()) {
            QModelIndex selected = ui->languagesList->selectionModel()->currentIndex();
            languages_model->removeRow(selected.row());
        }
    };

    QObject::connect(ui->addButton, &QPushButton::clicked, this, addLanguage);
    QObject::connect(ui->removeButton, &QPushButton::clicked, this, removeLanguage);

    QShortcut* removeShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->languagesList);
    QObject::connect(removeShortcut, &QShortcut::activated, this, removeLanguage);
}

ManageLanguagesWindow::~ManageLanguagesWindow()
{
    delete ui;
}
