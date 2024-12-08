#include "senario.h"
#include "ui_senario.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QKeyEvent>
#include <QSerialPortInfo>

senario::senario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::senario),
    A(new Arduino())
{
    ui->setupUi(this);
    E.updateTableView();

    if (A->getserial()->isOpen()) {
        qDebug() << "Arduino déjà connecté.";
    } else {
        int ret = A->connect_arduino();
        switch (ret) {
            case 0:
                qDebug() << "Arduino connecté sur :" << A->getarduino_port_name();
                break;
            case 1:
                qDebug() << "Arduino détecté mais non connecté.";
                break;
            case -1:
                qDebug() << "Arduino non disponible.";
                break;
        }
    }

    connect(A->getserial(), &QSerialPort::readyRead, this, &senario::update_label);

}

senario::~senario()
{
    if (A->getserial()->isOpen()) {
        A->close_arduino();
    }

    delete ui;
    delete A;
}

void senario::keyPressEvent(QKeyEvent *event)
{
    if (event->text().length() > 0) {
        scannedCode += event->text();
        scannedCode = scannedCode.trimmed();

        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            if (!scannedCode.isEmpty()) {
                processBarcode(scannedCode);
                scannedCode.clear();
            }
        }
    }
    QDialog::keyPressEvent(event);
}

void senario::processBarcode(const QString &code)
{
    bool ok;
    int scannedId = code.toInt(&ok);

    QString cmdMarker = "C:\\CanPark>";
    QString topMessage = "Qt [version 5.9.9]\n(c) Can Parks Corporation. Tous droits réservés.\n\n";
    QString newMessage;

    if (!ok) {
        newMessage = QString("%1 Erreur: Code %2 invalide").arg(cmdMarker).arg(code);
        ui->label->setText(topMessage % newMessage % "\n");
        A->write_to_arduino("Code invalide\n");
        return;
    }

    if (!Es.rechercherParId(scannedId)) {
        newMessage = QString("%1 Erreur: ID %2 introuvable").arg(cmdMarker).arg(scannedId);
        ui->label->setText(topMessage % newMessage % "\n");
        A->write_to_arduino("Introuvable\n");
        return;
    }

    QString nom = Es.getNomById(scannedId);
    QString prenom = Es.getPrenomById(scannedId);
    float a, b;

    if (Es.rechercherParId1(scannedId)) {
        // Client fidèle : réduction de prix
        Es.setPriceReducedBy10Percent(scannedId, a, b);
        E.updateTableView();

        newMessage = QString("%1 ID: %2, Nom: %3, Prenom: %4\nPrix avant: %5, Prix après: %6 avec succès")
                      .arg(cmdMarker)
                      .arg(scannedId)
                      .arg(nom)
                      .arg(prenom)
                      .arg(a, 0, 'f', 2)
                      .arg(b, 0, 'f', 2);

        A->write_to_arduino(QString("%1 -> %2")
                               .arg(a, 0, 'f', 2)
                               .arg(b, 0, 'f', 2)
                               .toUtf8());
    } else {
        // Client non fidèle
        a=Es.getPrixById(scannedId);
        newMessage = QString("%1 ID: %2, Nom: %3, Prenom: %4\nn'est pas un client fidèle")
                      .arg(cmdMarker)
                      .arg(scannedId)
                      .arg(nom)
                      .arg(prenom);

        A->write_to_arduino(QString("Le prix est %1")
                               .arg(a, 0, 'f', 2)
                               .toUtf8());
    }

    // Mise à jour de l'interface utilisateur
    ui->label->setText(topMessage % newMessage % "\n");
    ui->label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}




// Mettre à jour l'étiquette à partir des données Arduino
void senario::update_label()
{
    QByteArray rawData = A->read_from_arduino();
    QString data = QString::fromUtf8(rawData).trimmed();

    if (!data.isEmpty()) {
        processBarcode(data);
    }
}

void senario::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Vérifier si la connexion Arduino est déjà ouverte
    if (!A->getserial()->isOpen()) {
        // Vérifier la disponibilité du port avant de se connecter
        QString port = A->getarduino_port_name();
        bool portAvailable = false;

        for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
            if (info.portName() == port) {
                portAvailable = true;
                break;
            }
        }

        if (portAvailable) {
            int ret = A->connect_arduino();
            switch (ret) {
                case 0:
                    qDebug() << "Arduino connecté sur :" << A->getarduino_port_name();
                    break;
                case 1:
                    qDebug() << "Arduino détecté mais non connecté.";
                    break;
                case -1:
                    qDebug() << "Arduino non disponible.";
                    break;
            }
        } else {
            qDebug() << "Port série non disponible.";
        }
    }
}
