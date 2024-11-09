#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QTableView>
#include <QDebug>
#include <QAxObject>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtSql/QSqlQuery>
#include "sat.h"  // Adjust the class name to match your dialog class

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->confirmerq, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedq);
    connect(ui->supprimerq, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedq);
    ui->tableViewq->setModel(ESq.afficher());
    connect(ui->ajouterq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(1); // Show client page
    });
    connect(ui->avanceq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(2); // Show client management page
    });

    // Connect push_button_2 to display the employee management page
    connect(ui->statiquesq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(3); // Show client page
    });
    connect(ui->listeq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        ui->tableViewq->setModel(ESq.afficher());// Show client management page
    });
    //equipementttttttttttttttttttttttttttttttttttttttttttttttt
    ui->recherche->setPlaceholderText("recherche");
    ui->tableView->setModel(Es.afficher());
 ui->id->setValidator(new QIntValidator(0, 999999, this));
 connect(ui->confirmer, &QPushButton::clicked, this, &Menu::on_pushButton_ajouter_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &Menu::on_pushButton_supprimer_clicked);
    // Connectez le signal textChanged à un slot de recherche dans le constructeur de votre fenêtre
    connect(ui->recherche, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherche);
connect(ui->tri, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableView);
// Initialiser la date du jour dans le QDateEdit
ui->dateEdit->setDate(QDate::currentDate());
 connect(ui->pdf, &QPushButton::clicked, this, &Menu::exporterEnPDF);
 connect(ui->ex, &QPushButton::clicked, this, &Menu::exporterEnExcel);
 // Dans le constructeur ou une autre fonction appropriée :
 connect(ui->statiques, &QPushButton::clicked, this, &Menu::openStatistiquesDialog);


    updateTableView();



    connect(ui->liste, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(0); // Show client management page
    });

    // Connect push_button_2 to display the employee management page
    connect(ui->ajouter, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(1); // Show client page
    });
    connect(ui->avance, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(2); // Show client management page
    });

    // Connect push_button_2 to display the employee management page
    connect(ui->statiques, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(3); // Show client page
    });

    connect(ui->home, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0); // Show client management page
    });

    // Connect push_button_2 to display the employee management page
    connect(ui->client, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1); // Show client page
    });


    // Delivery
    connect(ui->delivery, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2); // Show delivery page
    });

    // Employee
    connect(ui->employee, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(3); // Show employee page
    });

    // Sale
    connect(ui->sale, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(4); // Show sale page
    });

    // Matter
    connect(ui->matter, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(5); // Show matter page
    });

    // Equipment
    connect(ui->equipement, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(6); // Show equipment page
    });


}

Menu::~Menu()
{
    delete ui;
}
void Menu::on_pushButton_ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString email = ui->email->text();
    QString type_cli = ui->type->text();
    QString produit = ui->produit->text();
    int tel = ui->telephone->text().toInt();
    float quantite = ui->quantite->text().toFloat();
    QDate date = ui->dateEdit->date();

Client E(id, nom, prenom, email, type_cli, produit, tel, quantite, date);
bool test = E.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The Client was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        clearAndRefreshTable();
        updateTableView();
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the Client to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Menu::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Es.supprimer(id);

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The Client was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        clearAndRefreshTable();
        updateTableView();
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the Client from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Menu::updateTableView()
{
    ui->tableView->setModel(nullptr);
    QSqlQueryModel *newModel = Es.afficher();
    ui->tableView->setModel(newModel);
}

void Menu::on_pushButton_refresh_clicked()
{
    updateTableView();
}

void Menu::clearAndRefreshTable()
{
    ui->tableView->setModel(nullptr);
    QSqlTableModel *model = Es.afficher();
    ui->tableView->setModel(model);
}

