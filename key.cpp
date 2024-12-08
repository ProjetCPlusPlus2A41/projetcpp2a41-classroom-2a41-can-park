#include "key.h"
#include "ui_key.h"
#include <QMessageBox>
#include <QTimer>

key::key(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::key),
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

    connect(A->getserial(), &QSerialPort::readyRead, this, &key::readFromArduino);
    connect(ui->cancel, &QPushButton::clicked, this, &key::close);

}

key::~key()
{
    if (A->getserial()->isOpen()) {
        A->close_arduino();
    }
    delete A;
    delete ui;
}
void key::readFromArduino()
{
    QByteArray data = A->read_from_arduino();  // Read data from Arduino
    QString inputCode = QString::fromUtf8(data).trimmed();  // Ensure there is no partial reading


    if (!inputCode.isEmpty())
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM LIVRAISON WHERE UPPER(ID_LIVRAISON) = :code");
        query.bindValue(":code", inputCode.toUpper());

        if (query.exec()) {
            if (query.next()) {
                int count = query.value(0).toInt();

                if (count > 0) // Code trouvé dans la base de données
                {
                    QByteArray byteArray;
                    byteArray.append("true"); // Send 'true' to Arduino for success
                    A->write_to_arduino(byteArray);
                    QString nom = query.value("ID_LIVRAISON").toString();

                    QMessageBox::information(this, "Succès", "L'ID est valide et trouvé !");
                    ui->mezen->setIcon(QIcon("C:/Users/haouas/Downloads/porte.png"));
                    QTimer::singleShot(4000, this, [this]() {
                        ui->mezen->setIcon(QIcon("C:/Users/haouas/Downloads/porte-de-chantier.png"));
                    });
                    QString message =nom;

                    ui->label->setText(message);
                }
                else {  // Code non trouvé
                    QByteArray byteArray;
                    byteArray.append("false"); // Send 'false' to Arduino for failure
                    A->write_to_arduino(byteArray);

                }
            }
        }
    }
}


