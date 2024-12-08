#include "equipement.h"

equipement::equipement()
{
    id_eq=0;
    nom_eq="";
    type_eq="";
    etat_eq="";
    nb_eq=0;
    cout_eq=0;
}
equipement::equipement(QString nom_eq, QString type_eq,QString etat_eq,int id_eq, int nb_eq, float cout_eq )
{
    this->id_eq=id_eq;
    this->nom_eq=nom_eq;
    this->type_eq=type_eq;
    this->etat_eq=etat_eq;
    this->nb_eq=nb_eq;
    this->cout_eq=cout_eq;
}

bool equipement::ajouter(){
    QSqlQuery query;
    QString nbconvetit = QString::number(nb_eq);  // If tel is numeric, keep it as a number
    QString coutconvertit = QString::number(cout_eq);
    QString res = QString::number(id_eq);

    query.prepare("INSERT INTO EQUIPEMENT (ID_EQ, NOM_EQ, TYPE_EQ, ETAT_EQ, NB_EQ, COUT_EQ) "
                  "VALUES (:id_eq, :nom_eq, :type_eq, :etat_eq, :nb_eq, :cout_eq)");

    query.bindValue(":id_eq", res);
    query.bindValue(":nom_eq", nom_eq);
    query.bindValue(":type_eq", type_eq);
    query.bindValue(":etat_eq", etat_eq);
    query.bindValue(":nb_eq", nbconvetit);
    query.bindValue(":cout_eq", coutconvertit);
     return query.exec();
}

QSqlTableModel* equipement::afficher(){

    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("EQUIPEMENT");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nb"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cout"));
    return model;
}

bool equipement::supprimer(int id_eq){
    QSqlQuery query;
    QString res =QString::number(id_eq);

    query.prepare("Delete from EQUIPEMENT where ID_EQ= :id_eq");
    query.bindValue(":id_eq",res);

    return  query.exec();
}
