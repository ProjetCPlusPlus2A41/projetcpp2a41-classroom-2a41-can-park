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
#include "employee.h"
#include "senario.h"
#include "produit.h"
#include "sms.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu),    pi(0)  // Initialize 'pi' with a default value

{
    ui->setupUi(this);

//livraisonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
    connect(ui->confirmerl, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedl);
    ui->tableViewl->setModel(ESl.afficher());
    connect(ui->ajouterl, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetl->setCurrentIndex(1);
    });
   connect(ui->supprimerl, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedl);


    connect(ui->listel, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetl->setCurrentIndex(0);
        ui->tableViewl->setModel(ESl.afficher());
    });
    connect(ui->avancel, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetl->setCurrentIndex(2);
    });
    connect(ui->pdfl, &QPushButton::clicked, this, &Menu::exporterEnPDFl);
    connect(ui->tril, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableViewl);
    connect(ui->recherchel, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherchel);
    ui->tableViewl->setModel(ESl.afficher());
    connect(ui->supprimerToutl, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clickedl);
    ui->tableViewl->setModel(ESl.afficher());
    connect(ui->statiquesl, &QPushButton::clicked, this, [this]() {
        this->pi = 2;  // Set 'pi' to 2 when the first button is clicked
        qDebug() << "Value of pi after statiquesl click:" << pi;  // Debugging
        openStatistiquesDialog();
    });




    //prduittttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

    connect(ui->confirmert, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedt);
    ui->tableViewt->setModel(ESt.afficher());
    connect(ui->ajoutert, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgett->setCurrentIndex(1);
    });
   connect(ui->supprimert, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedt);


    connect(ui->listet, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgett->setCurrentIndex(0);
        ui->tableViewt->setModel(ESt.afficher());
    });
    connect(ui->avancet, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgett->setCurrentIndex(2);
    });
    connect(ui->pdft, &QPushButton::clicked, this, &Menu::exporterEnPDFt);
    connect(ui->trit, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableViewt);
    connect(ui->recherchet, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherchet);
    ui->tableViewt->setModel(ESt.afficher());
    connect(ui->supprimerToutt, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clickedt);
    ui->tableViewt->setModel(ESt.afficher());
    ui->tableViewt->setModel(ESt.afficher());
    connect(ui->statiquest, &QPushButton::clicked, this, [this]() {
        this->pi = 4;  // Set 'pi' to 1 when the second button is clicked
        qDebug() << "Value of pi after statiques click:" << pi;  // Debugging
        openStatistiquesDialog();
    });
    //employeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
        connect(ui->confirmere, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikede);
        ui->tableViewe->setModel(ESe.afficher());
        connect(ui->ajoutere, &QPushButton::clicked, this, [this]() {
            ui->stackedWidgete->setCurrentIndex(1);
        });
       connect(ui->supprimere, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikede);


        connect(ui->listee, &QPushButton::clicked, this, [this]() {
            ui->stackedWidgete->setCurrentIndex(0);
            ui->tableViewe->setModel(ESe.afficher());
        });
        connect(ui->pdfe, &QPushButton::clicked, this, &Menu::exporterEnPDFe);
        connect(ui->trie, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableViewe);
        connect(ui->recherchee, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherchee);
        ui->tableViewe->setModel(ESe.afficher());
        connect(ui->supprimerToute, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clickede);
        connect(ui->exe, &QPushButton::clicked, this, [this]() {
            exporterEnExcel(ui->tableViewe->model());
        });
        connect(ui->statiquese, &QPushButton::clicked, this, [this]() {
            this->pi = 3;  // Set 'pi' to 1 when the second button is clicked
            openStatistiquesDialog();
        });
        ui->tableViewe->setModel(ESe.afficher());
        //matiereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
    connect(ui->confirmerm, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedm);
    connect(ui->supprimerm, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedm);
    ui->tableViewm->setModel(ESm.afficher());
    connect(ui->ajouterm, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(1);
    });
    connect(ui->avancem, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(2);
    });


    connect(ui->listem, &QPushButton::clicked, this, [this]() {
        ui->stackedWidgetm->setCurrentIndex(0);
        ui->tableViewm->setModel(ESm.afficher());
    });
    ui->idm->setValidator(new QIntValidator(0, 999999, this));
    ui->idm1->setValidator(new QIntValidator(0, 999999, this));
    ui->am->setDate(QDate::currentDate());
    connect(ui->pdfm, &QPushButton::clicked, this, &Menu::exporterEnPDFm);
    connect(ui->trim, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableViewm);
    connect(ui->recherchem, &QLineEdit::textChanged, this, &Menu::on_textChanged_recherchem);
    ui->tableViewm->setModel(ESl.afficher());
    connect(ui->supprimerToutm, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clickedm);
    ui->tableViewm->setModel(ESm.afficher());
    connect(ui->statiquesm, &QPushButton::clicked, this, [this]() {
        this->pi = 5;  // Set 'pi' to 1 when the second button is clicked
        qDebug() << "Value of pi after statiques click:" << pi;  // Debugging
        openStatistiquesDialog();
    });
    //equipementttttttttttttttttttttttttttttttttttttttttttttttt
    connect(ui->confirmerq, &QPushButton::clicked, this, &Menu::on_pushbutton_ajouter_clikedq);
    connect(ui->supprimerq, &QPushButton::clicked, this, &Menu::on_pushbutton_supprimer_clikedq);
    ui->tableViewq->setModel(ESq.afficher());
    connect(ui->ajouterq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });
    connect(ui->avanceq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });


    connect(ui->listeq, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        ui->tableViewq->setModel(ESq.afficher());
    });
    connect(ui->pdfq, &QPushButton::clicked, this, &Menu::exporterEnPDFq);
    connect(ui->triq, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Menu::trierTableViewq);
    connect(ui->rechercheq, &QLineEdit::textChanged, this, &Menu::on_textChanged_rechercheq);
    ui->tableViewq->setModel(ESq.afficher());
    connect(ui->supprimerToutq, &QPushButton::clicked, this, &Menu::on_pushButton_supprimerTout_clickedq);
    connect(ui->statiquesq, &QPushButton::clicked, this, [this]() {
        this->pi = 6;  // Set 'pi' to 1 when the second button is clicked
        qDebug() << "Value of pi after statiques click:" << pi;  // Debugging
        openStatistiquesDialog();
    });
    connect(ui->sms, &QPushButton::clicked, this, &Menu::opensmsDialog);
    connect(ui->selectPhotoButton, &QPushButton::clicked, this, &Menu::on_selectPhotoButton_clicked);
    setupTableView();

    //clientttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
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
 connect(ui->ex, &QPushButton::clicked, this, [this]() {
     exporterEnExcel(ui->tableView->model());
 });


 connect(ui->statiques, &QPushButton::clicked, this, [this]() {
     this->pi = 1;  // Set 'pi' to 1 when the second button is clicked
     qDebug() << "Value of pi after statiques click:" << pi;  // Debugging
     openStatistiquesDialog();
 });

 connect(ui->honeywell, &QPushButton::clicked, this, &Menu::opensenarioDialog);

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
        ui->stackedWidget->setCurrentIndex(1);
    });


    connect(ui->delivery, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->employee, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
    });

    connect(ui->sale, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(4);
    });

    connect(ui->matter, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(5);
    });

    connect(ui->equipement, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(6); // Show equipment page
    });


}

