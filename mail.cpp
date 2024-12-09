#include "mail.h"
#include "ui_mail.h"
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>

mail::mail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mail)
{
    ui->setupUi(this);
  connect(ui->envoi, &QPushButton::clicked, this, &mail::sendEmailFromUI);
    connect(ui->cancel, &QPushButton::clicked, this, &mail::close);
    ui->objectif->setPlaceholderText("Objet");
    ui->message->setPlaceholderText("Rédigez votre message");
     ui->tableView->setVisible(false);
     connect(ui->piece, &QPushButton::clicked, this, &mail::selectAttachmentFile);

    connect(ui->envoi3, &QPushButton::clicked, this, [this]() {
        if (ui->tableView->isVisible()) {
            ui->tableView->setVisible(false);
        } else {
            ui->tableView->setModel(Es.afficher());
            ui->tableView->setVisible(true);
        }
    });
}

mail::~mail()
{
    delete ui;
}

void mail::sendEmailFromUI() {
    bool ok;
    QSqlQuery query;
    int id = ui->idemail->text().toInt(&ok);
    QString subject = ui->objectif->text();
    QString message = ui->message->toPlainText();

    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide !");
        return;
    }

    Client client;

    if (client.checkIfExists(id)) {
        query.prepare("SELECT EMAIL FROM CLIENT WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            QString toEmail = query.value(0).toString();
            sendEmail(toEmail, subject, message);
        } else {
            QMessageBox::warning(this, "Erreur", "Aucun email trouvé pour cet ID !");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Le code à barre n'existe pas pour cet ID !");
    }
}


void mail::sendEmail(const QString &toEmail, const QString &subject, const QString &message) {
    QString smtpServer = "smtp://smtp.gmail.com:587";
    QString email = "yassinebensaad567@gmail.com";
    QString appPassword = "rgki mwew mtbq momy";

    QStringList curlArgs;
    curlArgs << "-v"
             << "--ssl-reqd"
             << "--mail-from" << email
             << "--mail-rcpt" << toEmail
             << "--user" << email + ":" + appPassword
             << "--url" << smtpServer
             << "--upload-file" << "-";

    QByteArray emailContent;
    emailContent.append("From: " + email + "\n");
    emailContent.append("To: " + toEmail + "\n");
    emailContent.append("Subject: " + subject + "\n");
    emailContent.append("Content-Type: multipart/mixed; boundary=\"boundary\"\n\n");

    emailContent.append("--boundary\n");
    emailContent.append("Content-Type: text/plain; charset=UTF-8\n\n");
    emailContent.append(message + "\n\n");

    if (!attachmentFilePath.isEmpty()) {
        QFile file(attachmentFilePath);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray fileData = file.readAll().toBase64();
            QString fileName = QFileInfo(file).fileName();
            file.close();

            emailContent.append("--boundary\n");
            emailContent.append("Content-Type: application/octet-stream\n");
            emailContent.append("Content-Disposition: attachment; filename=\"" + fileName + "\"\n");
            emailContent.append("Content-Transfer-Encoding: base64\n\n");
            emailContent.append(fileData + "\n\n");
        }
    }

    emailContent.append("--boundary--\n");

    QProcess *process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start("curl", curlArgs);
    process->write(emailContent);
    process->closeWriteChannel();
    process->waitForFinished();

    if (process->exitStatus() == QProcess::NormalExit) {
        ui->label->setText("Email sent successfully!");
        QTimer::singleShot(5000, this, [this]() { ui->label->setText(""); });
    } else {
        ui->label->setText("Failed to send email.");
    }

    process->deleteLater();
}

void mail::selectAttachmentFile() {
    attachmentFilePath = QFileDialog::getOpenFileName(this, "Select Attachment", "", "All Files (*.*)");
    if (!attachmentFilePath.isEmpty()) {
        ui->label->setText("Attachment selected: " + attachmentFilePath);
    }
}

