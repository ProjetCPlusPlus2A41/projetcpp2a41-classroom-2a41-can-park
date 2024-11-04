#include "etudiant.h"

Etudiant::Etudiant()
{
nom="";
prenom="";
id=0;
}
Etudiant::Etudiant(int id,QString nom,QString prenom){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
}
bool Etudiant::ajouter(){
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("SELECT COUNT(*) FROM ETUDIANT WHERE id = :id");
       query.bindValue(":id", id);
       query.exec();

       if (query.next() && query.value(0).toInt() > 0) {
           return false;
       }
query.prepare("insert into  ETUDIANT (id, nom, prenom) VALUES (:id, :nom, :prenom)");    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

    return query.exec();
}
bool Etudiant::supprimer(int id){
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from ETUDIANT where ID= :id");
    query.bindValue(":id",res);
    return query.exec();

}
QSqlTableModel* Etudiant::afficher() {
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("ETUDIANT");


    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    return model;
}


bool Etudiant::supprimerTous() {
    QSqlQuery query;
    query.prepare("DELETE FROM ETUDIANT");

    return query.exec();
}
