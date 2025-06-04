
#ifndef TABLE_HACHAGE_H
#define TABLE_HACHAGE_H

#include <QString>
#include <QVector>

#define Nmax 535

struct VALEUR {
    QString type;
    QString standing;
    QString modele;
    int nombre_de_chambre;
    int nombre_de_toilettes;
    QVector<QString> photos;
    QString description;
};

struct MAISON {
    QString cle;
    VALEUR valeur;
    MAISON *suivant;
};

class table_hachage
{
private:
    MAISON **maisons;
    int hachage_actuelle;
    int nbr_de_maison;

public:
    table_hachage();
    ~table_hachage();
    void inserer(QString cle, VALEUR val);
    VALEUR get(QString cle);
    void supprimer(QString cle);
    bool contient(QString cle);
    int size();
    bool Est_vide();
    void vider();
    void affiche();
    MAISON* getMaisonAtIndex(int index);
    void charger();
    void sauvegarder();
    void setHachage_actuelle(int hash);
    int getHachage_actuelle();

private:
    int f1(QString str);
    unsigned long f2(QString& str);
    unsigned long f3(QString str);
    int f4();
};

VALEUR creerVal(QString type, QString standing,  int chambres, int toilettes,QString modele, QString description, QVector<QString> photos);

#endif // TABLE_HACHAGE_H
