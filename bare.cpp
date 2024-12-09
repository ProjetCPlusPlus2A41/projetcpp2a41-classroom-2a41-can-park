#include "bare.h"
#include "menu.h"
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QSqlTableModel>
#include <QIntValidator>
#include <QAxObject>
#include "ui_bare.h"
#include "ui_menu.h"
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QAxObject>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include"client.h"
bare::bare(QWidget *parent) :
     QDialog(parent),
    ui(new Ui::bare)
{
    ui->setupUi(this);
ui->tableView->setVisible(false);
    connect(ui->envoi_2, &QPushButton::clicked, this, &bare::genererCodeBarre);
    connect(ui->cancel, &QPushButton::clicked, this, &bare::close);
    connect(ui->envoi3, &QPushButton::clicked, this, [this]() {
        if (ui->tableView->isVisible()) {
            ui->tableView->setVisible(false);
        } else {
            ui->tableView->setModel(Es.afficher());
            ui->tableView->setVisible(true);
        }
    });

    connect(ui->envoi, &QPushButton::clicked, this, &bare::exporterEnPDF);

ui->lineEditId->setValidator(new QIntValidator(0, 999999, this));

}

bare::~bare()
{
    delete ui;
}

void bare::genererCodeBarre() {
    bool ok;
       int id = ui->lineEditId->text().toInt(&ok);
       if (!ok) {
           QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
           return;
       }

       Client client;

           if (client.checkIfExists(id)) {
               QString cheminFichierExcel = "C:\\firqs\\Classeur3.xlsm";
               envoyerIdVersExcel(cheminFichierExcel, QString::number(id));
           } else {
               QMessageBox::warning(this, "Erreur", "Le code à barre n'existe pas pour cet ID !");
           }
       }


void bare::envoyerIdVersExcel(const QString& cheminFichierExcel, const QString& id) {
    QAxObject* excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false);  // Hide Excel

    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", cheminFichierExcel);
    QAxObject* sheet = workbook->querySubObject("Worksheets(int)", 1);

    QAxObject* cell = sheet->querySubObject("Cells(int, int)", 1, 1);
    cell->setProperty("Value", id);

    excel->dynamicCall("Run(const QString&)", "GenererCodeBarre");  // Call the macro

    workbook->dynamicCall("Save()");


    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    delete cell;
    delete sheet;
    delete workbook;
    delete workbooks;
    delete excel;

    QTimer::singleShot(0, this, &bare::afficherImageDelayed);
}

void bare::afficherImageDelayed() {
    QString cheminImage = "C:/firqs/firqscodebarre.png";
    afficherImage(cheminImage);
}

void bare::afficherImage(const QString& cheminImage)
{
    QPixmap image(cheminImage);
    if (image.isNull()) {

        ui->label->setText("Erreur de chargement de l'image");
    } else {
        ui->label->setPixmap(image);
        ui->label->setScaledContents(true);
    }
}
void bare::exporterEnPDF() {
    QString directoryPath = "C:/firqs/canpark";

    QDir dir(directoryPath);
    if (!dir.exists()) {
        dir.mkpath(directoryPath);
    }

    QString filename = QFileDialog::getSaveFileName(this, "Exporter en PDF", directoryPath + "/CarteDeFidelite.pdf", "PDF Files (*.pdf)");

    if (filename.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom de fichier non spécifié.");
        return;
    }

    QPdfWriter writer(filename);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setResolution(300);

    QPainter painter(&writer);
    int margin = 30;
    painter.translate(margin, margin);

    QSizeF pageSize(1200, 620);
    float pageWidth = pageSize.width();
    float pageHeight = pageSize.height();

    QString frontBackgroundPath = "C:/firqs/canpark/vueface.png";
    QPixmap frontBackground(frontBackgroundPath);
    if (!frontBackground.isNull()) {
        painter.drawPixmap(0, 0, pageWidth / 2, pageHeight / 2, frontBackground);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image d'arrière-plan avant.");
    }

    QString backBackgroundPath = "C:/firqs/canpark/vuear.png";  // Provide the path to the back background image
    QPixmap backBackground(backBackgroundPath);
    if (!backBackground.isNull()) {
        painter.drawPixmap(700, 0, pageWidth / 2, pageHeight / 2, backBackground);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image d'arrière-plan arrière.");
    }



    QFont headerFont("Arial", 14, QFont::Bold);
    QFont dataFont("Arial", 12);

    int id = ui->lineEditId->text().toInt();
    Client client;

    if (client.checkIfExists(id)) {
        QSqlQuery query;
        query.prepare("SELECT nom, prenom FROM CLIENT WHERE id = :id");
        query.bindValue(":id", id);
        if (query.exec() && query.next()) {
            QString nom = query.value("nom").toString();
            QString prenom = query.value("prenom").toString();

            painter.setFont(dataFont);
            painter.setPen(QPen(QColor(255,255,255)));
            painter.drawText(230, 150, "ID: " + QString::number(id));
            painter.drawText(230, 200, "Nom: " + nom);
            painter.drawText(230, 250, "Prénom: " + prenom);
        } else {
            QMessageBox::warning(this, "Erreur", "Client introuvable.");
        }
    }


    QString cheminImage = "C:/firqs/firqscodebarre.png";
    QPixmap image(cheminImage);
    if (!image.isNull()) {
        int barcodeWidth = 400;
        int barcodeHeight = image.height() * barcodeWidth / image.width();

        int barcodeX = 700 + (pageWidth / 2 - barcodeWidth) / 2;
        int barcodeY = (pageHeight / 2 - barcodeHeight) / 2;
        painter.drawPixmap(barcodeX, barcodeY, barcodeWidth, barcodeHeight, image);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image du code-barres.");
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Données exportées avec succès en PDF.");
}




