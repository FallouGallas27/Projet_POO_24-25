
#include "table_hachage.h"
#include <QMessageBox>
#include <QtSql>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#define Nmax 535
table_hachage::table_hachage()
{
    maisons = new MAISON *[Nmax];
    nbr_de_maison = 0;
    hachage_actuelle = 1;
    for (int i = 0; i < Nmax; i++) {
        maisons[i] = nullptr;
    }
}

table_hachage::~table_hachage()
{
    if (maisons) {
        for (int i = 0; i < Nmax; i++) {
            if (maisons[i]) {
                MAISON *tmp = maisons[i];
                while (tmp) {
                    maisons[i] = maisons[i]->suivant;
                    delete tmp;
                    tmp = maisons[i];
                }
            }
        }
        delete[] maisons;
    }
}

void table_hachage::charger()
{
    this->hachage_actuelle = 1;
    if (QSqlDatabase::contains("ma_connexion_temporaire")) {
        QSqlDatabase::removeDatabase("ma_connexion_temporaire");
    }
    QSqlDatabase mysdb1 = QSqlDatabase::database("gestion_maison");
    if (!mysdb1.isOpen()) {
        if (!mysdb1.open()) {
            qDebug() << "Échec de la connexion : " << mysdb1.lastError().text();
            return;
        }
    }

    QSqlQuery query(mysdb1);

    // Requête pour récupérer les maisons avec leurs photos
    query.prepare("SELECT m.id, m.type, m.standing, m.nombre_de_chambre, "
                  "m.nombre_de_toilettes, m.modele, m.description, "
                  "GROUP_CONCAT(p.nom_fichier SEPARATOR ',') as photos "
                  "FROM maisons m "
                  "LEFT JOIN photos p ON m.id = p.maison_id "
                  "GROUP BY m.id, m.type, m.standing, m.nombre_de_chambre, "
                  "m.nombre_de_toilettes, m.modele, m.description");

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
        return;
    }

    while (query.next())
    {
        QString maisonId = query.value(0).toString();
        if (!contient(maisonId))
        {
            QVector<QString> photos;
            QString photosStr = query.value(7).toString(); // Colonne photos concaténées

            if (!photosStr.isEmpty() && photosStr != "NULL") {
                QStringList photosList = photosStr.split(",");
                for (const QString &photo : photosList) {
                    QString photoTrimmed = photo.trimmed();
                    if (!photoTrimmed.isEmpty()) {
                        photos.append(photoTrimmed);
                    }
                }
            }

            VALEUR V = creerVal(query.value(1).toString(),    // type
                                query.value(2).toString(),    // standing
                                query.value(3).toInt(),       // nombre_de_chambre
                                query.value(4).toInt(),       // nombre_de_toilettes
                                query.value(5).toString(),    // modele
                                query.value(6).toString(),    // description
                                photos);                      // photos

            qDebug() << "Chargement - Clé :" << maisonId << "Photos :" << photos.size();
            inserer(maisonId, V);
        }
    }

    mysdb1.close();
}
void table_hachage::sauvegarder()
{
    if (QSqlDatabase::contains("gestion_maison")) {
        QSqlDatabase::removeDatabase("gestion_maison");
    }
    QSqlDatabase mysdb1 = QSqlDatabase::addDatabase("QMYSQL", "ma_connexion_temporaire");
    mysdb1.setHostName("127.0.0.1");
    mysdb1.setDatabaseName("gestion_maison");
    mysdb1.setUserName("root");
    mysdb1.setPassword("gallas27");
    mysdb1.setPort(3306);

    if (!mysdb1.open()) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                             "Échec de la connexion à la base de données : " + mysdb1.lastError().text());
        return;
    }

    QSqlQuery query(mysdb1);

    // Commencer une transaction
    mysdb1.transaction();

    try {
        // Vider les tables existantes
        if (!query.exec("DELETE FROM photos")) {
            throw std::runtime_error("Erreur lors de la suppression des photos");
        }
        if (!query.exec("DELETE FROM maisons")) {
            throw std::runtime_error("Erreur lors de la suppression des maisons");
        }

        // Préparer la requête d'insertion pour les maisons
        query.prepare("INSERT INTO maisons (id, type, standing, nombre_de_chambre, "
                     "nombre_de_toilettes, modele, description) "
                     "VALUES (:id, :type, :standing, :nombre_de_chambre, "
                     ":nombre_de_toilettes, :modele, :description)");

        // Insérer les maisons
        for (int i = 0; i < Nmax; i++) {
            MAISON *current = maisons[i];
            while (current) {
                const QString& identifiant = current->cle;
                const VALEUR& valeur = current->valeur;

                query.bindValue(":id", identifiant);
                query.bindValue(":type", valeur.type);
                query.bindValue(":standing", valeur.standing);
                query.bindValue(":nombre_de_chambre", valeur.nombre_de_chambre);
                query.bindValue(":nombre_de_toilettes", valeur.nombre_de_toilettes);
                query.bindValue(":modele", valeur.modele);
                query.bindValue(":description", valeur.description);

                if (!query.exec()) {
                    throw std::runtime_error("Erreur lors de l'insertion d'une maison");
                }

                current = current->suivant;
            }
        }

        // Préparer la requête d'insertion pour les photos
        query.prepare("INSERT INTO photos (maison_id, nom_fichier) VALUES (:maison_id, :nom_fichier)");

        // Insérer les photos
        for (int i = 0; i < Nmax; i++) {
            MAISON *current = maisons[i];
            while (current) {
                const QString& identifiant = current->cle;
                const VALEUR& valeur = current->valeur;

                // Insérer chaque photo individuellement
                for (const QString& photo : valeur.photos) {
                    if (!photo.isEmpty()) {
                        query.bindValue(":maison_id", identifiant);
                        query.bindValue(":nom_fichier", photo);

                        if (!query.exec()) {
                            throw std::runtime_error("Erreur lors de l'insertion d'une photo");
                        }
                    }
                }

                current = current->suivant;
            }
        }

        // Confirmer la transaction
        mysdb1.commit();
        QMessageBox::information(nullptr, "Succès", "Données sauvegardées avec succès !");

    } catch (const std::exception& e) {
        // Annuler la transaction en cas d'erreur
        mysdb1.rollback();
        QMessageBox::critical(nullptr, "Erreur de sauvegarde",
                             QString("Erreur lors de la sauvegarde : %1").arg(e.what()));
    }

    mysdb1.close();
}
void table_hachage::inserer(QString cle, VALEUR val)
{
    int valeur_hachage ;

    switch (hachage_actuelle) {
    case 1:
        valeur_hachage = f1(cle);
        break;
    case 2:
        valeur_hachage = f2(cle);
        break;
    case 3:
        valeur_hachage = f3(cle);
        break;
    default:
        valeur_hachage = f4();
        break;
    }

    if (!contient(cle)) {
        MAISON *nouvelle_maison = new MAISON;
        nouvelle_maison->cle = cle;
        nouvelle_maison->valeur.type = val.type;
        nouvelle_maison->valeur.standing = val.standing;
        nouvelle_maison->valeur.modele = val.modele;
        nouvelle_maison->valeur.nombre_de_chambre = val.nombre_de_chambre;
        nouvelle_maison->valeur.nombre_de_toilettes = val.nombre_de_toilettes;
        nouvelle_maison->valeur.photos = val.photos;
        nouvelle_maison->valeur.description = val.description;
        nouvelle_maison->suivant = nullptr;

        if (!maisons[valeur_hachage]) {
            maisons[valeur_hachage] = nouvelle_maison;
        } else {
            nouvelle_maison->suivant = maisons[valeur_hachage];
            maisons[valeur_hachage] = nouvelle_maison;
        }

        nbr_de_maison++;
    }
}

