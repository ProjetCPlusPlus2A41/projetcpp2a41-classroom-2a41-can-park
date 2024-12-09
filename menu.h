#ifndef MENU_H
#define MENU_H
#include "client.h"
#include "equipement.h"
#include "matiere.h"

#include <QDialog>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QFont>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QFontMetrics>
#include <QPageSize>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>


namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    Client Es;
    equipement ESq;
    matiere ESm;
public slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_refresh_clicked();
    void updateTableView();
    void clearAndRefreshTable();
    void on_textChanged_recherche(const QString &text);
    void rechercherParId(int idRecherche);
    void exporterEnPDF();
void exporterEnExcel();
void openStatistiquesDialog();
void openEmailDialog();
void openbareDialog();
void on_pushButton_supprimerTout_clicked();
//equipementtttttttttttttttttttttttt
void on_pushbutton_ajouter_clikedq();
void on_pushbutton_supprimer_clikedq();
//matireeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void on_pushbutton_ajouter_clikedm();
void on_pushbutton_supprimer_clikedm();
private:
    Ui::Menu *ui;
    void trierTableView(int index);
};

#endif // MENU_H
