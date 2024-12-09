#ifndef LIVRAISON_H
#define LIVRAISON_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>

class Livraison
{
private:
    int id_livraison;
       QDate date_livraison;
       QString adresse_livraison;
       double frais_livraison;
       QString type_livraison;
       QString etat_livraison;
public:
    Livraison();
    Livraison(int id, QDate date, QString adresse, double frais, QString type, QString etat);
    QSqlTableModel* afficher();       // Display all livraison records
        bool supprimer(int idl);           // Delete a livraison by ID
        bool ajouter();
};

#endif // LIVRAISON_H