VALEUR table_hachage::get(QString cle)
{
    int valeur_hachage;

    switch (hachage_actuelle) {
    case 1:
        valeur_hachage = f1(cle);
        break;
    case 2:
        valeur_hachage = f2(cle);
        break;
    case 3:
        valeur_hachage = f3(cle);
        break;
    default:
        for (int i = 0; i < Nmax; i++) {
            MAISON *tmp = maisons[i];
            while (tmp) {
                if (tmp->cle == cle) {
                    return tmp->valeur;
                }
                tmp = tmp->suivant;
            }
        }
        return VALEUR();
    }

    MAISON *tmp = maisons[valeur_hachage];
    while (tmp) {
        if (tmp->cle == cle) {
            return tmp->valeur;
        }
        tmp = tmp->suivant;
    }

    return VALEUR();
}

void table_hachage::supprimer(QString cle)
{
    int valeur_hachage;

    switch (hachage_actuelle) {
    case 1:
        valeur_hachage = f1(cle);
        break;
    case 2:
        valeur_hachage = f2(cle);
        break;
    case 3:
        valeur_hachage = f3(cle);
        break;
    default:
        valeur_hachage = f4();
        break;
    }

    if (maisons[valeur_hachage]) {
        if (maisons[valeur_hachage]->cle == cle) {
            MAISON *tmp = maisons[valeur_hachage];
            maisons[valeur_hachage] = maisons[valeur_hachage]->suivant;
            delete tmp;
            nbr_de_maison--;
            return;
        } else {
            MAISON *precedent = maisons[valeur_hachage];
            MAISON *courant = maisons[valeur_hachage]->suivant;

            while (courant && courant->cle != cle) {
                precedent = courant;
                courant = courant->suivant;
            }

            if (courant) {
                precedent->suivant = courant->suivant;
                delete courant;
                nbr_de_maison--;
            }
        }
    }
}

