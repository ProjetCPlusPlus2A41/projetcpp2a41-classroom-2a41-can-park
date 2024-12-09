#include "livraison.h"

Livraison::Livraison()
{
    id_livraison = 0;
    date_livraison = QDate::currentDate();
    adresse_livraison = "";
    frais_livraison = 0.0;
    type_livraison = "";
    etat_livraison = "";
}

Livraison::Livraison(int id, QDate date, QString adresse, double frais, QString type, QString etat)
{
    this->id_livraison = id;
    this->date_livraison = date;
    this->adresse_livraison = adresse;
    this->frais_livraison = frais;
    this->type_livraison = type;
    this->etat_livraison = etat;
}

bool Livraison::ajouter()
{
    QSqlQuery query;
    QString emConvertit = date_livraison.toString("yyyy-MM-dd");

    QString res = QString::number(id_livraison);
    QString fraisConvertit = QString::number(frais_livraison);

    query.prepare("SELECT COUNT(*) FROM LIVRAISON WHERE ID_LIVRAISON = :id_livraison");
    query.bindValue(":id_livraison", id_livraison);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return false; // ID already exists
    }

    query.prepare("INSERT INTO LIVRAISON (ID_LIVRAISON, DATE_LIVRAISON, ADRESSE_LIVRAISON, FRAIS_LIVRAISON, TYPE_LIVRAISON, ETAT_LIVRAISON) "
                  "VALUES (:id_livraison, TO_DATE(:date_livraison, 'YYYY-MM-DD'), :adresse_livraison, :frais_livraison, :type_livraison, :etat_livraison)");

    query.bindValue(":id_livraison", res);
    query.bindValue(":date_livraison", emConvertit);
    query.bindValue(":adresse_livraison", adresse_livraison);
    query.bindValue(":frais_livraison", fraisConvertit);
    query.bindValue(":type_livraison", type_livraison);
    query.bindValue(":etat_livraison", etat_livraison);

    return query.exec();
}

bool Livraison::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM LIVRAISON WHERE ID_LIVRAISON = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlTableModel* Livraison::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("LIVRAISON");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Livraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Livraison"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Frais Livraison"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type Livraison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat Livraison"));

    return model;
}