Menu::~Menu()
{
    delete ui;
}
void Menu::setInitials(const QString &initials) {
    // Mettre à jour le texte du bouton avec les initiales
    ui->pushButton->setText(initials);

    // Personnaliser l'apparence pour ressembler à Microsoft
    ui->pushButton->setStyleSheet(
          "QPushButton {"
          "    border: 2px solid rgb(40, 72, 83);"   // Bordure de couleur spécifique
          "    border-radius: 50px;"                // Bouton circulaire
          "    background-color: rgb(40, 72, 83);"      // Fond transparent
          "    color: rgb(255, 255, 255);"             // Texte de la même couleur que la bordure
          "    font-size: 20px;"                    // Taille du texte
          "    font-weight: bold;"                  // Texte en gras
          "}"
          "QPushButton:hover {"
          "    background-color: rgba(40, 72, 83, 0.1);" // Fond légèrement coloré au survol
          "}"
      );
    ui->pushButton->setFixedSize(100, 100); // Taille fixe pour un cercle parfait
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
    float prix = quantite * 0.5;

Client E(id, nom, prenom, email, type_cli, produit, tel, quantite, date,prix);
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

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE id = :id");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec()) {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();

        if (count == 0) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("No Client found with the given ID.\nPlease enter a valid ID."),
                                 QMessageBox::Ok);
            return;
        }
    } else {
        QMessageBox::critical(this, tr("Error"),
                              tr("Failed to check if the Client exists in the database.\nClick OK to continue."),
                              QMessageBox::Ok);
        return;
    }

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
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("CLIENT");
    model->select();
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
        switch (index) {
            case 1:
                model->setSort(model->fieldIndex("nom"), Qt::AscendingOrder);
                break;
            case 2:
                model->setSort(model->fieldIndex("quantite"), Qt::DescendingOrder);
                break;
            default:
                model->setSort(-1, Qt::AscendingOrder); // Default behavior
                break;
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

void Menu::on_pushButton_supprimerTout_clicked()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT");
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
        query.prepare("DELETE FROM CLIENT");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            clearAndRefreshTable();  // Refresh the table view after deletion
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}
void Menu::exporterEnExcel(QAbstractItemModel* model) {
    if (!model) {
        QMessageBox::critical(this, "Erreur", "Aucun modèle à exporter.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, "Exporter en Excel", "", "Excel Files (*.xlsx)");
    if (filename.isEmpty()) {
        return;  // Annulé par l'utilisateur
    }

    QAxObject *excel = new QAxObject("Excel.Application", this);
    if (!excel || excel->isNull()) {
        QMessageBox::critical(this, "Erreur", "Impossible de démarrer Excel. Vérifiez son installation.");
        delete excel;
        return;
    }

    excel->setProperty("Visible", false);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add");
    QAxObject *sheet = workbook->querySubObject("Worksheets(int)", 1);

    // Export des en-têtes
    for (int col = 0; col < model->columnCount(); ++col) {
        QString headerText = model->headerData(col, Qt::Horizontal).toString();
        QString cell = QString("%1%2").arg(QChar('A' + col)).arg(1);  // Ligne 1 pour les en-têtes
        QAxObject *cellObject = sheet->querySubObject("Range(const QString&)", cell);
        cellObject->setProperty("Value", headerText);
        delete cellObject;
    }

    // Export des données
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellText = model->data(model->index(row, col)).toString();
            QString cell = QString("%1%2").arg(QChar('A' + col)).arg(row + 2);  // Ligne 2+ pour les données
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

    QMessageBox::information(this, "Succès", "Données exportées avec succès !");
}


void Menu::openStatistiquesDialog() {
    SAT *satDialog = new SAT(pi, this); // Passer la valeur actuelle de pi
        satDialog->exec();
}
void Menu::openEmailDialog(){
    mail *dialog = new mail(this);
       dialog->exec();


}
void Menu::openbareDialog(){
    bare *dialog = new bare(this);
       dialog->exec();


}
void Menu::opensenarioDialog() {
    // Using QScopedPointer to automatically manage memory
    QScopedPointer<senario> dialog(new senario(this));

    // Exécuter le dialogue en mode modal
    dialog->exec();
}
void Menu::opensmsDialog(){
    sms *dialog = new sms(this);
       dialog->exec();


}
//employeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void Menu::on_pushbutton_ajouter_clikede()
{
    int ide = ui->ide->text().toInt();
    QString nome = ui->nome->text();
    QString prenome = ui->prenome->text();

    QString emaile = ui->emaile->text();
    QString numc = ui->nume->text();
    float salairec = ui->salairee->text().toFloat();
    QString postec = ui->postee->text();
    QDate datec = ui->datee->date();

    // Create the employee object
    employee emp(ide, prenome,nome,emaile,numc,salairec,postec,datec);

    // Add the employee to the database
    bool test = emp.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The employee was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewe->setModel(emp.afficher());  // Refresh the table
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the employee to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

// Slot for deleting an employee by ID
void Menu::on_pushbutton_supprimer_clikede()
{
    int ide = ui->lineEdit_IDSe->text().toInt();
    bool test = ESe.supprimer(ide);  // Use emp instance here

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The employee was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewe->setModel(ESe.afficher());  // Refresh the table
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the employee from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
void Menu::on_textChanged_recherchee(const QString &text)
{
    if (text.isEmpty()) {
        ui->tableViewe->setModel(ESe.afficher());
    } else {
        bool ok;
        int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParIde(idRecherche);
        }
    }
}

void Menu::rechercherParIde(int idRecherche)
{
    QString idRechercheStr = QString::number(idRecherche);

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE TO_CHAR(ide) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableViewe->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}

void Menu::trierTableViewe(int index)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewe->model());

    if (model) {
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("NOME"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("SALAIREC"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
    }
}

void Menu::exporterEnPDFe()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Nom de fichier non spécifié."));
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

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewe->model());
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
    QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès en PDF."));
}


void Menu::on_pushButton_supprimerTout_clickede()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYE");
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
        query.prepare("DELETE FROM EMPLOYE");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            ui->tableViewe->setModel(ESe.afficher());
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
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
    if (currentImagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Avertissement"),
                             tr("Veuillez sélectionner une photo avant d'ajouter un équipement."),
                             QMessageBox::Ok);
        return;
    }


    // Ajouter la photo comme chemin ou BLOB
    bool test = E.ajouter(currentImagePath);
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
void Menu::on_textChanged_rechercheq(const QString &text)
{
    if (text.isEmpty()) {
        ui->tableViewq->setModel(ESq.afficher());
    } else {
        bool ok;
        int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParIdq(idRecherche);
        }
    }
}

