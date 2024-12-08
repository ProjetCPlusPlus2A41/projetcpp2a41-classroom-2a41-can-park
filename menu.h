#ifndef MENU_H
#define MENU_H
#include "client.h"
#include "equipement.h"
#include "matiere.h"
#include "employee.h"
#include "produit.h"
#include "livraison.h"
#include "mainwindow.h"

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
#include "PhotoBlobDelegate.h"

#include <QDesktopServices>
#include <QUrl>
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
    employee ESe;
    produit ESt;
    Livraison ESl;
public:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_refresh_clicked();
    void updateTableView();
    void clearAndRefreshTable();
    void on_textChanged_recherche(const QString &text);
    void rechercherParId(int idRecherche);
    void exporterEnPDF();
    void on_button_return_to_main_clicked();
    void setMainWindow(MainWindow *mainWindow); // Définir la MainWindow

//void exporterEnExcel();
void openStatistiquesDialog();
void openEmailDialog();
void openbareDialog();
void opensenarioDialog();
void opensmsDialog();
void openQRDialog();
void opencatDialog();
void openpresenceDialog();
void openechourouDialog();
void exporterEnExcel(QAbstractItemModel* model);

void on_pushButton_supprimerTout_clicked();
//equipementtttttttttttttttttttttttt
void on_pushbutton_ajouter_clikedq();
void on_pushbutton_supprimer_clikedq();
void on_textChanged_rechercheq(const QString &text);
void rechercherParIdq(int idRecherche);
void exporterEnPDFq();
void on_pushButton_supprimerTout_clickedq();
void on_selectPhotoButton_clicked();
QString currentImagePath; // Déclarez la variable pour stocker le chemin de l'image

void setupTableView() ;
//matireeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void on_pushbutton_ajouter_clikedm();
void on_pushbutton_supprimer_clikedm();
void on_textChanged_recherchem(const QString &text);
void rechercherParIdm(int idRecherche);
void exporterEnPDFm();
void on_pushButton_supprimerTout_clickedm();
void on_stackWidget_currentChanged(int index);

//employeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
void on_pushbutton_ajouter_clikede();
void on_pushbutton_supprimer_clikede();
void setInitials(const QString &initials);
void on_textChanged_recherchee(const QString &text);
void rechercherParIde(int idRecherche);
void exporterEnPDFe();
void on_pushButton_supprimerTout_clickede();
void on_btnPrendrePhoto_clicked();

//void exporterEnExcele();

//produitttttttttttttttttttttttttttttttttttttttttttt
void on_pushbutton_ajouter_clikedt();
void on_pushbutton_supprimer_clikedt();
void on_textChanged_recherchet(const QString &text);
void rechercherParIdt(int idRecherche);
void exporterEnPDFt();
void on_pushButton_supprimerTout_clickedt();
//livraisonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
void on_pushbutton_ajouter_clikedl();
void on_pushbutton_supprimer_clikedl();
void on_textChanged_recherchel(const QString &text);
void rechercherParIdl(int idRecherche);
void exporterEnPDFl();
void on_pushButton_supprimerTout_clickedl();
void afficherLivraisonsDansCalendrier();
void on_calendarWidget_clicked(const QDate &date);
void displayDeliveriesInCalendar();
void applyStylesheetForDeliveries();
void on_pushButton_showMap_clicked();

private slots:
void on_Chatbot_clicked();

private:
    Ui::Menu *ui;
    void trierTableView(int index);
    void trierTableViewq(int index);
    void trierTableViewl(int index);
    void trierTableViewm(int index);
    void trierTableViewt(int index);
    void trierTableViewe(int index);

    int pi;
int S=0;
MainWindow *mainWindow; // Référence à l'instance de MainWindow


};

#endif // MENU_H