#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>

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
    bool ajouter(const QString &imagePath);
bool idExiste(const QString &id) const;
};

#endif // EQUIPEMENT_H
