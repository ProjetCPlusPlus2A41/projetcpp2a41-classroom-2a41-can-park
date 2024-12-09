#include "bare.h"
#include "menu.h"
#include <QFileDialog>    // Pour ouvrir une boîte de dialogue de sauvegarde de fichier
#include <QPdfWriter>     // Pour l'écriture de fichiers PDF
#include <QPainter>       // Pour dessiner sur le PDF
#include <QMessageBox>    // Pour afficher des messages d'erreur ou de confirmation
#include <QPixmap>        // Pour gérer les images, comme le code-barres
#include <QBrush>         // Pour remplir des formes avec des couleurs
#include <QPen>           // Pour définir les couleurs et styles de ligne pour le texte
#include <QFont>          // Pour gérer les polices de texte
#include <QSqlTableModel> // Pour manipuler les données de la table SQL dans les vues
#include <QIntValidator>  // Pour valider les entrées numériques
#include <QAxObject>
#include "ui_bare.h"
#include "ui_menu.h"
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QAxObject>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>  // Include QTimer
#include"client.h"
bare::bare(QWidget *parent) :
     QDialog(parent),
    ui(new Ui::bare)
{
    ui->setupUi(this);
ui->tableView->setVisible(false);
    // Connect the button to the barcode generation action
    connect(ui->envoi_2, &QPushButton::clicked, this, &bare::genererCodeBarre);
    connect(ui->cancel, &QPushButton::clicked, this, &bare::close);
    // Connect the button click to toggle the visibility of the table view
    connect(ui->envoi3, &QPushButton::clicked, this, [this]() {
        // Check if the table view is currently visible
        if (ui->tableView->isVisible()) {
            ui->tableView->setVisible(false);  // Hide the table view if it's visible
        } else {
            ui->tableView->setModel(Es.afficher());  // Set the model for the table
            ui->tableView->setVisible(true);  // Show the table view if it's hidden
        }
    });

    connect(ui->envoi, &QPushButton::clicked, this, &bare::exporterEnPDF);

ui->lineEditId->setValidator(new QIntValidator(0, 999999, this));
    // Optionally display the initial image if available
}

bare::~bare()
{
    delete ui;
}

// Function to generate barcode from the entered ID
void bare::genererCodeBarre() {
    bool ok;
       int id = ui->lineEditId->text().toInt(&ok);  // Convert the entered text into an integer

       if (!ok) {
           QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
           return;  // Exit if the ID is invalid
       }

       Client client;

           if (client.checkIfExists(id)) {
               // ID exists, proceed to generate barcode
               QString cheminFichierExcel = "C:\\firqs\\Classeur3.xlsm";  // Path to the Excel file
               envoyerIdVersExcel(cheminFichierExcel, QString::number(id));  // Call the method to generate barcode
           } else {
               // ID does not exist in the database
               QMessageBox::warning(this, "Erreur", "Le code à barre n'existe pas pour cet ID !");
           }
       }


// Implementation of envoyerIdVersExcel
void bare::envoyerIdVersExcel(const QString& cheminFichierExcel, const QString& id) {
    QAxObject* excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false);  // Hide Excel

    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", cheminFichierExcel);
    QAxObject* sheet = workbook->querySubObject("Worksheets(int)", 1);

    // Place the ID in cell A1
    QAxObject* cell = sheet->querySubObject("Cells(int, int)", 1, 1);
    cell->setProperty("Value", id);

    // Call the macro to generate the barcode
    excel->dynamicCall("Run(const QString&)", "GenererCodeBarre");  // Call the macro

    // Save the Excel file
    workbook->dynamicCall("Save()");

    // Optionally: Wait for 2 seconds to ensure the barcode is generated (you can make it asynchronous)

    // Close the Excel file and quit Excel
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    // Clean up
    delete cell;
    delete sheet;
    delete workbook;
    delete workbooks;
    delete excel;

    // Use QTimer to delay the display of the generated barcode image by 7 seconds
    QTimer::singleShot(0, this, &bare::afficherImageDelayed);
}

// Function to display the image after a delay
void bare::afficherImageDelayed() {
    QString cheminImage = "C:/firqs/firqscodebarre.png";  // Replace with the actual path of the generated barcode image
    afficherImage(cheminImage);
}

void bare::afficherImage(const QString& cheminImage)
{
    QPixmap image(cheminImage);  // Load the image from the file
    if (image.isNull()) {
        // If the image is invalid, display an error message
        ui->label->setText("Erreur de chargement de l'image");
    } else {
        // Display the image in the QLabel
        ui->label->setPixmap(image);
        ui->label->setScaledContents(true);  // Resize the image to fit the QLabel
    }
}
void bare::exporterEnPDF() {
    // Define the directory path where cards will be saved
    QString directoryPath = "C:/firqs/canpark";  // Adjust the path as needed

    // Create the directory if it doesn't exist
    QDir dir(directoryPath);
    if (!dir.exists()) {
        dir.mkpath(directoryPath);
    }

    // Get the file name for saving within the specified folder
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

    QSizeF pageSize(1200, 620);  // Adjusted for A4
    float pageWidth = pageSize.width();
    float pageHeight = pageSize.height();

    // Load background image for the front card section
    QString frontBackgroundPath = "C:/firqs/canpark/vueface.png";  // Provide the path to the front background image
    QPixmap frontBackground(frontBackgroundPath);
    if (!frontBackground.isNull()) {
        painter.drawPixmap(0, 0, pageWidth / 2, pageHeight / 2, frontBackground);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image d'arrière-plan avant.");
    }

    // Load background image for the back card section
    QString backBackgroundPath = "C:/firqs/canpark/vuear.png";  // Provide the path to the back background image
    QPixmap backBackground(backBackgroundPath);
    if (!backBackground.isNull()) {
        painter.drawPixmap(700, 0, pageWidth / 2, pageHeight / 2, backBackground);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image d'arrière-plan arrière.");
    }

    // Add the logo at the top center of the front card


    // Front card content
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
            painter.setPen(QPen(QColor(255,255,255)));  // Black text color
            painter.drawText(230, 150, "ID: " + QString::number(id));
            painter.drawText(230, 200, "Nom: " + nom);
            painter.drawText(230, 250, "Prénom: " + prenom);
        } else {
            QMessageBox::warning(this, "Erreur", "Client introuvable.");
        }
    }

    // Barcode placement (back section)
    QString cheminImage = "C:/firqs/firqscodebarre.png";  // Path for the barcode image
    QPixmap image(cheminImage);
    if (!image.isNull()) {
        int barcodeWidth = 400;  // Adjust barcode size
        int barcodeHeight = image.height() * barcodeWidth / image.width();  // Maintain aspect ratio

        // Calculate centered position within the right rectangle
        int barcodeX = 700 + (pageWidth / 2 - barcodeWidth) / 2;
        int barcodeY = (pageHeight / 2 - barcodeHeight) / 2;
        painter.drawPixmap(barcodeX, barcodeY, barcodeWidth, barcodeHeight, image);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'image du code-barres.");
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Données exportées avec succès en PDF.");
}




