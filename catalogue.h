#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QStackedWidget>
#include <QScrollArea>
#include <QFileDialog>
#include <QList> // Pour stocker les chemins des images
#include <QJsonArray> // Pour gérer la sauvegarde en JSON
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

namespace Ui {
class catalogue;
}

class catalogue : public QDialog
{
    Q_OBJECT

public:
    explicit catalogue(QWidget *parent = nullptr);
    ~catalogue();

private slots:
    void addProduct();
    void deleteProduct();
    void previousPage();
    void nextPage();

private:
    Ui::catalogue *ui;
    QStackedWidget *stackedWidget;
    QScrollArea *scrollArea;
    QGridLayout *currentGridLayout;
    int currentRow;
    int currentColumn;
    int currentPage;
    const int maxColumns = 3;
    const int maxRows = 3;

    QList<QString> products; // List to track products (image paths)

    void createNewPage();
    void saveProducts();  // Save product list to file
    void loadProducts();  // Load product list from file
    void addProductFromFile(const QString &imagePath);  // Add product from saved data
};
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

signals:
    void clicked(); // Custom signal

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            emit clicked(); // Emit the clicked signal
        }
    }
};

#endif // CATALOGUE_H
