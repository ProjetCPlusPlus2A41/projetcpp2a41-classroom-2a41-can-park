#ifndef PRODUIT_H
#define PRODUIT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlTableModel>

class produit
{
public:
    produit();
    produit(int);
    produit(int,int,QString,float);
    int getIdProduit();
    int getQty();
    QString getNom();
    float getPrixUnitaire();
    void setIdproduit(int);
    void setQty(int);
    void setNom(QString);
    void setPrixUnitaire(float);
    //fonction de base
    bool ajouter();
    QSqlTableModel* afficher();
    bool supprimer(int);
private:
    int idProduit, qty;
    QString Nom;
    float prixUnitaire;


};

#endif // PRODUIT_H
