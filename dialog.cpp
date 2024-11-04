#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QSqlError>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->tableView->setModel(Es.afficher());

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Dialog::on_pushButton_ajouter_clicked);
    connect(ui->pushButton_supp, &QPushButton::clicked, this, &Dialog::on_pushButton_supprimer_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::on_pushButton_refresh_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Dialog::on_pushButton_enregistrer_clicked);

    updateTableView();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();

    Etudiant E(id, nom, prenom);
    bool test = E.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The student was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        clearAndRefreshTable();
        updateTableView();
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the student to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Dialog::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Es.supprimer(id);

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The student was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        clearAndRefreshTable();
        updateTableView();
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the student from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

void Dialog::updateTableView()
{
    ui->tableView->setModel(nullptr);
    QSqlQueryModel *newModel = Es.afficher();
    ui->tableView->setModel(newModel);
}

void Dialog::on_pushButton_refresh_clicked()
{
    updateTableView();
}

void Dialog::clearAndRefreshTable()
{
    ui->tableView->setModel(nullptr);
    QSqlTableModel *model = Es.afficher();
    ui->tableView->setModel(model);
}

void Dialog::on_pushButton_enregistrer_clicked()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
    if (model) {
        if (model->submitAll()) {
            QMessageBox::information(this, "Success", "Changes saved successfully.");
        } else {
            QMessageBox::critical(this, "Error", model->lastError().text());
        }
    }
}
