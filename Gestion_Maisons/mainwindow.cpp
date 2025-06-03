
//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "SeConnecter.h"
//#include <QMessageBox>
//#include <QDebug>

//// À ajouter dans le constructeur de MainWindow après l'initialisation de l'UI
//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//    , table(new table_hachage())
//{
//    ui->setupUi(this);
//    setWindowTitle("Gestion Maison - Avec Photos");

//    // Créer un bouton pour afficher les détails
//    QPushButton *detailsButton = new QPushButton("Détails avec Photos", this);

//    // L'ajouter au layout horizontal existant
//    ui->horizontalLayout->addWidget(detailsButton);

//    // Connecter le bouton
//    connect(detailsButton, &QPushButton::clicked, this, &MainWindow::on_detailsButton_clicked);

//    // Améliorer l'affichage du textEdit pour les photos
//    ui->displayTextEdit->setFont(QFont("Consolas", 9)); // Police monospace

//    // Reste du constructeur...
//    if (NotreConnection()) {
//        QMessageBox::information(this, "Connexion", "Connexion à la base de données réussie !");
//        table->charger();
//        on_displayButton_clicked();
//    } else {
//        QMessageBox::critical(this, "Erreur", "Échec de la connexion à la base de données !");
//    }

//    // Connect buttons to slots
//    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
//    connect(ui->getButton, &QPushButton::clicked, this, &MainWindow::on_getButton_clicked);
//    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
//    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::on_displayButton_clicked);
//    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
//    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
//    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

//    // Initialize the hash table
//    table->setHachage_actuelle(1); // Use f1 as default hash function
//}

//MainWindow::~MainWindow()
//{
//    delete table;
//    delete ui;
//}

////void MainWindow::on_addButton_clicked()
////{
////    QString id = ui->idLineEdit->text();
////    QString type = ui->typeLineEdit->text();
////    QString standing = ui->standingLineEdit->text();
////    int chambres = ui->chambresSpinBox->value();
////    int toilettes = ui->toilettesSpinBox->value();
////    QString modele = ui->modeleLineEdit->text();
////    QString description = ui->descriptionTextEdit->toPlainText();
////    QString photosStr = ui->photosLineEdit->text();

////    if (id.isEmpty() || type.isEmpty() || standing.isEmpty() || modele.isEmpty()) {
////        QMessageBox::warning(this, "Erreur de saisie", "Veuillez remplir tous les champs requis (Clé, Type, Standing, Modèle).");
////        return;
////    }

////    QVector<QString> photos;
////    if (!photosStr.isEmpty()) {
////        QStringList photosList = photosStr.split(",");
////        for (const QString &photo : photosList) {
////            photos.append(photo.trimmed());
////        }
////    }

////    VALEUR val = creerVal(type, standing,chambres, toilettes,modele, description, photos);
////    table->inserer(id, val);
////    QMessageBox::information(this, "Succès", "Maison ajoutée avec succès !");
////    clearInputs();
////    on_displayButton_clicked(); // Update display after adding
////}

//void MainWindow::on_getButton_clicked()
//{
//    QString id = ui->idLineEdit->text();
//    if (id.isEmpty()) {
//        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé.");
//        return;
//    }

//    VALEUR val = table->get(id);
//    if (val.type.isEmpty()) {
//        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
//        return;
//    }

//    ui->typeLineEdit->setText(val.type);
//    ui->standingLineEdit->setText(val.standing);
//    ui->modeleLineEdit->setText(val.modele);
//    ui->chambresSpinBox->setValue(val.nombre_de_chambre);
//    ui->toilettesSpinBox->setValue(val.nombre_de_toilettes);
//    ui->photosLineEdit->setText(val.photos.toList().join(", "));
//    ui->descriptionTextEdit->setPlainText(val.description);
//}

//void MainWindow::on_deleteButton_clicked()
//{
//    QString id = ui->idLineEdit->text();
//    if (id.isEmpty()) {
//        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé.");
//        return;
//    }

//    if (table->contient(id)) {
//        table->supprimer(id);
//        QMessageBox::information(this, "Succès", "Maison avec la clé " + id + " supprimée avec succès !");
//        clearInputs();
//        on_displayButton_clicked(); // Update display after deleting
//    } else {
//        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
//    }
//}

//void MainWindow::on_displayButton_clicked()
//{
//    QString output;
//    QTextStream stream(&output);
//    int houseCount = 0;