void Menu::rechercherParIdq(int idRecherche)
{
    QString idRechercheStr = QString::number(idRecherche);

    QSqlQuery query;
    query.prepare("SELECT * FROM EQUIPEMENT WHERE TO_CHAR(ID_EQ) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableViewq->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}

void Menu::trierTableViewq(int index)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewq->model());

    if (model) {
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("NOM_EQ"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("NB_EQ"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
    }
}

void Menu::exporterEnPDFq()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Nom de fichier non spécifié."));
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

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewq->model());
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
    QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès en PDF."));
}
void Menu::on_pushButton_supprimerTout_clickedq()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EQUIPEMENT");
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
        query.prepare("DELETE FROM EQUIPEMENT");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            ui->tableViewq->setModel(ESq.afficher());
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}
void Menu::setupTableView()
{
    ui->tableViewq->setModel(ESq.afficher());

    // Ajouter le délégué pour afficher les images
    PhotoBlobDelegate *photoDelegate = new PhotoBlobDelegate(this);
    ui->tableViewq->setItemDelegateForColumn(6, photoDelegate); // Colonne 6 pour les images

    ui->tableViewq->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewq->verticalHeader()->setDefaultSectionSize(100);
}

void Menu::on_selectPhotoButton_clicked()
{
    qDebug() << "Photo selection button clicked"; // Ajoutez ceci pour voir si c'est appelé plusieurs fois

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Sélectionnez une image"), "",
                                                     tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        ui->photoLabel->setPixmap(pixmap.scaled(ui->photoLabel->size(),
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation));
        currentImagePath = imagePath; // Enregistrer le chemin pour utilisation
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
void Menu::on_textChanged_recherchem(const QString &text)
{
    if (text.isEmpty()) {
        ui->tableViewm->setModel(ESm.afficher());
    } else {
        bool ok;
        int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParIdm(idRecherche);
        }
    }
}

