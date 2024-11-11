#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("CPP_project");
db.setUserName("Malek");
db.setPassword("oracle");

if (db.open())
test=true;

    return  test;
}