bool table_hachage::contient(QString cle)
{
    int valeur_hachage;

    switch (hachage_actuelle) {
    case 1:
        valeur_hachage = f1(cle);
        break;
    case 2:
        valeur_hachage = f2(cle);
        break;
    case 3:
        valeur_hachage = f3(cle);
        break;
    default:
        for (int i = 0; i < Nmax; i++) {
            MAISON *tmp = maisons[i];
            while (tmp) {
                if (tmp->cle == cle) {
                    return true;
                }
                tmp = tmp->suivant;
            }
        }
        return false;
    }

    MAISON *tmp = maisons[valeur_hachage];
    while (tmp) {
        if (tmp->cle == cle) {
            return true;
        }
        tmp = tmp->suivant;
    }

    return false;
}

int table_hachage::size()
{
    return nbr_de_maison;
}

bool table_hachage::Est_vide()
{
    int i = 0;
    while (i < Nmax) {
        if (maisons[i]) {
            break;
        }
        i++;
    }
    if (i == Nmax) {
        return true;
    } else {
        return false;
    }
}

int table_hachage::f1(QString str)
{
    unsigned int hash = 0;
    for (QChar c : str) {
        hash = hash * 17 + c.unicode();
    }
    return hash % Nmax;
}

unsigned long table_hachage::f2(QString& str)
{
    unsigned long hash = 5381;
    for (QChar c : str) {
        hash = ((hash << 5) + hash) + c.unicode();
    }
    return hash % Nmax;
}

unsigned long table_hachage::f3(QString str)
{
    unsigned long hash = 0;
    unsigned long prime1 = 16777619;
    unsigned long prime2 = 2166136261;

    for (int i = 0; i < str.length(); i++) {
        QChar c = str[i];
        hash ^= c.unicode();
        hash *= prime1;
        hash += (hash << 13) | (hash >> 19);
        hash ^= (hash << 7) | (hash >> 25);
        hash *= prime2;
        hash ^= (hash << 3);
        hash += (hash >> 5);
        hash ^= (hash << 4);
        hash += (hash >> 17);
        hash ^= (hash << 25);
        hash += (hash >> 6);
    }

    return hash % Nmax;
}

int table_hachage::f4()
{
    for (int i = 0; i < Nmax; i++) {
        if (maisons[i] == nullptr) {
            return i;
        }
    }
    return -1;
}

VALEUR creerVal(QString type, QString standing,  int chambres, int toilettes,QString modele, QString description, QVector<QString> photos)
{
    VALEUR v;
    v.type = type;
    v.standing = standing;
    v.modele = modele;
    v.nombre_de_chambre = chambres;
    v.nombre_de_toilettes = toilettes;
    v.photos = photos;
    v.description = description;
    return v;
}

void table_hachage::setHachage_actuelle(int hash)
{
    hachage_actuelle = hash;
}

int table_hachage::getHachage_actuelle()
{
    return hachage_actuelle;
}

void table_hachage::vider()
{
    if (maisons) {
        for (int i = 0; i < Nmax; i++) {
            if (maisons[i]) {
                MAISON *tmp = maisons[i];
                MAISON *suiv = maisons[i];
                while (suiv) {
                    tmp = suiv;
                    suiv = suiv->suivant;
                    delete tmp;
                }
                maisons[i] = nullptr;
            }
        }
        delete[] maisons;
    }
    maisons = new MAISON *[Nmax];
    nbr_de_maison = 0;
    hachage_actuelle = 3;
    for (int i = 0; i < Nmax; i++) {
        maisons[i] = nullptr;
    }
}

void table_hachage::affiche()
{
    for (int i = 0; i < Nmax; i++) {
        MAISON *current = maisons[i];
        while (current) {
            qDebug() << "Clé :" << current->cle;
            qDebug() << "Type :" << current->valeur.type;
            qDebug() << "Standing :" << current->valeur.standing;
            qDebug() << "Nombre de chambres :" << current->valeur.nombre_de_chambre;
            qDebug() << "Nombre de toilettes :" << current->valeur.nombre_de_toilettes;
            qDebug() << "Modèle :" << current->valeur.modele;
            qDebug() << "Description :" << current->valeur.description;
            qDebug() << "Nombre de photos :" << current->valeur.photos.size();
            qDebug() << "-----------------------------------";
            current = current->suivant;
        }
    }
}

MAISON* table_hachage::getMaisonAtIndex(int index)
{
    if (index >= 0 && index < Nmax) {
        return maisons[index];
    }
    return nullptr;
}