void Menu::on_textChanged_recherche(const QString &text)
{
    // Si le texte est vide, on réinitialise le modèle de la table
    if (text.isEmpty()) {
        ui->tableView->setModel(Es.afficher());
    } else {
        // Si le texte peut être converti en entier, on effectue la recherche par ID
        bool ok;
               int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParId(idRecherche);
        }
    }
}
void Menu::rechercherParId(int idRecherche)
{
    // Convertir l'ID en chaîne pour utiliser LIKE dans la requête SQL
    QString idRechercheStr = QString::number(idRecherche);

    // Créer une requête SQL pour rechercher les clients dont l'ID commence par ce texte
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE TO_CHAR(ID) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");  // Utilisation de % pour rechercher les IDs commençant par l'ID saisi

    if (query.exec()) {
        // Si la requête réussit, mettre à jour le modèle avec les résultats
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}
void Menu::trierTableView(int index) {
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());

    if (model) {
        if (index == 0) {  // Si l'index est 0, réinitialiser le tri
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:  // Trier par "Nom" en ordre croissant (insensible à la casse)
                    model->setSort(model->fieldIndex("Nom"), Qt::AscendingOrder);
                    break;
                case 2:  // Trier par "Quantite" en ordre décroissant
                    model->setSort(model->fieldIndex("Quantite"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();  // Rafraîchir la vue avec les données triées
    }
}
void Menu::exporterEnPDF() {
    QString filename = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");

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

    QFont headerFont("Arial", 12, QFont::Bold);
    QFont dataFont("Arial", 10);
    painter.setFont(headerFont);

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());

    if (model) {
        int yOffset = 50;
        int rowHeight = 200;
        int columnWidth = 500; // Augmenté pour un meilleur espacement des colonnes

        // Dessiner les en-têtes des colonnes
        for (int col = 0; col < model->columnCount(); ++col) {
            painter.drawText(col * columnWidth, yOffset, model->headerData(col, Qt::Horizontal).toString());
        }
        yOffset += rowHeight;

        // Dessiner les lignes de données
        painter.setFont(dataFont);
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellText = model->data(model->index(row, col)).toString();
                painter.drawText(col * columnWidth, yOffset, cellText);
            }
            yOffset += rowHeight;
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Données exportées avec succès en PDF.");
}


void Menu::exporterEnExcel() {
    // Sélectionner un emplacement pour sauvegarder le fichier Excel
    QString filename = QFileDialog::getSaveFileName(this, "Exporter en Excel", "", "Excel Files (*.xlsx)");

    if (filename.isEmpty()) {
        return; // Si aucun fichier n'est sélectionné, on quitte la fonction
    }

    // Obtenir le modèle de données du QTableView
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
    if (!model) {
        return; // Si le modèle n'est pas valide, on quitte la fonction
    }

    // Initialiser Excel via QAxObject
    QAxObject *excel = new QAxObject("Excel.Application", this);
    excel->setProperty("Visible", false); // Rendre Excel invisible pendant l'exportation

    // Créer un nouveau classeur
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add");
    QAxObject *sheet = workbook->querySubObject("Worksheets(int)", 1); // Sélectionner la première feuille

    // Exporter les en-têtes du modèle
    for (int col = 0; col < model->columnCount(); ++col) {
        QString headerText = model->headerData(col, Qt::Horizontal).toString();
        QString cell = QString("%1%2").arg(QChar('A' + col)).arg(1); // Ex: "A1", "B1", ...
        QAxObject *cellObject = sheet->querySubObject("Range(const QString&)", cell);
        cellObject->setProperty("Value", headerText);
        delete cellObject;
    }

    // Exporter les données du tableau
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellText = model->data(model->index(row, col)).toString();
            QString cell = QString("%1%2").arg(QChar('A' + col)).arg(row + 2); // Ligne 2 pour les données
            QAxObject *cellObject = sheet->querySubObject("Range(const QString&)", cell);
            cellObject->setProperty("Value", cellText);
            delete cellObject;
        }
    }

    // Sauvegarder le fichier Excel
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filename));

    // Fermer Excel
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    // Libérer la mémoire
    delete sheet;
    delete workbook;
    delete workbooks;
    delete excel;
}
#include <QtCharts>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QtCharts>
#include <QPushButton>
#include <QDialog>
#include <QSqlTableModel>
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include<QtCharts>
void Menu::openStatistiquesDialog() {
    SAT *dialog = new SAT(this);  // Create the dialog (replace "sat" with the actual dialog class name)
       dialog->exec();  // Show the dialog as a modal window
}
//equipementttttttttttttttttttt
void Menu::on_pushbutton_ajouter_clikedq(){

    int id_eq = ui->idq->text().toInt();
    QString nom_eq = ui->nomq->text();
    QString type_eq = ui->typeq->text();
    QString etat_eq = ui->etatq->text();
    int nb_eq = ui->nbq->text().toInt();
    float cout_eq = ui->coutq->text().toFloat();

    equipement E(nom_eq, type_eq, etat_eq, id_eq, nb_eq, cout_eq);
    bool test = E.ajouter();
    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The equipment was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        // Refresh table view to display the updated data
        ui->tableViewq->setModel(ESq.afficher());

    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the equipment to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
void Menu::on_pushbutton_supprimer_clikedq(){

    int id_eq = ui->idq2->text().toInt();
    bool test = ESq.supprimer(id_eq);
    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The Equipement was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewq->setModel(ESq.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the Equipement from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }

}








