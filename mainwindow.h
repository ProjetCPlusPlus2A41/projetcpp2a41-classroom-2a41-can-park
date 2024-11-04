#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "livraison.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_rechercher_clicked();

private:
    Ui::MainWindow *ui;
    Livraison Ltmp;
};

#endif // MAINWINDOW_H
