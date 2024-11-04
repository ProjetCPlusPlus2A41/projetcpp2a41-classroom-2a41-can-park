#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet2A");//inserer le nom de la source de données
    db.setUserName("souhail");//inserer nom de l'utilisateur
    db.setPassword("1111");//inserer mot de passe de cet utilisateur
    qDebug() << "Username :" << db.userName();
    qDebug() << "password :" << db.password();
    if (db.open()){

        test=true;
    } else {
        qDebug() << "last error" << db.lastError();
    }
    return  test;
}
