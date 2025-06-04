#ifndef DISPLAY_HOUSE_DIALOG_H
#define DISPLAY_HOUSE_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include "table_hachage.h"

class DisplayHouseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayHouseDialog(table_hachage* table, QWidget *parent = nullptr);

private:
    void setupUI();
    void displayHouseInfo(MAISON* maison);
    table_hachage* tableHachage;
    QVBoxLayout* mainLayout;
    QScrollArea* scrollArea;
};

#endif // DISPLAY_HOUSE_DIALOG_H
