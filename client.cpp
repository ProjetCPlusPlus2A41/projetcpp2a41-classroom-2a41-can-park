#include "client.h"

Client::Client()
{
    nom = "";
    prenom = "";
    id = 0;
    email = "";
    type_cli = "";
    produit = "";
    tel = 0;
    quantite = 0.0;
    prix=0.0;
    date = QDate::currentDate();

}

Client::Client(int id, QString nom, QString prenom, QString email, QString type_cli, QString produit, int tel, float quantite, QDate date,float prix)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->type_cli = type_cli;
    this->produit = produit;
    this->tel = tel;
    this->quantite = quantite;
    this->date = date;
    this->prix = prix;

}

bool Client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString telconvetit = QString::number(tel);  // If tel is numeric, keep it as a number
    QString quanconvertit = QString::number(quantite);
    QString dateconvertit = date.toString("yyyy-MM-dd");  // Standard date format
    QString prixConvertit = QString::number(prix);

    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return false;
    }

    query.prepare("INSERT INTO CLIENT (ID, NOM, PRENOM, EMAIL, TYPE_CLI, PRODUIT, TEL, QUANTITE, DATE_CREATION,PRIX) "
                  "VALUES (:id, :nom, :prenom, :email, :type_cli, :produit, TO_NUMBER(:tel), :quantite, TO_DATE(:date, 'YYYY-MM-DD'),:prix)");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":type_cli", type_cli);
    query.bindValue(":produit", produit);
    query.bindValue(":tel", telconvetit);
    query.bindValue(":quantite", quanconvertit);
    query.bindValue(":date", dateconvertit);
    query.bindValue(":prix", prixConvertit);

    return query.exec();
}



bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlTableModel* Client::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("CLIENT");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type Client"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Prix"));


    return model;
}

bool Client::supprimerTous()
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT");
    return query.exec();
}
void Client::countLoyalAndNonLoyalClients(int &loyalClients, int &nonLoyalClients)
{
    QSqlQuery query;

    query.prepare(R"(
        SELECT
            COUNT(CASE WHEN QUANTITE >= 100 THEN 1 END) AS loyal_clients,
            COUNT(CASE WHEN QUANTITE < 100 THEN 1 END) AS non_loyal_clients
        FROM CLIENT
    )");

    if (query.exec()) {
        if (query.next()) {
            loyalClients = query.value("loyal_clients").toInt();
            nonLoyalClients = query.value("non_loyal_clients").toInt();
        } else {
            loyalClients = 0;
            nonLoyalClients = 0;
        }
    } else {

        loyalClients = 0;
        nonLoyalClients = 0;
    }
}
bool Client::checkIfExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next() && query.value(0).toInt() > 0) {
        return true;
    } else {
        return false;
    }
}
bool Client::setPriceReducedBy10Percent(int id,float &a,float &b) {
    QSqlQuery query;
    query.prepare("SELECT prix FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error fetching current price:" << query.lastError();
        return false;
    }

    if (query.next()) {
        // Get the current price
        double currentPrice = query.value(0).toDouble();
a=currentPrice;
        double reducedPrice = currentPrice * 0.90;
b=reducedPrice;
        // Update the price in the database
        query.prepare("UPDATE CLIENT SET prix = :prix WHERE id = :id");
        query.bindValue(":prix", reducedPrice);
        query.bindValue(":id", id);

        if (!query.exec()) {
            qDebug() << "Error updating price:" << query.lastError();
            return false;
        }

        qDebug() << "Price for student with ID" << id << "reduced to" << reducedPrice;
        return true;
    } else {
        qDebug() << "No student found with ID" << id;
        return false;
    }
}
bool Client::rechercherParId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        return query.next();
    }
    return false;
}
QString Client::getNomById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT nom FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value("nom").toString();
    } else {
        qDebug() << "Erreur lors de la récupération du nom pour l'ID" << id << ":" << query.lastError().text();
        return QString();
    }
}
float Client::getPrixById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT prix FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value("prix").toFloat();
    } else {
        qDebug() << "Erreur lors de la récupération du nom pour l'ID" << id << ":" << query.lastError().text();
        return float();
    }
}
QString Client::getPrenomById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT prenom FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value("prenom").toString();
    } else {
        qDebug() << "Erreur lors de la récupération du prénom pour l'ID" << id << ":" << query.lastError().text();
        return QString();
    }
}
bool Client::rechercherParId1(int id)
{
    QSqlQuery query;
    query.prepare("SELECT quantite FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            float quantite = query.value(0).toInt();

            if (quantite > 100) {
                return true;
            }
        }
    }

    return false;
}

