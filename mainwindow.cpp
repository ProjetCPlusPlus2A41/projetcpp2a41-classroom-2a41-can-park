#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "menu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->A->setPlaceholderText("Email");
    ui->B->setPlaceholderText("Mot de Passe");
    connect(ui->login, &QPushButton::clicked, this, &MainWindow::on_pushButton_login_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_pushButton_cancel_clicked);
    ui->label_3->setTextInteractionFlags(Qt::NoTextInteraction);
    ui->label_4->setTextInteractionFlags(Qt::NoTextInteraction);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_login_clicked() {
    QString email = ui->A->text().trimmed();
    QString password = ui->B->text().trimmed();

    QSqlQuery query;
    query.prepare("SELECT PRENOME, NOME FROM EMPLOYE WHERE EMAILE = :email AND IDE = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QString prenom = query.value("PRENOME").toString();
            QString nom = query.value("NOME").toString();

            // Récupérer les initiales
            QString initiales = prenom.left(1).toUpper() + nom.left(1).toUpper();

            QMessageBox::information(this, "Succès", "Connexion réussie.");
            this->close();

            // Ouvrir le menu avec les initiales
            Menu *menu = new Menu();
            menu->setInitials(initiales); // Passer les initiales au menu
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->show();
        } else {
            QMessageBox::warning(this, "Échec", "Adresse e-mail ou mot de passe incorrect.");
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Une erreur s'est produite lors de l'authentification.");
    }
}






void MainWindow::on_pushButton_cancel_clicked(){

    this->close();
}
