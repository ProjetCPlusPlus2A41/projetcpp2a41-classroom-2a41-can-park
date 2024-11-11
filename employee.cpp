#include "employee.h"
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>

// Default constructor
employee::employee() {
    ide = 0;
    nome = "";
    emaile = "";
    numc = "";
    salairec = 0.0;
    postec = "";
    datec = QDate::currentDate();
}

// Parameterized constructor
employee::employee(int ide, QString nome, QString emaile, QString numc, float salairec, QString postec, QDate datec) {
    this->ide = ide;
    this->nome = nome;
    this->emaile = emaile;
    this->numc = numc;
    this->salairec = salairec;
    this->postec = postec;
    this->datec = datec;
}

// Method to display the employee list
QSqlTableModel* employee::afficher() {
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("EMPLOYEE");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Contact Number"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salary"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Position"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date of Employment"));

    return model;
}

// Method to add a new employee
bool employee::ajouter() {
    QSqlQuery query;

    // Convert numeric and date values to strings for binding
    QString salairecConvertit = QString::number(salairec, 'f', 2); // Convert double to QString with 2 decimal places
    QString datecConvertit = datec.toString("yyyy-MM-dd"); // Format QDate to string
    QString res = QString::number(ide); // Convert double to QString with 2 decimal places

    // Prepare the insertion query
    query.prepare("INSERT INTO EMPLOYEE (IDE, NOME, EMAILE, NUMC, SALAIREC, POSTEC, DATEC) "
                  "VALUES (:ide, :nome, :emaile, :numc, :salairec, :postec, TO_DATE(:datec, 'YYYY-MM-DD'))");

    // Bind values with conversions
    query.bindValue(":ide", res);  // Directly bind ide as an integer
    query.bindValue(":nome", nome);
    query.bindValue(":emaile", emaile);
    query.bindValue(":numc", numc);
    query.bindValue(":salairec", salairecConvertit);
    query.bindValue(":postec", postec);
    query.bindValue(":datec", datecConvertit);

    return query.exec();
}

// Method to delete an employee by ID
bool employee::supprimer(int ide) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE IDE = :ide");
    query.bindValue(":ide", ide);

    return query.exec();
}
