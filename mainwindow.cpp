#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpressionValidator>


#define file_carac "^[A-Za-z]+$"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_produitM->setValidator(new QRegularExpressionValidator(QRegularExpression(file_carac), this));
    ui->le_idM->setValidator(new QIntValidator(0, 9999999999, this));//taille 10
    ui->le_quantiteM->setValidator(new QIntValidator(1, 999999999, this));//taille 9
    ui->le_dateajoutM->setDate(QDate::currentDate());
    ui->le_dateexpirationM->setDate(QDate::currentDate().addMonths(1));

    ui->tab_MatierePremiere->setModel(MP.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouterM_clicked()
{
    if(controlSaisie()==1)
{

QDate dateajout = ui->le_dateajoutM->date();
QDate dateexpiration = ui->le_dateexpirationM->date();
QString produit=ui->le_produitM->text();
float prix=ui->le_prixM->text().toFloat();
QString categorie=ui->le_categorieM->currentText();
int id=ui->le_idM->text().toInt();
int quantite=ui->le_quantiteM->text().toInt();


 MatierePremiere MP(id,produit,quantite,categorie,dateajout,dateexpiration,prix);

 bool test1=MP.MatierePremiereExiste(id);
  qDebug() <<test1;
             if(test1==false)
  {
     bool test=MP.ajouter();

      qDebug() <<test;
             QMessageBox msgBox;
             if(test)
             {
                 ui->tab_MatierePremiere->setModel(MP.afficher());
                  clear();
                 msgBox.setText("Ajout avec Succes.");
                msgBox.exec();
             }

             else
             {
             msgBox.setText("!!Echec d'Ajout!!");
           msgBox.exec();
             }
     }

             else
             {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                             QObject::tr("MatierePremiere Existe !\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

             }
}
}

void MainWindow::on_tab_MatierePremiere_activated(const QModelIndex &index)
{
    // Get the selected reference from the table
    QString val = ui->tab_MatierePremiere->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM matierepremiere WHERE id = :id");
    qry.bindValue(":id", val);
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->le_idM->setText(qry.value(0).toString());
            QDate le_dateajoutM = qry.value(4).toDate();
            ui->le_dateajoutM->setDate(le_dateajoutM);
            QDate le_dateexpirationM = qry.value(5).toDate();
            ui->le_dateexpirationM->setDate(le_dateexpirationM);
            ui->le_produitM->setText(qry.value(1).toString());
            ui->le_quantiteM->setText(qry.value(2).toString());
            ui->le_categorieM->setCurrentText(qry.value(3).toString());
            ui->le_prixM->setText(qry.value(6).toString());
            ui->le_IDm_supp->setText(qry.value(0).toString());
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error::"), qry.lastError().text());
    }
}

void MainWindow::clear()
{
    ui->le_idM->clear();
    ui->le_dateajoutM->setDate(QDate::currentDate());
    ui->le_dateajoutM->setDate(QDate::currentDate());
    ui->le_produitM->clear();
    ui->le_quantiteM->clear();
    ui->le_prixM->clear();
    ui->le_categorieM->setCurrentText("choix");
    ui->le_IDm_supp->clear();
}

bool MainWindow::controlSaisie() {

    if (ui->le_idM->text().isEmpty() || ui->le_idM->text().toInt() == 0) {
        QMessageBox::warning(this, "Invalid ID", "The ID field cannot be empty or zero.");
        return false;
    }

    QDate selectedADDDate = ui->le_dateajoutM->date();
    QDate selectedeXPIREDate = ui->le_dateexpirationM->date();


    if (selectedeXPIREDate <= selectedADDDate) {
        QMessageBox::warning(this, "Invalid Expire Date", "Expiration date must be later than the addition date.");
        return false;
    }


    if (ui->le_produitM->text().isEmpty() || ui->le_produitM->text() == "") {
        QMessageBox::warning(this, "Missing Product Command", "The Product Command field cannot be empty.");
        return false;
    }



    if (ui->le_prixM->text().isEmpty() || ui->le_prixM->text().toFloat() == 0.0f) {
        QMessageBox::warning(this, "Invalid Price", "The Price field cannot be empty or zero.");
        return false;
    }


    if (ui->le_quantiteM->text().isEmpty() || ui->le_quantiteM->text().toInt() == 0) {
        QMessageBox::warning(this, "Invalid Quantity", "The Quantity field cannot be empty or zero.");
        return false;
    }


     if (ui->le_categorieM->currentText() == "Select a category") {
         QMessageBox::warning(this, "Invalid Category", "Please select a valid category.");
         return false;
     }

    return true;
}


void MainWindow::on_pb_modifierM_clicked()
{
    if(controlSaisie()==1)
    {
        QDate dateajout = ui->le_dateajoutM->date();
        QDate dateexpiration = ui->le_dateexpirationM->date();
        QString produit=ui->le_produitM->text();
        float prix=ui->le_prixM->text().toFloat();
        QString categorie=ui->le_categorieM->currentText();
        int id=ui->le_idM->text().toInt();
        int quantite=ui->le_quantiteM->text().toInt();

        MatierePremiere MP(id,produit,quantite,categorie,dateajout,dateexpiration,prix);
bool test1=MP.MatierePremiereExiste(id);
 qDebug() <<test1;
            if(test1==true)
 {
    bool test=MP.modifier();
     qDebug() <<test;
            QMessageBox msgBox;
            if(test)
            {
                ui->tab_MatierePremiere->setModel(MP.afficher());
                 clear();
                msgBox.setText("Modification avec Succes.");
               msgBox.exec();
            }

            else
            {
            msgBox.setText("!!Echec de modification!!");
          msgBox.exec();
            }
    }

            else
            {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("MatierePremiere n'existe pas pour modifier !\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }


    }

}

void MainWindow::on_pb_supprimerM_clicked()
{
 MatierePremiere MP;
 MP.setId(ui->le_IDm_supp->text().toInt());
 bool test1=MP.MatierePremiereExiste(MP.getId());

             if(test1==true)
  {
    bool test=MP.supprimer(MP.getId());
    QMessageBox msgBox;
    if(test)
    {
   msgBox.setText("Suppression avec succes.");
    ui->tab_MatierePremiere->setModel(MP.afficher());
   clear();
    }
   else
    msgBox.setText("!!Echec de suppression!!");
   msgBox.exec();

  }
             else
             {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Matiere Premiere n'existe pas !\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

             }

}
