#ifndef LIVRAISON_H
#define LIVRAISON_H
#include <QString>
#include <QSqlQueryModel>
#include <iostream>

using namespace std;

class Livraison
{
public:
    int id_livraison;
    QString adresse_livraison;
    QString date_livraison;
    double frais_livraison;
    QString type_livraison;
    QString etat_livraison;

    Livraison();
    Livraison(int, QString, QString, double, QString, QString);

    bool ajouter();

    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* rechercher(int id, const QString& adresse, const QString& etat, const QString& type, double frais, const QString& date);

};

#endif // LIVRAISON_H

