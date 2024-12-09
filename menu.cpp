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
#include "sat.h"
#include "mail.h"
#include "bare.h"
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->confirmerm, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedm);
    connect(ui->supprimerm, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedm);
    ui->tableViewm->setModel(ESm.afficher());
    connect(ui->ajouterm, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(1); // Show client page
    });
    connect(ui->avancem, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(2); // Show client management page
    });

    // Connect push_button_2 to display the employee management page
    connect(ui->statiquesm, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(3); // Show client page
    });
    connect(ui->listem, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(0);
        ui->tableViewm->setModel(ESm.afficher());// Show client management page
    });
    ui->idm->setValidator(new QIntValidator(0, 999999, this));
    ui->idm1->setValidator(new QIntValidator(0, 999999, this));
    ui->am->setDate(QDate::currentDate());

    //matiereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
    connect(ui->confirmerq, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedq);
    connect(ui->supprimerq, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedq);
    ui->tableViewq->setModel(ESq.afficher());
    connect(ui->ajouterq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->avanceq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(2); // Show client management page
    });

    connect(ui->statiquesq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(3);
    });
    connect(ui->listeq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        ui->tableViewq->setModel(ESq.afficher());
    });
    //equipementttttttttttttttttttttttttttttttttttttttttttttttt
    ui->recherche->setPlaceholderText("recherche");
    ui->tableView->setModel(Es.afficher());
 ui->id->setValidator(new QIntValidator(0, 999999, this));
 connect(ui->confirmer, &QPushButton::clicked, this, &Menu::on_pushButton_ajouter_clicked);
 connect(ui->carte, &QPushButton::clicked, this, &Menu::openbareDialog);

    connect(ui->supprimer, &QPushButton::clicked, this, &Menu::on_pushButton_supprimer_clicked);

    connect(ui->recherche, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherche);
connect(ui->tri, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableView);

ui->dateEdit->setDate(QDate::currentDate());
 connect(ui->pdf, &QPushButton::clicked, this, &Menu::exporterEnPDF);
 connect(ui->ex, &QPushButton::clicked, this, &Menu::exporterEnExcel);

 connect(ui->statiques, &QPushButton::clicked, this, &Menu::openStatistiquesDialog);

 connect(ui->emailc, &QPushButton::clicked, this, &Menu::openEmailDialog);

    updateTableView();


    connect(ui->supprimerTout, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clicked);

    connect(ui->liste, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });

    connect(ui->ajouter, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->avance, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });



    connect(ui->home, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });


    connect(ui->client, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1); // Show client page
    });


    connect(ui->delivery, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2); // Show delivery page
    });

    connect(ui->employee, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(3); // Show employee page
    });

    connect(ui->sale, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(4); // Show sale page
    });

    connect(ui->matter, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(5); // Show matter page
    });

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

    // Check if the id exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE id = :id");  // Adjust the table and column name if necessary
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec()) {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();

        if (count == 0) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("No Client found with the given ID.\nPlease enter a valid ID."),
                                 QMessageBox::Ok);
            return;  // Exit the function if the id does not exist
        }
    } else {
        QMessageBox::critical(this, tr("Error"),
                              tr("Failed to check if the Client exists in the database.\nClick OK to continue."),
                              QMessageBox::Ok);
        return;
    }

    // Proceed with the deletion if the id is valid
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

    if (text.isEmpty()) {
        ui->tableView->setModel(Es.afficher());
    } else {

        bool ok;
               int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParId(idRecherche);
        }
    }
}
void Menu::rechercherParId(int idRecherche)
{

    QString idRechercheStr = QString::number(idRecherche);


    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE TO_CHAR(ID) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {

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
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("Nom"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("Quantite"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
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
        int columnWidth = 500;


        for (int col = 0; col < model->columnCount(); ++col) {
            painter.drawText(col * columnWidth, yOffset, model->headerData(col, Qt::Horizontal).toString());
        }
        yOffset += rowHeight;


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

    QString filename = QFileDialog::getSaveFileName(this, "Exporter en Excel", "", "Excel Files (*.xlsx)");

    if (filename.isEmpty()) {
        return;
    }

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
    if (!model) {
        return;
    }

    QAxObject *excel = new QAxObject("Excel.Application", this);
    excel->setProperty("Visible", false);


    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add");
    QAxObject *sheet = workbook->querySubObject("Worksheets(int)", 1);

    // Exporter les en-têtes du modèle
    for (int col = 0; col < model->columnCount(); ++col) {
        QString headerText = model->headerData(col, Qt::Horizontal).toString();
        QString cell = QString("%1%2").arg(QChar('A' + col)).arg(1);
        QAxObject *cellObject = sheet->querySubObject("Range(const QString&)", cell);
        cellObject->setProperty("Value", headerText);
        delete cellObject;
    }


    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellText = model->data(model->index(row, col)).toString();
            QString cell = QString("%1%2").arg(QChar('A' + col)).arg(row + 2); // Ligne 2 pour les données
            QAxObject *cellObject = sheet->querySubObject("Range(const QString&)", cell);
            cellObject->setProperty("Value", cellText);
            delete cellObject;
        }
    }

    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filename));

    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    delete sheet;
    delete workbook;
    delete workbooks;
    delete excel;
}

void Menu::openStatistiquesDialog() {
    SAT *dialog = new SAT(this);
       dialog->exec();
}
void Menu::openEmailDialog(){
    mail *dialog = new mail(this);
       dialog->exec();


}
void Menu::openbareDialog(){
    bare *dialog = new bare(this);
       dialog->exec();


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
//matireeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void Menu::on_pushbutton_ajouter_clikedm()
{
    int idm = ui->idm->text().toInt();
    QString produitm = ui->porduitm->text();
    QString cm = ui->cm->text();
    float quantitem = ui->quantitem->text().toFloat();
    float prixm = ui->pm->text().toFloat();
    QDate em = ui->em->date();
    QDate am = ui->am->date();

    matiere M(idm, produitm, cm, quantitem, prixm, em, am);
    bool test = M.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewm->setModel(ESm.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the material to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Menu::on_pushbutton_supprimer_clikedm()
{
    int idm = ui->idm1->text().toInt();
    bool test = ESm.supprimer(idm);

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewm->setModel(ESm.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the material from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
void Menu::on_pushButton_supprimerTout_clicked()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT");  // Adjust the table name if necessary
    if (checkQuery.exec()) {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();

        // If there are no records, show an info message
        if (count == 0) {
            QMessageBox::information(this, "Information", "The table is empty. No entries to delete.");
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to check if the table is empty.");
        return;
    }

    // Ask the user for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer toutes les entrées ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Call the delete method for all records
        QSqlQuery query;
        query.prepare("DELETE FROM CLIENT");  // Adjust the table name if necessary
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            clearAndRefreshTable();  // Refresh the table view after deletion
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}







