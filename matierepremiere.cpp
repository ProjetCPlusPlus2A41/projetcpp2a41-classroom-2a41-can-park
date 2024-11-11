#include "matierepremiere.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlError>


MatierePremiere::MatierePremiere()
{
    id = 0;
    quantite = 0;
    prix = 0.0f;
    dateajout = QDate::currentDate(); // use QDate::currentDate() if you want today's date
    dateexpiration = QDate::currentDate(); // use QDate::currentDate() if you want today's date
    produit = "";
    categorie = "";
}

MatierePremiere::MatierePremiere(int id,QString produit,int quantite,QString categorie,QDate dateajout,QDate dateexpiration,float prix)
{
    this->id=id;
    this->produit=produit;
    this->quantite=quantite;
    this->categorie=categorie;
    this->dateajout=dateajout;
    this->dateexpiration=dateexpiration;
    this->prix=prix;
}

// Getters
int MatierePremiere::getId()  { return id;}

int MatierePremiere::getQuantite()  { return quantite;}

float MatierePremiere::getPrix()  { return prix;}

QDate MatierePremiere::getDateAjout()  { return dateajout;}

QDate MatierePremiere::getDateExpiration()  { return dateexpiration;}

QString MatierePremiere::getProduit()  { return produit;}

QString MatierePremiere::getCategorie()  {return categorie;}

// Setters
void MatierePremiere::setId(int newId) {id = newId;}

void MatierePremiere::setQuantite(int newQuantite) {quantite = newQuantite;}

void MatierePremiere::setPrix(float newPrix) {prix = newPrix;}

void MatierePremiere::setDateAjout( QDate newDateAjout) {
    if (newDateAjout.isValid()) {
        dateajout = newDateAjout;
    }
}

void MatierePremiere::setDateExpiration( QDate newDateExpiration) {
    if (newDateExpiration.isValid()) {
        dateexpiration = newDateExpiration;
    }
}

void MatierePremiere::setProduit( QString newProduit) { produit = newProduit;}

void MatierePremiere::setCategorie( QString newCategorie) { categorie = newCategorie;}


bool MatierePremiere::ajouter()
{
   QSqlQuery query;

   QString id_string = QString::number(id);
   QString quantite_string = QString::number(quantite);
   QString dateajout_string = dateajout.toString("dd-MMM-yy");
   QString dateexpiration_string = dateexpiration.toString("dd-MMM-yy");
   QString prix_string = QString::number(prix, 'f', 3);  // 'f' is for fixed-point notation, 3 decimal places

   query.prepare("INSERT INTO matierepremiere (id, produit, quantite, categorie, dateajout, dateexpiration, prix) "
                 "VALUES (:id, :produit, :quantite, :categorie, :dateajout, :dateexpiration, :prix)");

   // Bind values using named placeholders
   query.bindValue(":id", id_string);
   query.bindValue(":produit", produit);
   query.bindValue(":quantite", quantite_string);
   query.bindValue(":categorie", categorie);
   query.bindValue(":dateajout", dateajout_string);
   query.bindValue(":dateexpiration", dateexpiration_string);
   query.bindValue(":prix", prix_string);


   return query.exec();
}

QSqlQueryModel* MatierePremiere::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT id, produit, quantite, categorie, TO_CHAR(dateajout, 'DD-Mon-YY'), TO_CHAR(dateexpiration, 'DD-Mon-YY'), prix FROM matierepremiere");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Categorie"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Ajout"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Expiration"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Prix"));

return model;
}

bool MatierePremiere::modifier()
{
   QSqlQuery query;

   QString id_string = QString::number(id);
   QString quantite_string = QString::number(quantite);
   QString dateajout_string = dateajout.toString("dd-MMM-yy");
   QString dateexpiration_string = dateexpiration.toString("dd-MMM-yy");
   QString prix_string = QString::number(prix, 'f', 3);  // 'f' is for fixed-point notation, 3 decimal places

   query.prepare("UPDATE matierepremiere SET id = :id, produit = :produit, quantite = :quantite, categorie = :categorie, "
                 "dateajout = :dateajout, dateexpiration = :dateexpiration, prix = :prix "
                 "WHERE id = :id");  // Assuming id is the unique identifier for the update

   // Bind values using named placeholders
   query.bindValue(":id", id_string);
   query.bindValue(":produit", produit);
   query.bindValue(":quantite", quantite_string);
   query.bindValue(":categorie", categorie);
   query.bindValue(":dateajout", dateajout_string);
   query.bindValue(":dateexpiration", dateexpiration_string);
   query.bindValue(":prix", prix_string);

   if (!query.exec()) {
       qDebug() << "Error: " << query.lastError().text();
       return false;  // Return false if execution failed
   }

   return true;
}


bool MatierePremiere:: MatierePremiereExiste(  int id)
{
   bool exists = false;

   QSqlQuery checkQuery;
   checkQuery.prepare("SELECT id FROM matierepremiere WHERE id=:id");
   checkQuery.bindValue(":id", id);

   if (checkQuery.exec())
   {
       if (checkQuery.next())
       {
           exists = true;
       }
   }
   else
   {
       qDebug() << "Matiere Premiere not found:" << checkQuery.lastError();
   }

   return exists;
}

bool MatierePremiere::supprimer(int id)
{
   QSqlQuery query;
        query.prepare("Delete from matierepremiere where id=:id");
        query.bindValue(0,id);

   return query.exec();
}