//    stream << "=== LISTE DES MAISONS ===\n\n";

//    for (int j = 0; j < Nmax; j++) {
//        MAISON *current = table->getMaisonAtIndex(j);
//        while (current) {
//            houseCount++;
//            stream << "🏠 MAISON #" << houseCount << "\n";
//            stream << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
//            stream << "📋 ID : " << current->cle << "\n";
//            stream << "🏘️  Type : " << current->valeur.type << "\n";
//            stream << "⭐ Standing : " << current->valeur.standing << "\n";
//            stream << "🏗️  Modèle : " << current->valeur.modele << "\n";
//            stream << "🛏️  Chambres : " << current->valeur.nombre_de_chambre << "\n";
//            stream << "🚽 Toilettes : " << current->valeur.nombre_de_toilettes << "\n";
//            stream << "📝 Description : " << current->valeur.description << "\n";

//            // Affichage des photos
//            if (current->valeur.photos.isEmpty()) {
//                stream << "📷 Photos : Aucune photo disponible\n";
//            } else {
//                stream << "📷 Photos (" << current->valeur.photos.size() << ") :\n";
//                for (int i = 0; i < current->valeur.photos.size(); ++i) {
//                    stream << "   • " << current->valeur.photos[i] << "\n";
//                }
//            }

//            stream << "\n";
//            current = current->suivant;
//        }
//    }

//    if (houseCount == 0) {
//        stream << "Aucune maison trouvée dans la base de données.\n";
//        stream << "Utilisez le bouton 'Charger' pour récupérer les données.\n";
//    } else {
//        stream << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
//        stream << "📊 Total : " << houseCount << " maison(s) affichée(s)\n";
//    }

//    ui->displayTextEdit->setPlainText(output);
//    qDebug() << "Affichage : " << houseCount << " maison(s) affichée(s)";
//}
//void MainWindow::on_loadButton_clicked()
//{
//    table->charger();
//    QMessageBox::information(this, "Succès", "Données chargées depuis la base de données !");
//    on_displayButton_clicked(); // Ensure display is updated after loading
//}

//void MainWindow::on_saveButton_clicked()
//{
//    table->sauvegarder();
//    QMessageBox::information(this, "Succès", "Données enregistrées dans la base de données !");
//}

//void MainWindow::on_clearButton_clicked()
//{
//    table->vider();
//    QMessageBox::information(this, "Succès", "Tableau de hachage vidé !");
//    ui->displayTextEdit->clear();
//    clearInputs();
//}

//void MainWindow::clearInputs()
//{
//    ui->idLineEdit->clear();
//    ui->typeLineEdit->clear();
//    ui->standingLineEdit->clear();
//    ui->modeleLineEdit->clear();
//    ui->chambresSpinBox->setValue(0);
//    ui->toilettesSpinBox->setValue(0);
//    ui->photosLineEdit->clear();
//    ui->descriptionTextEdit->clear();
//}
//void MainWindow::on_detailsButton_clicked()
//{
//    QString id = ui->idLineEdit->text();
//    if (id.isEmpty()) {
//        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé pour afficher les détails.");
//        return;
//    }

//    if (!table->contient(id)) {
//        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
//        return;
//    }

//    VALEUR val = table->get(id);

//    QString details;
//    QTextStream stream(&details);

//    stream << "🏠 DÉTAILS DE LA MAISON\n";
//    stream << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
//    stream << "📋 Identifiant : " << id << "\n";
//    stream << "🏘️  Type : " << val.type << "\n";
//    stream << "⭐ Standing : " << val.standing << "\n";
//    stream << "🏗️  Modèle : " << val.modele << "\n";
//    stream << "🛏️  Nombre de chambres : " << val.nombre_de_chambre << "\n";
//    stream << "🚽 Nombre de toilettes : " << val.nombre_de_toilettes << "\n\n";

//    stream << "📝 DESCRIPTION :\n";
//    stream << "─────────────────────────────────────────\n";
//    stream << val.description << "\n\n";

//    stream << "📷 PHOTOS :\n";
//    stream << "─────────────────────────────────────────\n";
//    if (val.photos.isEmpty()) {
//        stream << "❌ Aucune photo disponible pour cette maison.\n";
//    } else {
//        stream << "✅ " << val.photos.size() << " photo(s) disponible(s) :\n\n";
//        for (int i = 0; i < val.photos.size(); ++i) {
//            stream << QString("📸 Photo %1 : %2\n").arg(i + 1).arg(val.photos[i]);
//        }

