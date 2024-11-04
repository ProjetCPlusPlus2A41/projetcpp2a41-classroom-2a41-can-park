#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QSqlTableModel>


class Etudiant
{
private:
    int id;
    QString nom;
    QString prenom;
public:
    Etudiant();
    Etudiant(int,QString,QString);
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getId(){return id;}
    void setNom( QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setId(int i) { id = i; }
    bool ajouter();
   QSqlTableModel * afficher();
    bool supprimer(int);
    bool supprimerTous();

};

#endif // ETUDIANT_H
