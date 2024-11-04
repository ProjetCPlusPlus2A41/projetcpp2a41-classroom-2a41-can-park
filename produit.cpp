#include "produit.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructors
produit::produit() {}

produit::produit(int idProduit) {
    this->idProduit = idProduit;
}

produit::produit(int idProduit, int qty, QString Nom, float prixUnitaire) {
    this->idProduit = idProduit;
    this->prixUnitaire = prixUnitaire;
    this->qty = qty;
    this->Nom = Nom;
}

// Getters
int produit::getIdProduit() {
    return this->idProduit;
}

int produit::getQty() {
    return this->qty;
}

QString produit::getNom() {
    return this->Nom;
}

float produit::getPrixUnitaire() {
    return this->prixUnitaire;
}

// Setters
void produit::setIdproduit(int id) {
    this->idProduit = id;
}

void produit::setQty(int quantity) {
    this->qty = quantity;
}

void produit::setNom(QString name) {
    this->Nom = name;
}

void produit::setPrixUnitaire(float prix) {
    this->prixUnitaire = prix;
}

// Methods
bool produit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (IDPRODUIT, NOM, PRIXUNITAIRE, QTY) "
                  "VALUES (:idProduit, :Nom, :prixUnitaire, :qty)");

    query.bindValue(":idProduit", idProduit);
    query.bindValue(":Nom", Nom);
    query.bindValue(":prixUnitaire", prixUnitaire);
    query.bindValue(":qty", qty);

    if (!query.exec()) {
        qDebug() << "Error adding produit:" << query.lastError().text();
        return false;
    }
    return true;
}


bool produit::supprimer(int code) {
    QSqlQuery query;
    QString res = QString::number(code);

    query.prepare("DELETE FROM PRODUITS WHERE idProduit = :id");
    query.bindValue(":id", res);

    return query.exec();
}

QSqlTableModel* produit::afficher() {
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("PRODUITS");
    model->setEditStrategy(QSqlTableModel::OnFieldChange); // Met à jour la base de données à chaque modification de cellule
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixUnitaire"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));

    return model;
}