//        stream << "\n💡 Les photos sont stockées dans le dossier 'images/' de votre application.\n";
//        stream << "   Chemin complet des photos :\n";
//        for (const QString& photo : val.photos) {
//            stream << "   → images/" << photo << "\n";
//        }
//    }

//    // Afficher dans une boîte de dialogue ou dans le textEdit
//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Détails de la maison - " + id);
//    msgBox.setText(details);
//    msgBox.setStandardButtons(QMessageBox::Ok);
//    msgBox.setIcon(QMessageBox::Information);
//    msgBox.exec();
//}
//bool MainWindow::validatePhotos(const QVector<QString>& photos, QString& missingFiles)
//{
//    bool allExist = true;
//    QStringList missing;

//    for (const QString& photo : photos) {
//        QString fullPath = QDir::currentPath() + "/images/" + photo;
//        QFileInfo fileInfo(fullPath);

//        if (!fileInfo.exists()) {
//            missing.append(photo);
//            allExist = false;
//        }
//    }

//    if (!allExist) {
//        missingFiles = missing.join(", ");
//    }

//    return allExist;
//}

//// Modification de la méthode on_addButton_clicked pour valider les photos
//void MainWindow::on_addButton_clicked()
//{
//    QString id = ui->idLineEdit->text();
//    QString type = ui->typeLineEdit->text();
//    QString standing = ui->standingLineEdit->text();
//    int chambres = ui->chambresSpinBox->value();
//    int toilettes = ui->toilettesSpinBox->value();
//    QString modele = ui->modeleLineEdit->text();
//    QString description = ui->descriptionTextEdit->toPlainText();
//    QString photosStr = ui->photosLineEdit->text();

//    if (id.isEmpty() || type.isEmpty() || standing.isEmpty() || modele.isEmpty()) {
//        QMessageBox::warning(this, "Erreur de saisie",
//                           "Veuillez remplir tous les champs requis (Clé, Type, Standing, Modèle).");
//        return;
//    }

//    QVector<QString> photos;
//    if (!photosStr.isEmpty()) {
//        QStringList photosList = photosStr.split(",");
//        for (const QString &photo : photosList) {
//            QString trimmedPhoto = photo.trimmed();
//            if (!trimmedPhoto.isEmpty()) {
//                photos.append(trimmedPhoto);
//            }
//        }

//        // Valider que les photos existent
//        QString missingFiles;
//        if (!validatePhotos(photos, missingFiles)) {
//            QMessageBox::StandardButton reply;
//            reply = QMessageBox::question(this, "Photos manquantes",
//                                        QString("Les photos suivantes n'existent pas :\n%1\n\n"
//                                               "Voulez-vous continuer sans ces photos ?")
//                                        .arg(missingFiles),
//                                        QMessageBox::Yes | QMessageBox::No);
//            if (reply == QMessageBox::No) {
//                return;
//            }
//        }
//    }

//    VALEUR val = creerVal(type, standing, chambres, toilettes, modele, description, photos);
//    table->inserer(id, val);
//    QMessageBox::information(this, "Succès", "Maison ajoutée avec succès !");
//    clearInputs();
//    on_displayButton_clicked();
//}
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeConnecter.h"
#include <QMessageBox>
#include <QDebug>
#include <QFontDatabase>

// Constructeur de MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , table(new table_hachage())
{
    ui->setupUi(this);
    setWindowTitle("Gestion Maison - Avec Photos");

    // Créer un bouton pour afficher les détails
    QPushButton *detailsButton = new QPushButton("Détails avec Photos", this);

    // L'ajouter au layout horizontal existant
    ui->horizontalLayout->addWidget(detailsButton);

    // Connecter le bouton
    connect(detailsButton, &QPushButton::clicked, this, &MainWindow::on_detailsButton_clicked);

    // Utiliser une police qui prend en charge les emojis
    QFont font = QFontDatabase().font("Segoe UI", "Regular", 10);
    if (!font.exactMatch()) {
        font = QFont("Arial", 10); // Fallback vers Arial si Segoe UI n'est pas disponible
    }
    ui->displayTextEdit->setFont(font);

    // Vérifier la connexion à la base de données
    if (NotreConnection()) {
        QMessageBox::information(this, "Connexion", "Connexion à la base de données réussie !");
        table->charger();
        on_displayButton_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la connexion à la base de données !");
    }

    // Connecter les boutons aux slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->getButton, &QPushButton::clicked, this, &MainWindow::on_getButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::on_displayButton_clicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

    // Initialiser la table de hachage
    table->setHachage_actuelle(1); // Utiliser f1 comme fonction de hachage par défaut
}

