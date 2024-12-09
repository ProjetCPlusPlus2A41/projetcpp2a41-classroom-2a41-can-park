#ifndef SMS_H
#define SMS_H

#include <QDialog>
#include "equipement.h"

namespace Ui {
class sms;
}

class sms : public QDialog
{
    Q_OBJECT

public:
    explicit sms(QWidget *parent = nullptr);
    ~sms();
void envoyerSMS_viaTwilio();
equipement Esq;
private:
    Ui::sms *ui;
};

#endif // SMS_H
