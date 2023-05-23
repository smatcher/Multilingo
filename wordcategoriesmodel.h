#ifndef WORDCATEGORIESMODEL_H
#define WORDCATEGORIESMODEL_H

#include "databasecontent.h"

#include <QAbstractListModel>
#include <QAction>

class WordCategoriesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WordCategoriesModel(QObject *parent, DatabaseContent* database_content);

    int rowCount(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;

private:
    DatabaseContent* m_database_content;

public slots:
    void addCategory(QString categoryName);
    void removeCategories(const QModelIndexList& categoriesToRemove);
};

#endif // WORDCATEGORIESMODEL_H
