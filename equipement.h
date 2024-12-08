#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
class equipement
{
    QString nom_eq, type_eq, etat_eq;
    int id_eq, nb_eq;
    float cout_eq;
public:
    equipement();
    equipement(QString nom_eq, QString type_eq,QString etat_eq,int id_eq, int nb_eq, float cout_eq );
public slots:

    QSqlTableModel * afficher();
    bool supprimer(int id_eq);
    bool ajouter();

};

#endif // EQUIPEMENT_H
