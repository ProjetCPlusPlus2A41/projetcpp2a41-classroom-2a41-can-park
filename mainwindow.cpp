#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Connecter les boutons aux fonctions correspondantes
    connect(ui->pushButton_ajouter, &QPushButton::clicked, this, &MainWindow::on_pushButton_ajouter_clicked);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &MainWindow::on_pushButton_supprimer_clicked);

    // Affiche initialement les données dans le tableau
    ui->tableView->setModel(Ltmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    int id_livraison = ui->lineEdit_id_livraison->text().toInt();
    QString date_livraison = ui->lineEdit_date_livraison->text();
    QString adresse_livraison = ui->lineEdit_adresse_livraison->text();
    double frais_livraison = ui->lineEdit_frais_livraison->text().toDouble();
    QString type_livraison = ui->lineEdit_type_livraison->text();
    QString etat_livraison = ui->lineEdit_etat_livraison->text();

    Livraison L(id_livraison, adresse_livraison, date_livraison, frais_livraison, type_livraison, etat_livraison);
    bool test = L.ajouter();

    if (test)
    {
        ui->tableView->setModel(Ltmp.afficher()); // Mise à jour de la vue après ajout
        QMessageBox::information(this, tr("Ajout"), tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id_livraison = ui->lineEdit_id_livraison->text().toInt();
    bool test = Ltmp.supprimer(id_livraison);

    if (test)
    {
        ui->tableView->setModel(Ltmp.afficher()); // Mise à jour de la vue après suppression
        QMessageBox::information(this, tr("Suppression"), tr("Suppression effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_modifier_clicked()
{
    int id_livraison = ui->lineEdit_id_livraison->text().toInt();
    QString date_livraison = ui->lineEdit_date_livraison->text();
    QString adresse_livraison = ui->lineEdit_adresse_livraison->text();
    double frais_livraison = ui->lineEdit_frais_livraison->text().toDouble();
    QString type_livraison = ui->lineEdit_type_livraison->text();
    QString etat_livraison = ui->lineEdit_etat_livraison->text();

    Livraison L(id_livraison, adresse_livraison, date_livraison, frais_livraison, type_livraison, etat_livraison);

    if (L.modifier(id_livraison)) {
        ui->tableView->setModel(L.afficher()); // Mise à jour de la vue
        QMessageBox::information(this, tr("Modification"), tr("Modification effectuée avec succès."));
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}
void MainWindow::on_pushButton_rechercher_clicked() {
    int id = ui->lineEdit_id_livraison->text().isEmpty() ? 0 : ui->lineEdit_id_livraison->text().toInt();
    QString adresse = ui->lineEdit_adresse_livraison->text();
    QString etat = ui->lineEdit_etat_livraison->text();
    QString type = ui->lineEdit_type_livraison->text();
    double frais = ui->lineEdit_frais_livraison->text().isEmpty() ? 0.0 : ui->lineEdit_frais_livraison->text().toDouble();
    QString date = ui->lineEdit_date_livraison->text();

    qDebug() << "Recherche avec critères - ID:" << id << ", Adresse:" << adresse << ", Etat:" << etat
             << ", Type:" << type << ", Frais:" << frais << ", Date:" << date;

    QSqlQueryModel* resultModel = Ltmp.rechercher(id, adresse, etat, type, frais, date);
    if (resultModel && resultModel->rowCount() > 0) {
        ui->tableView->setModel(resultModel);
    } else {
        QMessageBox::information(this, tr("Recherche"), tr("Aucun résultat trouvé."));
        ui->tableView->setModel(Ltmp.afficher());  // Afficher toutes les livraisons si aucun résultat
    }
}








