#include "DisplayHouseDialog.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

DisplayHouseDialog::DisplayHouseDialog(table_hachage* table, QWidget *parent)
    : QDialog(parent), tableHachage(table)
{
    setWindowTitle("Liste des maisons");
    resize(800, 600);
    setupUI();
}

void DisplayHouseDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* scrollWidget = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

    // Afficher toutes les maisons
    for (int i = 0; i < 535; i++) {
        MAISON* maison = tableHachage->getMaisonAtIndex(i);
        while (maison) {
            displayHouseInfo(maison, scrollLayout); // Passer le scrollLayout
            maison = maison->suivant;
        }
    }

    // Ajouter un espacement à la fin
    scrollLayout->addStretch();

    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    QPushButton* closeButton = new QPushButton("Fermer", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeButton);

    setLayout(mainLayout);
}

void DisplayHouseDialog::displayHouseInfo(MAISON* maison, QVBoxLayout* parentLayout)
{
    QWidget* houseWidget = new QWidget();
    QVBoxLayout* houseLayout = new QVBoxLayout(houseWidget);

    // Informations de la maison
    QLabel* idLabel = new QLabel(QString("ID: %1").arg(maison->cle));
    QLabel* typeLabel = new QLabel(QString("Type: %1").arg(maison->valeur.type));
    QLabel* standingLabel = new QLabel(QString("Standing: %1").arg(maison->valeur.standing));
    QLabel* modelLabel = new QLabel(QString("Modèle: %1").arg(maison->valeur.modele));
    QLabel* roomsLabel = new QLabel(QString("Chambres: %1").arg(maison->valeur.nombre_de_chambre));
    QLabel* bathroomsLabel = new QLabel(QString("Toilettes: %1").arg(maison->valeur.nombre_de_toilettes));
    QLabel* descLabel = new QLabel(QString("Description: %1").arg(maison->valeur.description));

    // Style pour les labels
    QString labelStyle = "QLabel { font-weight: bold; margin: 2px; }";
    idLabel->setStyleSheet(labelStyle);
    typeLabel->setStyleSheet(labelStyle);
    standingLabel->setStyleSheet(labelStyle);
    modelLabel->setStyleSheet(labelStyle);
    roomsLabel->setStyleSheet(labelStyle);
    bathroomsLabel->setStyleSheet(labelStyle);
    descLabel->setStyleSheet(labelStyle);
    descLabel->setWordWrap(true); // Permettre le retour à la ligne pour la description

    houseLayout->addWidget(idLabel);
    houseLayout->addWidget(typeLabel);
    houseLayout->addWidget(standingLabel);
    houseLayout->addWidget(modelLabel);
    houseLayout->addWidget(roomsLabel);
    houseLayout->addWidget(bathroomsLabel);
    houseLayout->addWidget(descLabel);

    // Afficher les images
    if (!maison->valeur.photos.isEmpty()) {
        QHBoxLayout* imagesLayout = new QHBoxLayout();
        int imageCount = 0;
        const int maxImages = 3; // Limiter le nombre d'images affichées

        for (const QString& photoPath : maison->valeur.photos) {
            if (imageCount >= maxImages) break;

            QLabel* imageLabel = new QLabel();
            imageLabel->setFixedSize(100, 100);
            imageLabel->setScaledContents(true);
            imageLabel->setStyleSheet("border: 1px solid gray;");

            QPixmap pixmap(photoPath);
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                imageLabel->setText("Image\nnon trouvée");
                imageLabel->setAlignment(Qt::AlignCenter);
                imageLabel->setStyleSheet("border: 1px solid gray; color: red;");
            }
            imagesLayout->addWidget(imageLabel);
            imageCount++;
        }

        if (maison->valeur.photos.size() > maxImages) {
            QLabel* moreLabel = new QLabel(QString("+%1 autres").arg(maison->valeur.photos.size() - maxImages));
            moreLabel->setAlignment(Qt::AlignCenter);
            moreLabel->setStyleSheet("color: blue; font-style: italic;");
            imagesLayout->addWidget(moreLabel);
        }

        imagesLayout->addStretch();
        houseLayout->addLayout(imagesLayout);
    }

    // Style pour le widget de la maison
    houseWidget->setStyleSheet("QWidget { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 10px; margin: 5px; }");
    houseWidget->setLayout(houseLayout);

    // Ajouter au layout parent (scrollLayout)
    parentLayout->addWidget(houseWidget);

    // Ajouter un séparateur
    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("color: #ccc;");
    parentLayout->addWidget(separator);
}
