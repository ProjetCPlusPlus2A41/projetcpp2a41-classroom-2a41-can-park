#include "matiere.h"

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
