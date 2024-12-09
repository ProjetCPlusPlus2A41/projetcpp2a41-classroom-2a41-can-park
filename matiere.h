#ifndef MATIERE_H
#define MATIERE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QString>
#include <QDate>
class matiere
{
    QString produitm, cm;
    int idm;
    float prixm,quantitem;
    QDate em,am;
public:
    matiere();
    matiere(int id, QString produitm, QString cm,float quantitem,float prixmm ,QDate em,QDate am);
public slots:

    QSqlTableModel * afficher();
    bool supprimer(int id_eq);
    bool ajouter();
};

#endif // MATIERE_H
