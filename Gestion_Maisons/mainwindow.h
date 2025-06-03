#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table_hachage.h"
#include "SeConnecter.h"
#include <QDir>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_getButton_clicked();
    void on_deleteButton_clicked();
    void on_displayButton_clicked();
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_clearButton_clicked();
    void on_detailsButton_clicked();
    bool validatePhotos(const QVector<QString>&, QString&);

private:
    Ui::MainWindow *ui;
    table_hachage *table;
    void clearInputs();
};

#endif // MAINWINDOW_H
