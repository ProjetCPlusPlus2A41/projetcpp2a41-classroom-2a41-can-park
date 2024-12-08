
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QPixmap>
#include <QList>
#include "catalogue.h"
#include "ui_catalogue.h"

catalogue::catalogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catalogue),
    currentRow(0),
    currentColumn(0),
    currentPage(0)
{
    ui->setupUi(this);

    // Setup Stacked Widget
    stackedWidget = new QStackedWidget(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(stackedWidget);
    scrollArea->setWidgetResizable(true);
    ui->layout->addWidget(scrollArea);

    createNewPage();

    // Add "+" button
    QPushButton *addButton = new QPushButton("+", this);
    addButton->setIcon(QIcon(":/icons/plus.png"));
    connect(addButton, &QPushButton::clicked, this, &catalogue::addProduct);
    ui->layout->addWidget(addButton);

    // Add "Previous" and "Next" buttons
    QPushButton *previousButton = new QPushButton("Précédent", this);
    connect(previousButton, &QPushButton::clicked, this, &catalogue::previousPage);
    ui->layout->addWidget(previousButton);

    QPushButton *nextButton = new QPushButton("Suivant", this);
    connect(nextButton, &QPushButton::clicked, this, &catalogue::nextPage);
    ui->layout->addWidget(nextButton);

    // Load previously saved products
    loadProducts();
}

catalogue::~catalogue()
{
    delete ui;
    // Save products when closing
    saveProducts();
}

void catalogue::createNewPage()
{
    QWidget *page = new QWidget;
    currentGridLayout = new QGridLayout(page);
    stackedWidget->addWidget(page);
    currentPage = stackedWidget->count() - 1;
}

void catalogue::addProduct()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Choisir une image", "", "Images (*.png *.jpg *.bmp)");

    if (!imagePath.isEmpty()) {
        // Add product to the list and UI
        products.append(imagePath);
        addProductFromFile(imagePath);
    }
}

void catalogue::addProductFromFile(const QString &imagePath)
{
    // Create a clickable label for the product image
    ClickableLabel *product = new ClickableLabel(this);
    product->setPixmap(QPixmap(imagePath).scaled(100, 100));
    product->setAlignment(Qt::AlignCenter);

    // Connect the label's clicked signal to the deleteProduct slot
    connect(product, &ClickableLabel::clicked, this, &catalogue::deleteProduct);

    currentGridLayout->addWidget(product, currentRow, currentColumn);

    // Update position in the grid
    currentColumn++;
    if (currentColumn >= maxColumns) {
        currentColumn = 0;
        currentRow++;
    }

    // If the page is full, create a new one
    if (currentRow >= maxRows) {
        currentRow = 0;
        currentColumn = 0;
        createNewPage();
        stackedWidget->setCurrentIndex(currentPage);
    }
}

void catalogue::deleteProduct()
{
    // This method is called when a product image is clicked
    QObject *senderObj = sender();
    ClickableLabel *clickedLabel = qobject_cast<ClickableLabel *>(senderObj);
    if (clickedLabel) {
        // Find the corresponding widget and remove it
        int index = currentGridLayout->indexOf(clickedLabel);
        if (index != -1) {
            QString imagePath = products.at(index);
            products.removeAt(index); // Remove the image path from the list
            delete clickedLabel;     // Delete the clicked label (product)
        }

        // Immediately save changes after deletion
        saveProducts();
    }
}

void catalogue::previousPage()
{
    if (currentPage > 0) {
        stackedWidget->setCurrentIndex(--currentPage);
    }
}

void catalogue::nextPage()
{
    if (currentPage < stackedWidget->count() - 1) {
        stackedWidget->setCurrentIndex(++currentPage);
    }
}

void catalogue::saveProducts()
{
    // Save the product paths to a file
    QFile file("products.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString &productPath : products) {
            out << productPath << "\n";
        }
    }
}

void catalogue::loadProducts()
{
    // Load the product paths from the file
    QFile file("products.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                products.append(line);
                addProductFromFile(line);
            }
        }
    }
}

