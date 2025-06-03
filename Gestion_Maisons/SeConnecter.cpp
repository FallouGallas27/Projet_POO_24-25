#include "SeConnecter.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

bool NotreConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "gestion_maison");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("gestion_maison");
    db.setUserName("root");
    db.setPassword("gallas27");
    db.setPort(3306);
    if (!db.open()) {
        qDebug() << "Échec de la connexion à la base de données :" << db.lastError().text();
        return false;
    }
    return true;
}
