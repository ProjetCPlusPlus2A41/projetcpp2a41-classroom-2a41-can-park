#include "livraison.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <iostream>

using namespace std;

Livraison::Livraison() : id_livraison(0), adresse_livraison(""), date_livraison(""), frais_livraison(0.0), type_livraison(""), etat_livraison("") {}

Livraison::Livraison(int id, QString adresse, QString date, double frais, QString type, QString etat)
{
    id_livraison = id;
    adresse_livraison = adresse;
    date_livraison = date;
    frais_livraison = frais;
    type_livraison = type;
    etat_livraison = etat;
}

bool Livraison::ajouter()
{
    QSqlQuery query;
    // Préparez la requête d'insertion
    query.prepare("INSERT INTO Livraison (id_livraison, date_livraison, adresse_livraison, frais_livraison, type_livraison, etat_livraison) "
                  "VALUES (:id_livraison, :date_livraison, :adresse_livraison, :frais_livraison, :type_livraison, :etat_livraison)");

    // Liez les valeurs
    query.bindValue(":id_livraison", id_livraison);
    query.bindValue(":date_livraison", date_livraison);
    query.bindValue(":adresse_livraison", adresse_livraison);
    query.bindValue(":frais_livraison", frais_livraison);
    query.bindValue(":type_livraison", type_livraison);
    query.bindValue(":etat_livraison", etat_livraison);

    // Exécutez la requête et gérez les erreurs
    if (!query.exec()) {
        cout << "Erreur lors de l'ajout : " << query.lastError().text().toStdString() << endl;
        return false;
    }
    return true;
}


QSqlQueryModel* Livraison::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Livraison");
    return model;
}

bool Livraison::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Livraison WHERE id_livraison = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        cout << "Error deleting record: " << query.lastError().text().toStdString() << endl;
        return false;
    }
    return true;
}
bool Livraison::modifier(int id)
{
    QSqlQuery query;
    QString queryString = "UPDATE Livraison SET ";

    bool firstField = true;
    if (!date_livraison.isEmpty()) {
        queryString += "date_livraison = :date_livraison";
        firstField = false;
    }
    if (!adresse_livraison.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "adresse_livraison = :adresse_livraison";
        firstField = false;
    }
    if (frais_livraison != 0) {
        if (!firstField) queryString += ", ";
        queryString += "frais_livraison = :frais_livraison";
        firstField = false;
    }
    if (!type_livraison.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "type_livraison = :type_livraison";
        firstField = false;
    }
    if (!etat_livraison.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "etat_livraison = :etat_livraison";
    }

    queryString += " WHERE id_livraison = :id_livraison";
    query.prepare(queryString);

    // Bind values only if not empty or zero
    query.bindValue(":id_livraison", id);
    if (!date_livraison.isEmpty()) query.bindValue(":date_livraison", date_livraison);
    if (!adresse_livraison.isEmpty()) query.bindValue(":adresse_livraison", adresse_livraison);
    if (frais_livraison != 0) query.bindValue(":frais_livraison", frais_livraison);
    if (!type_livraison.isEmpty()) query.bindValue(":type_livraison", type_livraison);
    if (!etat_livraison.isEmpty()) query.bindValue(":etat_livraison", etat_livraison);

    if (!query.exec()) {
        std::cout << "Erreur lors de la modification : " << query.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}
QSqlQueryModel* Livraison::rechercher(int id, const QString& adresse, const QString& etat, const QString& type, double frais, const QString& date) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString queryString = "SELECT * FROM Livraison WHERE 1=1";  // 1=1 facilite l'ajout dynamique des conditions

    // Construction de la chaîne de requête dynamiquement selon les champs
    if (id > 0) {
        queryString += " AND id_livraison = :id";
    }
    if (!adresse.isEmpty()) {
        queryString += " AND adresse_livraison LIKE :adresse";
    }
    if (!etat.isEmpty()) {
        queryString += " AND etat_livraison LIKE :etat";
    }
    if (!type.isEmpty()) {
        queryString += " AND type_livraison LIKE :type";
    }
    if (frais > 0) {
        queryString += " AND frais_livraison = :frais";
    }
    if (!date.isEmpty()) {
        queryString += " AND date_livraison = :date";
    }

    // Préparation de la requête finale
    query.prepare(queryString);

    // Liaison des valeurs seulement si elles sont définies
    if (id > 0) query.bindValue(":id", id);
    if (!adresse.isEmpty()) query.bindValue(":adresse", "%" + adresse + "%");
    if (!etat.isEmpty()) query.bindValue(":etat", "%" + etat + "%");
    if (!type.isEmpty()) query.bindValue(":type", "%" + type + "%");
    if (frais > 0) query.bindValue(":frais", frais);
    if (!date.isEmpty()) query.bindValue(":date", date);

    // Exécution et vérification de la requête
    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête:" << query.lastError();
        delete model;  // Nettoyer en cas d'erreur
        return nullptr;
    }

    // Mise en place du modèle pour l'affichage
    model->setQuery(move(query));
    if (model->rowCount() == 0) {
        qDebug() << "Aucun résultat trouvé.";
    } else {
        qDebug() << "Nombre de résultats:" << model->rowCount();
    }

    return model;
}

