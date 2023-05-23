#include "wordentry.h"

WordEntry::WordEntry(QObject *parent)
    : QObject{parent}
    , m_type(WordType::None)
{}
