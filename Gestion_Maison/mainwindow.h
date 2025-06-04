#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table_hachage.h"
#include "DisplayHouseDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherMessage(const QString &titre, const QString &message);

private slots:
    // Base menu slots
    void on_actionCharger_triggered();
    void on_actionAfficher_triggered();
    void on_actionTaille_triggered();
    void on_actionSauvegarder_triggered();
    void on_actionQuitter_triggered();

    // Maison menu slots
    void on_actionRecherche_triggered();
    void on_actionInserer_triggered();
    void on_actionSupprimer_triggered();

    // FonctionHachage menu slots
    void on_actionF1_2_triggered();
    void on_actionF2_2_triggered();
    void on_actionF3_2_triggered();
    void on_actionSansHach_triggered();

    // Courbe menu slots
    void on_actionHachage_SansHachage_triggered();
    void on_actionHachage_fi_hachage_fi_triggered();

    // New slot for displaying houses
    void on_actionAfficherMaisons_triggered();

private:
    void initialiserTableHachage();

    Ui::MainWindow *ui;
    table_hachage *tableHachage;
};

#endif // MAINWINDOW_H
