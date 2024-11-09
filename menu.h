#ifndef MENU_H
#define MENU_H
#include "client.h"
#include "equipement.h"

#include <QDialog>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QFont>             // Pour définir la police du texte
#include <QHeaderView>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlTableModel>
#include <QFont>
#include <QHeaderView>
#include <QFontMetrics>

#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlTableModel>
#include <QFont>
#include <QFontMetrics>
#include <QHeaderView>
#include <QPageSize>
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include<QtCharts>


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
void on_pushbutton_ajouter_clikedq();

void on_pushbutton_supprimer_clikedq();
private:
    Ui::Menu *ui;
    void trierTableView(int index);
};

#endif // MENU_H
