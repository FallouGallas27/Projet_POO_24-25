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

    // Display all houses
    for (int i = 0; i < 535; i++) {
        MAISON* maison = tableHachage->getMaisonAtIndex(i);
        while (maison) {
            displayHouseInfo(maison);
            maison = maison->suivant;
        }
    }

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    QPushButton* closeButton = new QPushButton("Fermer", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeButton);

    setLayout(mainLayout);
}

void DisplayHouseDialog::displayHouseInfo(MAISON* maison)
{
    QWidget* houseWidget = new QWidget();
    QVBoxLayout* houseLayout = new QVBoxLayout(houseWidget);

    // House information
    QLabel* idLabel = new QLabel(QString("ID: %1").arg(maison->cle));
    QLabel* typeLabel = new QLabel(QString("Type: %1").arg(maison->valeur.type));
    QLabel* standingLabel = new QLabel(QString("Standing: %1").arg(maison->valeur.standing));
    QLabel* modelLabel = new QLabel(QString("Modèle: %1").arg(maison->valeur.modele));
    QLabel* roomsLabel = new QLabel(QString("Chambres: %1").arg(maison->valeur.nombre_de_chambre));
    QLabel* bathroomsLabel = new QLabel(QString("Toilettes: %1").arg(maison->valeur.nombre_de_toilettes));
    QLabel* descLabel = new QLabel(QString("Description: %1").arg(maison->valeur.description));

    houseLayout->addWidget(idLabel);
    houseLayout->addWidget(typeLabel);
    houseLayout->addWidget(standingLabel);
    houseLayout->addWidget(modelLabel);
    houseLayout->addWidget(roomsLabel);
    houseLayout->addWidget(bathroomsLabel);
    houseLayout->addWidget(descLabel);

    // Display images
    if (!maison->valeur.photos.isEmpty()) {
        QHBoxLayout* imagesLayout = new QHBoxLayout();
        for (const QString& photoPath : maison->valeur.photos) {
            QLabel* imageLabel = new QLabel();
            QPixmap pixmap(photoPath);
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
            } else {
                imageLabel->setText("Image non trouvée");
            }
            imagesLayout->addWidget(imageLabel);
        }
        houseLayout->addLayout(imagesLayout);
    }

    houseLayout->addStretch();
    mainLayout->addWidget(houseWidget);

    // Add separator
    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(separator);
}
