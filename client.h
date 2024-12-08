#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlTableModel>
#include<QDate>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QDate>
#include <QDebug>
#include <QSqlError>

class Client
{
private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString type_cli;
    QString produit;
    int tel;
    float quantite;
    QDate date;
float prix;
public:
    Client();
    Client(int id, QString nom, QString prenom, QString email, QString type_cli, QString produit, int tel, float quantite, QDate date,float prix);


    bool checkIfExists(int id);
    bool rechercherParId(int id);
    bool rechercherParId1(int id);
    float getPrixById(int id);

    QString getNomById(int id);
        QString getPrenomById(int id);
    bool ajouter();
    QSqlTableModel* afficher();
    bool supprimer(int);
    bool supprimerTous();
    void countLoyalAndNonLoyalClients(int &loyalClients, int &nonLoyalClients);
    bool setPriceReducedBy10Percent(int id,float &,float &);


};


#endif // CLIENT_H