void Menu::rechercherParIdm(int idRecherche)
{
    QString idRechercheStr = QString::number(idRecherche);

    QSqlQuery query;
    query.prepare("SELECT * FROM MATIERE WHERE TO_CHAR(idm) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableViewm->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}

void Menu::trierTableViewm(int index)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewm->model());

    if (model) {
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("QUANTITEM"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("PRIXM"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
    }
}

void Menu::exporterEnPDFm()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Nom de fichier non spécifié."));
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

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewm->model());
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
    QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès en PDF."));
}
void Menu::on_pushButton_supprimerTout_clickedm()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM MATIERE");
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
        query.prepare("DELETE FROM MATIERE");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            ui->tableViewm->setModel(ESm.afficher());
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}
//prouitttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

void Menu::on_pushbutton_ajouter_clikedt()
{
    int idt = ui->idt->text().toInt();
    QString nomt = ui->nomt->text();

    int quantitet = ui->quantitet->text().toInt();
    float prixt = ui->prixt->text().toFloat();


    produit M(idt,nomt,prixt,quantitet);
    bool test = M.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewt->setModel(ESt.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the material to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Menu::on_pushbutton_supprimer_clikedt()
{
    int idt = ui->lineEdit_IDSt->text().toInt();
    bool test = ESt.supprimer(idt);

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewt->setModel(ESt.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the material from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
void Menu::on_textChanged_recherchet(const QString &text)
{
    if (text.isEmpty()) {
        ui->tableViewt->setModel(ESt.afficher());
    } else {
        bool ok;
        int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParIdt(idRecherche);
        }
    }
}

void Menu::rechercherParIdt(int idRecherche)
{
    QString idRechercheStr = QString::number(idRecherche);

    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT WHERE TO_CHAR(idt) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableViewt->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}

void Menu::trierTableViewt(int index)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewt->model());

    if (model) {
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("QUANTITET"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("PRIXT"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
    }
}

void Menu::exporterEnPDFt()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Nom de fichier non spécifié."));
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

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewt->model());
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
    QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès en PDF."));
}
void Menu::on_pushButton_supprimerTout_clickedt()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM PRODUIT");
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
        query.prepare("DELETE FROM PRODUIT");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            ui->tableViewt->setModel(ESt.afficher());
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}
//livraisonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
void Menu::on_pushbutton_ajouter_clikedl()
{
    int id_livraison = ui->idl->text().toInt();
    QDate date_livraison = ui->datel->date();
    QString adresse_livraison = ui->adressel->text();
    double frais_livraison = ui->fraisl->text().toDouble();
    QString type_livraison = ui->typel->text();
    QString etat_livraison = ui->etatl->text();

    Livraison L(id_livraison, date_livraison, adresse_livraison, frais_livraison, type_livraison, etat_livraison);
    bool test = L.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewl->setModel(ESl.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the material to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Menu::on_pushbutton_supprimer_clikedl()
{
    int idl = ui->lineEdit_IDSl->text().toInt();
    bool test = ESl.supprimer(idl);

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The material was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewl->setModel(ESl.afficher());
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the material from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
void Menu::on_textChanged_recherchel(const QString &text)
{
    if (text.isEmpty()) {
        ui->tableViewl->setModel(ESl.afficher());
    } else {
        bool ok;
        int idRecherche = text.toInt(&ok);
        if (ok) {
            rechercherParIdl(idRecherche);
        }
    }
}

void Menu::rechercherParIdl(int idRecherche)
{
    QString idRechercheStr = QString::number(idRecherche);

    QSqlQuery query;
    query.prepare("SELECT * FROM LIVRAISON WHERE TO_CHAR(ID_LIVRAISON) LIKE :id");
    query.bindValue(":id", idRechercheStr + "%");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableViewl->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche.");
    }
}

void Menu::trierTableViewl(int index)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewl->model());

    if (model) {
        if (index == 0) {
            model->setSort(-1, Qt::AscendingOrder);
        } else {
            switch (index) {
                case 1:
                    model->setSort(model->fieldIndex("frais_livraison"), Qt::AscendingOrder);
                    break;
                case 2:
                    model->setSort(model->fieldIndex("date_livraison"), Qt::DescendingOrder);
                    break;
                default:
                    return;
            }
        }
        model->select();
    }
}

void Menu::exporterEnPDFl()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Nom de fichier non spécifié."));
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

    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableViewl->model());
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
    QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès en PDF."));
}
void Menu::on_pushButton_supprimerTout_clickedl()
{
    // Check if the table is empty
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM LIVRAISON");
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
        query.prepare("DELETE FROM LIVRAISON");
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Toutes les entrées ont été supprimées.");
            ui->tableViewl->setModel(ESl.afficher());
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression de toutes les entrées.");
        }
    }
}




