#ifndef SAT_H
#define SAT_H

#include <QDialog>
#include<QtCore>
#include<QtGui>
#include<QtWidgets>
#include<QtCharts>
namespace Ui {
class SAT;
}

class SAT : public QDialog
{
    Q_OBJECT

public:
    explicit SAT(QWidget *parent = nullptr);
    ~SAT();
void createPieChart();
private:
    Ui::SAT *ui;
};

#endif // SAT_H
