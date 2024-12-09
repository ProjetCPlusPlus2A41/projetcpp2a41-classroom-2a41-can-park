#ifndef SENARIO_H
#define SENARIO_H
#include<arduino.h>
#include <QDialog>
#include<client.h>
#include<menu.h>
namespace Ui {
class senario;
}

class senario : public QDialog
{
    Q_OBJECT

public:
    explicit senario(QWidget *parent = nullptr);
    ~senario();
    Client Es;
    int i=0;
    Menu E;
 protected:
     void keyPressEvent(QKeyEvent *event) override;
void showEvent(QShowEvent *event) override;
void resizeWindow();

void initializeLabel();

private :
     void update_label();


 public :

     void processBarcode(const QString &code);


 private:
     Ui::senario *ui;
     QByteArray data;
     Arduino *A;
     QString scannedCode;
};

#endif // SENARIO_H
