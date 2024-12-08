#ifndef RIF_H
#define RIF_H
#include<arduino.h>
#include <QDialog>
#include <QDialog>
#include <employee.h>

namespace Ui {
class rif;
}

class rif : public QDialog
{
    Q_OBJECT

public:
    explicit rif(QWidget *parent = nullptr);
    ~rif();
    void readFromArduino();
private:
    Ui::rif *ui;
    QByteArray data;
    Arduino *A;

};

#endif // RIF_H
