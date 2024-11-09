#include "client.h"

Client::Client()
{
    nom = "";
    prenom = "";
    id = 0;
    email = "";
    type_cli = "";
    produit = "";
    tel = 0;
    quantite = 0.0;
    date = QDate::currentDate();
}

Client::Client(int id, QString nom, QString prenom, QString email, QString type_cli, QString produit, int tel, float quantite, QDate date)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->type_cli = type_cli;
    this->produit = produit;
    this->tel = tel;
    this->quantite = quantite;
    this->date = date;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString telconvetit = QString::number(tel);  // If tel is numeric, keep it as a number
    QString quanconvertit = QString::number(quantite);
    QString dateconvertit = date.toString("yyyy-MM-dd");  // Standard date format

    // Check if the ID already exists in the CLIENT table
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return false;
    }

    // Insert into CLIENT table
    query.prepare("INSERT INTO CLIENT (ID, NOM, PRENOM, EMAIL, TYPE_CLI, PRODUIT, TEL, QUANTITE, DATE_CREATION) "
                  "VALUES (:id, :nom, :prenom, :email, :type_cli, :produit, TO_NUMBER(:tel), :quantite, TO_DATE(:date, 'YYYY-MM-DD'))");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":type_cli", type_cli);
    query.bindValue(":produit", produit);
    query.bindValue(":tel", telconvetit);  // Pass tel as a numeric value
    query.bindValue(":quantite", quanconvertit);
    query.bindValue(":date", dateconvertit);  // Ensure date is passed as a string in proper format

    return query.exec();
}



bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlTableModel* Client::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("CLIENT");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Set headers for columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type Client"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date"));

    return model;
}

bool Client::supprimerTous()
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT");
    return query.exec();
}