MainWindow::~MainWindow()
{
    delete table;
    delete ui;
}

void MainWindow::on_getButton_clicked()
{
    QString id = ui->idLineEdit->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé.");
        return;
    }

    VALEUR val = table->get(id);
    if (val.type.isEmpty()) {
        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
        return;
    }

    ui->typeLineEdit->setText(val.type);
    ui->standingLineEdit->setText(val.standing);
    ui->modeleLineEdit->setText(val.modele);
    ui->chambresSpinBox->setValue(val.nombre_de_chambre);
    ui->toilettesSpinBox->setValue(val.nombre_de_toilettes);
    ui->photosLineEdit->setText(val.photos.toList().join(", "));
    ui->descriptionTextEdit->setPlainText(val.description);
}

void MainWindow::on_deleteButton_clicked()
{
    QString id = ui->idLineEdit->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé.");
        return;
    }

    if (table->contient(id)) {
        table->supprimer(id);
        QMessageBox::information(this, "Succès", "Maison avec la clé " + id + " supprimée avec succès !");
        clearInputs();
        on_displayButton_clicked(); // Mettre à jour l'affichage après suppression
    } else {
        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
    }
}

void MainWindow::on_displayButton_clicked()
{
    QString output;
    QTextStream stream(&output);
    int houseCount = 0;

    stream.setCodec("UTF-8"); // Assurer l'encodage UTF-8 pour les caractères spéciaux
    stream << "=== LISTE DES MAISONS ===\n\n";

    for (int j = 0; j < Nmax; j++) {
        MAISON *current = table->getMaisonAtIndex(j);
        while (current) {
            houseCount++;
            stream << "Maison #" << houseCount << "\n"; // Remplacer emoji 🏠
            stream << "----------------------------------------\n";
            stream << "ID : " << current->cle << "\n";
            stream << "Type : " << current->valeur.type << "\n";
            stream << "Standing : " << current->valeur.standing << "\n";
            stream << "Modèle : " << current->valeur.modele << "\n";
            stream << "Chambres : " << current->valeur.nombre_de_chambre << "\n";
            stream << "Toilettes : " << current->valeur.nombre_de_toilettes << "\n";
            stream << "Description : " << current->valeur.description << "\n";

            // Affichage des photos
            if (current->valeur.photos.isEmpty()) {
                stream << "Photos : Aucune photo disponible\n";
            } else {
                stream << "Photos (" << current->valeur.photos.size() << ") :\n";
                for (int i = 0; i < current->valeur.photos.size(); ++i) {
                    stream << "   - " << current->valeur.photos[i] << "\n";
                }
            }

            stream << "\n";
            current = current->suivant;
        }
    }

    if (houseCount == 0) {
        stream << "Aucune maison trouvée dans la base de données.\n";
        stream << "Utilisez le bouton 'Charger' pour récupérer les données.\n";
    } else {
        stream << "----------------------------------------\n";
        stream << "Total : " << houseCount << " maison(s) affichée(s)\n";
    }

    ui->displayTextEdit->setPlainText(output);
    qDebug() << "Affichage : " << houseCount << " maison(s) affichée(s)";
}

void MainWindow::on_loadButton_clicked()
{
    table->charger();
    QMessageBox::information(this, "Succès", "Données chargées depuis la base de données !");
    on_displayButton_clicked(); // Mettre à jour l'affichage après chargement
}

void MainWindow::on_saveButton_clicked()
{
    table->sauvegarder();
    QMessageBox::information(this, "Succès", "Données enregistrées dans la base de données !");
}

void MainWindow::on_clearButton_clicked()
{
    table->vider();
    QMessageBox::information(this, "Succès", "Tableau de hachage vidé !");
    ui->displayTextEdit->clear();
    clearInputs();
}

