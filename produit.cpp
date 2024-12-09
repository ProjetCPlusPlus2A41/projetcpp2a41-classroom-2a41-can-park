#include "produit.h"

produit::produit()
{
idt=0;
prixt=0;
nomt="";
quantitet=0;
}
produit::produit(int idt,QString nomt,float prixt,int quantitet)
{
this->idt=idt;
this->prixt=prixt;
this->nomt=nomt;
this->quantitet=quantitet;
}
bool produit::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(idt);
    QString quantConvertit = QString::number(quantitet);
    QString prixConvertit = QString::number(prixt);


    query.prepare("SELECT COUNT(*) FROM PRODUIT WHERE idt = :idt");
    query.bindValue(":idt", idt);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return false;  // ID already exists
    }

    query.prepare("INSERT INTO PRODUIT (IDT, NOMT, QUANTITET, PRIXT) "
                     "VALUES (:idt, :nomt, :quantitet, :prixt)");

       query.bindValue(":idt", res);
       query.bindValue(":nomt", nomt);
       query.bindValue(":quantitet", quantConvertit);
       query.bindValue(":prixt", prixConvertit);


    return query.exec();
}
bool produit::supprimer(int idt)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUIT WHERE idt = :idt");
    query.bindValue(":idt", idt);
    return query.exec();
}

QSqlTableModel* produit::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("PRODUIT");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nb Boite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix Unitaire"));


    return model;
}
