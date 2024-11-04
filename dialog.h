#ifndef DIALOG_H
#define DIALOG_H

#include "etudiant.h"
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <QApplication>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    Etudiant Es;

public slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_refresh_clicked();
    void updateTableView();
    void clearAndRefreshTable();
    void on_pushButton_enregistrer_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
