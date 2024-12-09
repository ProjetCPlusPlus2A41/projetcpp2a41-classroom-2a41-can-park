#ifndef SAT_H
#define SAT_H

#include <QDialog>
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include<QtCharts>
#include"menu.h"
#include"client.h"
#include "produit.h"
#include "matiere.h"
#include "equipement.h"
#include "employee.h"

namespace Ui {
class SAT;
}

class SAT : public QDialog
{
    Q_OBJECT
public:
 explicit SAT(int pi, QWidget *parent = nullptr);
    ~SAT();
void createPieChart();
void generateDeliveryBarChart();
void generateEmployeeLineChart();
void generateProductBarChart();
void generateProductPriceBarChart();
void generateEquipmentCostDonutChart();
private:
    Ui::SAT *ui;
};

#endif // SAT_H
