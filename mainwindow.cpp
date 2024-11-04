#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>
#include "produit.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableView->setModel(p.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonAjout_clicked() {
    // Retrieving the values from the input fields
    int code = ui->codeline->text().toInt();
    QString nom = ui->lineNom->text();
    int qte = ui->qteline->text().toInt();
    float prixu = ui->prixline->text().toFloat();
    // Create a product (produit) instance
    produit p(code, qte, nom, prixu);

    // Call the ajouter() method to add the product and get the result
    bool test = p.ajouter();

    // If ajout (add) is successful
    if (test) {
        // Refresh (actualiser)
        ui->tableView->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué \n"
                                             "Click Cancel to exit"),
                                 QMessageBox::Cancel);
    } else {
        // If ajout (add) fails
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit"),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButtonsupprimer_clicked() {
    int id = ui->deleteline->text().toInt();
    bool test = p.supprimer(id);

    if (test) {
        ui->tableView->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}
