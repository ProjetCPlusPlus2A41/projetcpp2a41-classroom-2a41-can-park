#ifndef MAIL_H
#define MAIL_H

#include <QDialog>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QNetworkRequest>

namespace Ui {
class mail;
}

class mail : public QDialog
{
    Q_OBJECT

public:
    explicit mail(QWidget *parent = nullptr);
    ~mail();

private slots:
    //void sendEmailToClient();
    //bool sendEmail(const QString &email, const QString &message);

private:
    Ui::mail *ui;
    //QNetworkAccessManager *networkManager; // Network manager for sending requests
};

#endif // MAIL_H
