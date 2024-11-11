#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matierepremiere.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouterM_clicked();
    void clear();
    bool controlSaisie();
    void on_tab_MatierePremiere_activated(const QModelIndex &index);
    void on_pb_modifierM_clicked();

    void on_pb_supprimerM_clicked();

private:
    Ui::MainWindow *ui;
    MatierePremiere MP;
};
#endif