void MainWindow::on_detailsButton_clicked()
{
    QString id = ui->idLineEdit->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une clé pour afficher les détails.");
        return;
    }

    if (!table->contient(id)) {
        QMessageBox::information(this, "Non trouvé", "Aucune maison trouvée avec la clé : " + id);
        return;
    }

    VALEUR val = table->get(id);

    QString details;
    QTextStream stream(&details);
    stream.setCodec("UTF-8"); // Assurer l'encodage UTF-8 pour les caractères spéciaux

    stream << "DÉTAILS DE LA MAISON\n";
    stream << "----------------------------------------\n";
    stream << "Identifiant : " << id << "\n";
    stream << "Type : " << val.type << "\n";
    stream << "Standing : " << val.standing << "\n";
    stream << "Modèle : " << val.modele << "\n";
    stream << "Nombre de chambres : " << val.nombre_de_chambre << "\n";
    stream << "Nombre de toilettes : " << val.nombre_de_toilettes << "\n\n";

    stream << "DESCRIPTION :\n";
    stream << "----------------------------------------\n";
    stream << val.description << "\n\n";

    stream << "PHOTOS :\n";
    stream << "----------------------------------------\n";
    if (val.photos.isEmpty()) {
        stream << "Aucune photo disponible pour cette maison.\n";
    } else {
        stream << val.photos.size() << " photo(s) disponible(s) :\n\n";
        for (int i = 0; i < val.photos.size(); ++i) {
            stream << QString("Photo %1 : %2\n").arg(i + 1).arg(val.photos[i]);
        }

        stream << "\nLes photos sont stockées dans le dossier 'images/' de votre application.\n";
        stream << "Chemin complet des photos :\n";
        for (const QString& photo : val.photos) {
            stream << "   - images/" << photo << "\n";
        }
    }

    // Afficher dans une boîte de dialogue
    QMessageBox msgBox;
    msgBox.setWindowTitle("Détails de la maison - " + id);
    msgBox.setText(details);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

bool MainWindow::validatePhotos(const QVector<QString>& photos, QString& missingFiles)
{
    bool allExist = true;
    QStringList missing;

    for (const QString& photo : photos) {
        QString fullPath = QDir::currentPath() + "/images/" + photo;
        QFileInfo fileInfo(fullPath);

        if (!fileInfo.exists()) {
            missing.append(photo);
            allExist = false;
        }
    }

    if (!allExist) {
        missingFiles = missing.join(", ");
    }

    return allExist;
}

void MainWindow::on_addButton_clicked()
{
    QString id = ui->idLineEdit->text();
    QString type = ui->typeLineEdit->text();
    QString standing = ui->standingLineEdit->text();
    int chambres = ui->chambresSpinBox->value();
    int toilettes = ui->toilettesSpinBox->value();
    QString modele = ui->modeleLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    QString photosStr = ui->photosLineEdit->text();

    if (id.isEmpty() || type.isEmpty() || standing.isEmpty() || modele.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie",
                           "Veuillez remplir tous les champs requis (Clé, Type, Standing, Modèle).");
        return;
    }

    QVector<QString> photos;
    if (!photosStr.isEmpty()) {
        QStringList photosList = photosStr.split(",");
        for (const QString &photo : photosList) {
            QString trimmedPhoto = photo.trimmed();
            if (!trimmedPhoto.isEmpty()) {
                photos.append(trimmedPhoto);
            }
        }

        // Valider que les photos existent
        QString missingFiles;
        if (!validatePhotos(photos, missingFiles)) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Photos manquantes",
                                        QString("Les photos suivantes n'existent pas :\n%1\n\n"
                                               "Voulez-vous continuer sans ces photos ?")
                                        .arg(missingFiles),
                                        QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No) {
                return;
            }
        }
    }

    VALEUR val = creerVal(type, standing, chambres, toilettes, modele, description, photos);
    table->inserer(id, val);
    QMessageBox::information(this, "Succès", "Maison ajoutée avec succès !");
    clearInputs();
    on_displayButton_clicked();
}

void MainWindow::clearInputs()
{
    ui->idLineEdit->clear();
    ui->typeLineEdit->clear();
    ui->standingLineEdit->clear();
    ui->modeleLineEdit->clear();
    ui->chambresSpinBox->setValue(0);
    ui->toilettesSpinBox->setValue(0);
    ui->photosLineEdit->clear();
    ui->descriptionTextEdit->clear();
}
