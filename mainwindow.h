#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employee.h" // Include the employee class
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Slots for handling button clicks for employee operations
    void on_pushbutton_ajouter_clikede();  // Add employee
    void on_pushbutton_supprimer_clikede(); // Delete employee

private:
    Ui::MainWindow *ui;
    employee emp;      // Object to handle the employee operations
};

#endif // MAINWINDOW_H
