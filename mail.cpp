#include "mail.h"
#include "ui_mail.h"
#include "client.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
//#include <QSslSocket>
#include <QDebug>

mail::mail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mail)
{
    ui->setupUi(this);
    //connect(ui->envoi, &QPushButton::clicked, this, &mail::sendEmailToClient);
    connect(ui->cancel, &QPushButton::clicked, this, &mail::close);
}

mail::~mail()
{
    delete ui;
}

/*void mail::sendEmailToClient() {
    QSqlQuery query;
    QString email;
    int clientId = ui->idemail->text().toInt();
    QString message = ui->message->toPlainText();

    // Step 1: Retrieve the client's email address using their ID
    query.prepare("SELECT EMAIL FROM CLIENT WHERE ID = :clientId");
    query.bindValue(":clientId", clientId);

    if (query.exec() && query.next()) {
        email = query.value(0).toString();
    } else {
        QMessageBox::warning(this, "Error", "Client ID not found.");
        return;
    }

    // Optional confirmation
    QMessageBox::information(this, "Compose Email",
                             "To: " + email + "\nMessage:\n" + message);

    // Send the email
    bool success = sendEmail(email, message);

    if (success) {
        QMessageBox::information(this, "Success", "Email sent to " + email);
    } else {
        QMessageBox::warning(this, "Failure", "Failed to send email.");
    }
}

bool mail::sendEmail(const QString &email, const QString &message) {
    QString smtpServer = "smtp.gmail.com";
    QSslSocket socket;
    int smtpPort = 587;  // Port 587 supports STARTTLS, but you can use 465 for implicit SSL

    // Connect to the server with SSL
    socket.connectToHostEncrypted(smtpServer, smtpPort);

    QString username = "yassinebensaad567.com"; // Replace with your email
    QString appPassword = "rgki mwew mtbq momy";// Replace with your app password

    if (!socket.waitForEncrypted(10000)) {
        qDebug() << "Failed to establish encrypted connection: " << socket.errorString();
        return false;
    }

    qDebug() << "Connected, sending EHLO";
    socket.write("EHLO localhost\r\n");
    socket.waitForReadyRead();
    qDebug() << "EHLO response: " << socket.readAll();

    // Authenticate with base64 encoding
    socket.write("AUTH LOGIN\r\n");
    socket.waitForReadyRead();
    socket.write(username.toUtf8().toBase64() + "\r\n");
    socket.waitForReadyRead();
    socket.write(appPassword.toUtf8().toBase64() + "\r\n");
    socket.waitForReadyRead();

    qDebug() << "Authentication responses received.";

    // Sending the email content
    socket.write("MAIL FROM:<" + username.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    socket.write("RCPT TO:<" + email.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    socket.write("DATA\r\n");
    socket.waitForReadyRead();

    QString mailData = "To: " + email + "\r\n";
    mailData += "From: " + username + "\r\n";
    mailData += "Subject: Message from Qt Application\r\n\r\n";
    mailData += message + "\r\n.\r\n";  // End the message with a period on a new line

    socket.write(mailData.toUtf8());
    socket.waitForReadyRead();

    socket.write("QUIT\r\n");
    socket.waitForReadyRead();

    socket.disconnectFromHost();
    return true;
}*/
