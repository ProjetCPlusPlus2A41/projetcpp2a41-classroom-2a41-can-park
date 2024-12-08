#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>

class produit
{
private:
    int idt;
    QString nomt;
    float prixt,quantitet;
public:
    produit();
    produit(int idt,QString nomt,float prixt,int quantitet);
public slots:
    // Methods for handling the database operations
    QSqlTableModel* afficher();   // Display the employee list in a table
    bool supprimer(int idt);      // Delete an employee by ID
    bool ajouter();
};

#endif // PRODUIT_H
