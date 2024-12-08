#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>

class employee
{
    // Employee fields
    int ide;
    QString nome, emaile, numc, postec,prenome;
    float salairec;
    QDate datec;

public:
    // Constructors
    employee();
    employee(int ide,QString prenome,QString nome, QString emaile, QString numc, float salairec, QString postec, QDate datec);

public slots:
    // Methods for handling the database operations
    QSqlTableModel* afficher();   // Display the employee list in a table
    bool supprimer(int ide);      // Delete an employee by ID
    bool ajouter();               // Add a new employee
};

#endif // EMPLOYEE_H
