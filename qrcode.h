#ifndef QRCODE_H
#define QRCODE_H

#include <QWidget>
#include <QLabel>
#include <QProcess>
#include <QPixmap>
#include <QDialog>
#include "produit.h"

namespace Ui {
class qrcode;
}

class qrcode : public QDialog
{
    Q_OBJECT

public:
    explicit qrcode(QWidget *parent = nullptr);
    ~qrcode();
    void generateQRCode();  // Fonction pour exécuter le script Python et afficher le QR code

private:
    Ui::qrcode *ui;
    produit ES;
};

#endif // QRCODE_H
