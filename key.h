#ifndef KEY_H
#define KEY_H

#include<arduino.h>
#include <QDialog>
#include <QDialog>
#include <employee.h>
namespace Ui {
class key;
}

class key : public QDialog
{
    Q_OBJECT

public:
    explicit key(QWidget *parent = nullptr);
    ~key();
    void readFromArduino();

private:
    Ui::key *ui;
    QByteArray data;
    Arduino *A;
};

#endif // KEY_H
