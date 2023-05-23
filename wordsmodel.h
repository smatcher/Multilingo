#ifndef WORDSMODEL_H
#define WORDSMODEL_H

#include <QAbstractTableModel>

class WordsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WordsModel(QObject *parent = nullptr);
};

#endif // WORDSMODEL_H
