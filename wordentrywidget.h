#ifndef WORDENTRYWIDGET_H
#define WORDENTRYWIDGET_H

#include "wordentry.h"

#include <QWidget>

namespace Ui {
class WordEntryWidget;
}

class WordEntryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WordEntryWidget(QWidget *parent, WordEntry* word_entry);
    ~WordEntryWidget();

private:
    Ui::WordEntryWidget *ui;
    WordEntry* m_word_entry;

public slots:
    void apply_changes();
};

#endif // WORDENTRYWIDGET_H
