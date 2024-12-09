#ifndef BARE_H
#define BARE_H

#include <QMainWindow>
#include <QAxObject>
#include <QMessageBox>
#include <QFileInfo>
#include "client.h"  // Include QTimer

namespace Ui {
class bare;
}

class bare : public  QDialog
{
    Q_OBJECT

public:
    explicit bare(QWidget *parent = nullptr);
    ~bare();

    // Déclaration du signal changeStackIndex
Client Es;

 private slots:
    void genererCodeBarre();
    void envoyerIdVersExcel(const QString& cheminFichierExcel, const QString& id);
    void afficherImage(const QString& cheminImage);
    void afficherImageDelayed();
    void exporterEnPDF();
private:
    Ui::bare *ui;
};

#endif // BARE_H
