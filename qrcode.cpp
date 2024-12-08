#include "qrcode.h"
#include "ui_qrcode.h"
#include <QWidget>
#include <QLabel>
#include <QProcess>
#include <QPixmap>
#include <QDialog>
#include <QMessageBox>
#include <QFile>

qrcode::qrcode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qrcode)
{
    ui->setupUi(this);
    ui->tableView->setVisible(false);
        connect(ui->envoi_2, &QPushButton::clicked, this, &qrcode::generateQRCode);
        connect(ui->cancel, &QPushButton::clicked, this, &qrcode::close);
        connect(ui->envoi3, &QPushButton::clicked, this, [this]() {
            if (ui->tableView->isVisible()) {
                ui->tableView->setVisible(false);
            } else {
                ui->tableView->setModel(ES.afficher());
                ui->tableView->setVisible(true);
            }
        });
}

qrcode::~qrcode()
{
    delete ui;
}
void qrcode::generateQRCode() {
    int productId = ui->lineEditId->text().toInt();  // Id provenant d'un QLineEdit, par exemple

    // Vérifiez si l'ID existe en utilisant la méthode verifierID
    produit prod;  // Créez une instance de la classe produit
    if (!prod.verifierID(productId)) {
        QMessageBox::warning(this, "Erreur", "Le produit avec cet ID n'existe pas.");
        return;
    }

    // Si l'ID existe, générer le QR Code
    QString qrData = "Produit ID: " + QString::number(productId);

    // Récupérer les informations du produit depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT NOMT, PRIXT, IDT FROM PRODUIT WHERE IDT = :idt");
    query.bindValue(":idt", productId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la récupération des informations du produit.");
        return;
    }

    if (query.next()) {
        QString productName = query.value(0).toString();
        float productPrice = query.value(1).toFloat();
        QString productid = query.value(2).toString();

        // Créer le texte à encoder dans le QR code
        qrData = "Nom: " + productName + "\nPrix: " + QString::number(productPrice) + "\nID: " + productid;

        // Spécifier le chemin de sauvegarde du QR code
        QString outputPath = "C:/firqs/canpark/qrcanbark/code_qr_produit_" + QString::number(productId) + ".png";

        // Créer un objet QProcess pour exécuter le script Python
        QProcess process;
        QString pythonPath = "python";  // Assurez-vous que 'python' est dans votre PATH
        QString scriptPath = "C:/firqs/import qrcode.py";  // Chemin vers le script Python

        // Argument pour exécuter le script avec les données et le chemin de sortie
        QStringList arguments;
        arguments << scriptPath << qrData << outputPath;

        // Démarrer le processus Python
        process.start(pythonPath, arguments);

        // Vérifier si le processus a démarré correctement
        if (!process.waitForStarted()) {
            QMessageBox::warning(this, "Erreur", "Impossible de démarrer le processus Python pour générer le QR Code.");
            return;
        }

        process.waitForFinished();

        // Vérifier si le fichier image existe après l'exécution
        QFile file(outputPath);
        if (file.exists()) {
            QPixmap qrPixmap(outputPath);  // Charger l'image générée
            if (!qrPixmap.isNull()) {
                ui->qrLabel->setPixmap(qrPixmap.scaled(ui->qrLabel->size(), Qt::KeepAspectRatio));  // Afficher l'image dans QLabel
                ui->qrLabel->update();  // Rafraîchir le QLabel pour afficher la nouvelle image
            } else {
                QMessageBox::warning(this, "Erreur", "Le QR Code généré est vide.");
            }
        } else {
            QMessageBox::warning(this, "Erreur", "Le QR Code n'a pas été généré.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les informations du produit.");
    }
}

