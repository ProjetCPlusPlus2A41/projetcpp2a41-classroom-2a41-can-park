#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    Connection();
    bool createconnect();
    void closeConnection();
};
#endif // CONNECTION_H
