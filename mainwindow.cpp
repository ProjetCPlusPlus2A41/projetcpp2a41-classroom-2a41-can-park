#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->ajoutere, &QPushButton::clicked, this, &MainWindow::on_pushbutton_ajouter_clikede);
    connect(ui->supprimere, &QPushButton::clicked, this, &MainWindow::on_pushbutton_supprimer_clikede);

    // Set validators for ID fields
    ui->ide->setValidator(new QIntValidator(0, 999999, this));
    ui->ide1->setValidator(new QIntValidator(0, 999999, this));

    // Display the data in the table view (using emp as the instance)
    ui->tableViewe->setModel(emp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for adding a new employee
void MainWindow::on_pushbutton_ajouter_clikede()
{
    int ide = ui->ide->text().toInt();
    QString nome = ui->nome->text();
    QString emaile = ui->emaile->text();
    QString numc = ui->nume->text();
    float salairec = ui->salairee->text().toFloat();
    QString postec = ui->postee->text();
    QDate datec = ui->datee->date();

    // Create the employee object
    employee emp(ide, nome, emaile, numc, salairec, postec, datec);

    // Add the employee to the database
    bool test = emp.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The employee was successfully added.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewe->setModel(emp.afficher());  // Refresh the table
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add the employee to the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}

// Slot for deleting an employee by ID
void MainWindow::on_pushbutton_supprimer_clikede()
{
    int ide = ui->ide1->text().toInt();
    bool test = emp.supprimer(ide);  // Use emp instance here

    if (test) {
        QMessageBox::information(this, tr("Success"),
                                 tr("The employee was successfully deleted.\nClick OK to continue."),
                                 QMessageBox::Ok);
        ui->tableViewe->setModel(emp.afficher());  // Refresh the table
    } else {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete the employee from the database.\nClick OK to continue."),
                              QMessageBox::Ok);
    }
}
