#include "matiere.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
matiere::matiere()
{
    idm = 0;
    produitm = "";
    cm = "";
    quantitem = 0.0;
    prixm = 0.0;
    em = QDate::currentDate();
    am = QDate::currentDate();
}

matiere::matiere(int idm, QString produitm, QString cm, float quantitem, float prixm, QDate em, QDate am)
{
    this->idm = idm;
    this->produitm = produitm;
    this->cm = cm;
    this->quantitem = quantitem;
    this->prixm = prixm;
    this->em = em;
    this->am = am;
}

bool matiere::ajouter()
{
    if (em < QDate::currentDate()) {
           QMessageBox::warning(nullptr, "Erreur", "La date d'expiration ne peut pas être dans le passé.");
           return false;  // Empêche l'ajout si la date d'expiration est passée
       }
    QSqlQuery query;
    QString res = QString::number(idm);
    QString quantConvertit = QString::number(quantitem);
    QString prixConvertit = QString::number(prixm);
    QString emConvertit = em.toString("yyyy-MM-dd");
    QString amConvertit = am.toString("yyyy-MM-dd");

    query.prepare("SELECT COUNT(*) FROM MATIERE WHERE idm = :idm");
    query.bindValue(":idm", idm);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return false;  // ID already exists
    }

    query.prepare("INSERT INTO MATIERE (IDM, PRODUITM, CM, QUANTITEM, PRIXM, EM, AM) "
                  "VALUES (:idm, :produitm, :cm, :quantitem, :prixm, TO_DATE(:em, 'YYYY-MM-DD'), TO_DATE(:am, 'YYYY-MM-DD'))");

    query.bindValue(":idm", res);
    query.bindValue(":produitm", produitm);
    query.bindValue(":cm", cm);
    query.bindValue(":quantitem", quantConvertit);
    query.bindValue(":prixm", prixConvertit);
    query.bindValue(":em", emConvertit);
    query.bindValue(":am", amConvertit);

    return query.exec();
}

bool matiere::supprimer(int idm)
{
    QSqlQuery query;
    query.prepare("DELETE FROM MATIERE WHERE idm = :idm");
    query.bindValue(":idm", idm);
    return query.exec();
}

QSqlTableModel* matiere::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("MATIERE");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Expiry  Date"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Entry  Date"));

    return model;
}
bool matiere::verifierExpiration()
{
    QSqlQuery query;
    query.prepare("SELECT IDM, PRODUITM, EM FROM MATIERE"); // Fetch all products from the database
    QDate currentDate = QDate::currentDate();
    QDate nextDay = currentDate.addDays(1);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'expiration" << query.lastError();
        return false;
    }

    QString message;
    bool found = false;

    while (query.next()) {
        int idm = query.value("IDM").toInt();
        QString produitm = query.value("PRODUITM").toString();
        QDate expirationDate = query.value("EM").toDate();

        // Validate the expiration date
        if (!expirationDate.isValid()) {
            qDebug() << "Date invalide pour le produit ID:" << idm;
            continue;
        }

        // Compare the expiration date dynamically for each product
        if (expirationDate <= currentDate) {
            // If the product has already expired
            found = true;
            message.append(QString("Le produit '%1' (ID: %2) a expiré (Date: %3)!\n")
                           .arg(produitm)
                           .arg(idm)
                           .arg(expirationDate.toString("dd/MM/yyyy")));
        } else if (expirationDate == nextDay) {
            // If the product expires tomorrow
            found = true;
            message.append(QString("Le produit '%1' (ID: %2) expire demain (Date: %3).\n")
                           .arg(produitm)
                           .arg(idm)
                           .arg(expirationDate.toString("dd/MM/yyyy")));
        }
    }

    // Display all the collected notifications in a single message box
    if (found) {
        QMessageBox::information(nullptr, "Produits Expirés ou Expirant",
                                  "Produits concernés:\n\n" + message);
    } else {
        QMessageBox::information(nullptr, "Aucune Expiration",
                                  "Aucun produit n'a expiré ou ne va expirer demain.");
    }

    return found;
}





