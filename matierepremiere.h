#ifndef MATIEREPREMIERE_H
#define MATIEREPREMIERE_H

#include <QDate>
#include <QString>
#include <QSqlQueryModel>

class MatierePremiere
{
public:
    MatierePremiere();
    MatierePremiere(int,QString,int,QString,QDate,QDate,float);


    int getId();
    int getQuantite();
    float getPrix();
    QDate getDateAjout();
    QDate getDateExpiration();
    QString getProduit();
    QString getCategorie();


    void setId(int);
    void setQuantite(int);
    void setPrix(float);
    void setDateAjout(QDate);
    void setDateExpiration(QDate);
    void setProduit(QString);
    void setCategorie(QString);


 //les methodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool MatierePremiereExiste(int id);
    bool supprimer(int id);

private:
    int id,quantite;
    float prix;
    QDate dateajout,dateexpiration;
    QString produit,categorie;

};

#endif
