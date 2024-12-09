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

public:
    Client();
    Client(int id, QString nom, QString prenom, QString email, QString type_cli, QString produit, int tel, float quantite, QDate date);

    int getId() { return id; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getEmail() { return email; }
    QString getTypeCli() { return type_cli; }
    QString getProduit() { return produit; }
    int getTel() { return tel; }
    float getQuantite() { return quantite; }
    QDate getDate() { return date; }

    void setId(int i) { id = i; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setEmail(QString e) { email = e; }
    void setTypeCli(QString t) { type_cli = t; }
    void setProduit(QString pr) { produit = pr; }
    void setTel(int t) { tel = t; }
    void setQuantite(float q) { quantite = q; }
    void setDate(QDate d) { date = d; }
    bool checkIfExists(int id);

    bool ajouter();
    QSqlTableModel* afficher();
    bool supprimer(int);
    bool supprimerTous();
    void countLoyalAndNonLoyalClients(int &loyalClients, int &nonLoyalClients);
};


#endif // CLIENT_H
