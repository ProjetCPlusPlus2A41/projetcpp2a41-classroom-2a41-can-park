#include "rif.h"
#include "ui_rif.h"
#include <QMessageBox>
#include <QTimer>

rif::rif(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rif),
    A(new Arduino) // Instanciation de l'objet Arduino
{
    ui->setupUi(this);
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

    connect(A->getserial(), &QSerialPort::readyRead, this, &rif::readFromArduino);
    connect(ui->cancel, &QPushButton::clicked, this, &rif::close);

}


rif::~rif()
{
    if (A->getserial()->isOpen()) {
        A->close_arduino();
    }
    delete A; // Libération mémoire
    delete ui;
}

void rif::readFromArduino()
{
    QByteArray data = A->read_from_arduino();
    QString uid = QString::fromUtf8(data).trimmed(); // Convertir les données en chaîne

    qDebug() << "UID reçu:" << uid;

    if (!uid.isEmpty())
    {
        if (uid != "/")
        {
            A->code += uid;
        }
        else
        {
            A->code.remove("/"); // Nettoyage
            qDebug() << "UID complet après nettoyage:" << A->code;

            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(RFID) = :code");
            query.bindValue(":code", A->code.toUpper());

            if (query.exec())
            {
                if (query.next())
                {
                    int count = query.value(0).toInt();
                    qDebug() << "Nombre d'entrées trouvées:" << count;

                    if (count > 0) // UID trouvé
                    {
                        QSqlQuery query1;
                        query1.prepare("UPDATE EMPLOYE SET PRESENCE = 'present' WHERE UPPER(RFID) = :code");
                        query1.bindValue(":code", A->code.toUpper());


                        if (query1.exec())
                        {
                            QByteArray byteArray;
                            byteArray.append('O'); // Caractère pour Arduino
                            A->write_to_arduino(byteArray);

                            QMessageBox::information(this, "Succès", "Le employé est présent !");
                            ui->mezen->setIcon(QIcon("C:/Users/haouas/Downloads/porte.png"));
                            QTimer::singleShot(4000, this, [this]() {
                                ui->mezen->setIcon(QIcon("C:/Users/haouas/Downloads/porte-de-chantier.png"));
                            });
                            QSqlQuery query2;
                                          query2.prepare("SELECT NOME, PRENOME FROM EMPLOYE  WHERE UPPER(RFID) = :code");
                                          query2.bindValue(":code", A->code.toUpper());

                                          if (query2.exec()) {
                                              if (query2.next()) {
                                                  QString nom = query2.value("NOME").toString();
                                                  ui->AS->setAlignment(Qt::AlignTop | Qt::AlignLeft);

                                                                          QString prenom = query2.value("PRENOME").toString();

                                                                          // Combine "Mr." with the name and surname
                                                                          QString fullName = "Mr. " + nom + " " + prenom;

                                                                          // Get the current time and format it
                                                                          QString time = QTime::currentTime().toString("hh:mm:ss");

                                                                          // Create the message
                                                                          QString message = fullName + "\n a ouvert la porte à \n" + time;

                                                  ui->AS->setText(message);
                                              }
                                          }


                        }

                    }
                    else // UID non trouvé
                    {
                        QByteArray byteArray;
                        byteArray.append('N');
                        A->write_to_arduino(byteArray);

                        QMessageBox::warning(this, "Erreur", "L'UID n'existe pas !");
                    }
                }
            }
            else
            {
            }

            A->code = ""; // Réinitialisation
        }
    }
}

