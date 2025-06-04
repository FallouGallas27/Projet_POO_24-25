#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeConnecter.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tableHachage(nullptr)
{
    ui->setupUi(this);
    NotreConnection();
    initialiserTableHachage();
}

MainWindow::~MainWindow()
{
    if (tableHachage) {
        delete tableHachage;
    }
    delete ui;
}

void MainWindow::initialiserTableHachage()
{
    tableHachage = new table_hachage();
}

void MainWindow::afficherMessage(const QString &titre, const QString &message)
{
    QMessageBox::information(this, titre, message);
}

// Slots pour le menu Base
void MainWindow::on_actionCharger_triggered()
{
    if (tableHachage) {
        tableHachage->charger();
        afficherMessage("Chargement", QString("Données chargées avec succès!\nNombre de maisons: %1")
                       .arg(tableHachage->size()));
    }
}

void MainWindow::on_actionAfficher_triggered()
{
    if (tableHachage && !tableHachage->Est_vide()) {
        tableHachage->affiche();
        afficherMessage("Affichage", "Les données ont été affichées dans la console de débogage.");
    } else {
        afficherMessage("Affichage", "Aucune donnée à afficher. Veuillez d'abord charger des données.");
    }
}

void MainWindow::on_actionTaille_triggered()
{
    if (tableHachage) {
        int taille = tableHachage->size();
        afficherMessage("Taille", QString("Nombre de maisons dans la table: %1").arg(taille));
    }
}

void MainWindow::on_actionSauvegarder_triggered()
{
    if (tableHachage && !tableHachage->Est_vide()) {
        tableHachage->sauvegarder();
    } else {
        afficherMessage("Sauvegarde", "Aucune donnée à sauvegarder.");
    }
}

void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}

// Slots pour le menu Maison
void MainWindow::on_actionRecherche_triggered()
{
    if (!tableHachage || tableHachage->Est_vide()) {
        afficherMessage("Recherche", "Aucune donnée disponible. Veuillez d'abord charger des données.");
        return;
    }

    bool ok;
    QString cle = QInputDialog::getText(this, "Recherche de maison",
                                       "Entrez l'ID de la maison à rechercher:",
                                       QLineEdit::Normal, "", &ok);

    if (ok && !cle.isEmpty()) {
        if (tableHachage->contient(cle)) {
            VALEUR valeur = tableHachage->get(cle);
            QString info = QString("Maison trouvée:\n"
                                 "Type: %1\n"
                                 "Standing: %2\n"
                                 "Modèle: %3\n"
                                 "Chambres: %4\n"
                                 "Toilettes: %5\n"
                                 "Description: %6\n"
                                 "Nombre de photos: %7")
                         .arg(valeur.type)
                         .arg(valeur.standing)
                         .arg(valeur.modele)
                         .arg(valeur.nombre_de_chambre)
                         .arg(valeur.nombre_de_toilettes)
                         .arg(valeur.description)
                         .arg(valeur.photos.size());
            afficherMessage("Résultat de recherche", info);
        } else {
            afficherMessage("Résultat de recherche", "Maison non trouvée.");
        }
    }
}

void MainWindow::on_actionInserer_triggered()
{
    if (!tableHachage) {
        return;
    }

    bool ok;
    QString cle = QInputDialog::getText(this, "Insérer une maison",
                                       "Entrez l'ID de la maison:",
                                       QLineEdit::Normal, "", &ok);

    if (ok && !cle.isEmpty()) {
        if (tableHachage->contient(cle)) {
            afficherMessage("Insertion", "Une maison avec cet ID existe déjà.");
            return;
        }

        QString type = QInputDialog::getText(this, "Type de maison",
                                           "Entrez le type de maison:",
                                           QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString standing = QInputDialog::getText(this, "Standing",
                                               "Entrez le standing:",
                                               QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString modele = QInputDialog::getText(this, "Modèle",
                                             "Entrez le modèle:",
                                             QLineEdit::Normal, "", &ok);
        if (!ok) return;

        int chambres = QInputDialog::getInt(this, "Chambres",
                                          "Nombre de chambres:",
                                          1, 1, 20, 1, &ok);
        if (!ok) return;

        int toilettes = QInputDialog::getInt(this, "Toilettes",
                                           "Nombre de toilettes:",
                                           1, 1, 10, 1, &ok);
        if (!ok) return;

        QString description = QInputDialog::getText(this, "Description",
                                                  "Entrez la description:",
                                                  QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QVector<QString> photos; // Vide pour l'instant
        VALEUR valeur = creerVal(type, standing, chambres, toilettes, modele, description, photos);

        tableHachage->inserer(cle, valeur);
        afficherMessage("Insertion", "Maison insérée avec succès!");
    }
}

void MainWindow::on_actionSupprimer_triggered()
{
    if (!tableHachage || tableHachage->Est_vide()) {
        afficherMessage("Suppression", "Aucune donnée disponible.");
        return;
    }

    bool ok;
    QString cle = QInputDialog::getText(this, "Supprimer une maison",
                                       "Entrez l'ID de la maison à supprimer:",
                                       QLineEdit::Normal, "", &ok);

    if (ok && !cle.isEmpty()) {
        if (tableHachage->contient(cle)) {
            tableHachage->supprimer(cle);
            afficherMessage("Suppression", "Maison supprimée avec succès!");
        } else {
            afficherMessage("Suppression", "Maison non trouvée.");
        }
    }
}

// Slots pour le menu FonctionHachage
void MainWindow::on_actionF1_2_triggered()
{
    if (tableHachage) {
        tableHachage->setHachage_actuelle(1);
        afficherMessage("Fonction de hachage", "Fonction de hachage F1 activée.");
    }
}

void MainWindow::on_actionF2_2_triggered()
{
    if (tableHachage) {
        tableHachage->setHachage_actuelle(2);
        afficherMessage("Fonction de hachage", "Fonction de hachage F2 activée.");
    }
}

void MainWindow::on_actionF3_2_triggered()
{
    if (tableHachage) {
        tableHachage->setHachage_actuelle(3);
        afficherMessage("Fonction de hachage", "Fonction de hachage F3 activée.");
    }
}

void MainWindow::on_actionSansHach_triggered()
{
    if (tableHachage) {
        tableHachage->setHachage_actuelle(4);
        afficherMessage("Fonction de hachage", "Mode sans hachage activé (stockage séquentiel).");
    }
}

// Slots pour le menu Courbe
void MainWindow::on_actionHachage_SansHachage_triggered()
{
    // Fonctionnalité pour comparer les performances hachage vs sans hachage
    afficherMessage("Comparaison", "Fonctionnalité de comparaison Hachage/Sans hachage à implémenter.");
}

void MainWindow::on_actionHachage_fi_hachage_fi_triggered()
{
    // Fonctionnalité pour comparer différentes fonctions de hachage
    if (tableHachage) {
        QString info = QString("Fonction de hachage actuelle: F%1").arg(tableHachage->getHachage_actuelle());
        afficherMessage("Fonction actuelle", info);
    }
}

void MainWindow::on_actionAfficherMaisons_triggered()
{
    if (!tableHachage || tableHachage->Est_vide()) {
        afficherMessage("Affichage", "Aucune maison à afficher. Veuillez d'abord charger des données.");
        return;
    }

    DisplayHouseDialog* dialog = new DisplayHouseDialog(tableHachage, this);
    dialog->exec();
}
