#include "sat.h"
#include "ui_sat.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include "client.h"
#include "livraison.h"
#include "menu.h"
#include "matiere.h"

SAT::SAT(int pi,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAT)
{
    ui->setupUi(this);

    switch (pi) {
          case 1:
        createPieChart();
        qDebug() << "Value of pi after button click:" << pi;

              break;
          case 2:
              generateDeliveryBarChart();
              qDebug() << "Value of pi after button click:" << pi;

              break;
    case 3:
generateEmployeeLineChart();
        break;
    case 4:
        generateProductBarChart();
        break;
    case 5:

        generateProductPriceBarChart();
        break;
    case 6:
        generateEquipmentCostDonutChart();
        break;
          default:
              QMessageBox::warning(this, "Erreur", "Valeur invalide pour pi !");
              break;
      }

}
void SAT:: createPieChart(){
    Client client;

    int loyalClients = 0;
    int nonLoyalClients = 0;

    client.countLoyalAndNonLoyalClients(loyalClients, nonLoyalClients);

    QPieSeries *series = new QPieSeries();

    QPieSlice *slice1 = series->append("Loyal Clients", loyalClients);
    QPieSlice *slice2 = series->append("Non-Loyal Clients", nonLoyalClients);

    slice1->setLabel(QString("%1 %").arg(slice1->percentage() * 100, 0, 'f', 1));
    slice2->setLabel(QString("%1 %").arg(slice2->percentage() * 100, 0, 'f', 1));

    connect(series, &QPieSeries::hovered, this, [=](QPieSlice *slice, bool state) {
        if (state) {
            slice->setExploded(true);
            slice->setLabelVisible(true);
        } else {
            slice->setExploded(false);
            slice->setLabelVisible(false);
        }
    });

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Clients Fidèles vs Clients Non Fidèles");

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    this->setLayout(layout);
}

void SAT::generateDeliveryBarChart() {
    // Create a series to hold the data for the chart
    QBarSeries *series = new QBarSeries();

    // Create a bar set for the deliveries
    QBarSet *set_1 = new QBarSet("Deliveries");

    // Query the database for delivery counts by address
    QSqlQuery query("SELECT adresse_livraison, COUNT(*) FROM LIVRAISON GROUP BY adresse_livraison");

    // Create a list to hold the address names
    QStringList addressNames;

    // Variable to hold the maximum delivery count
    int maxCount = 0;

    // Loop through the query results
    while (query.next()) {
        QString address = query.value(0).toString();  // Address from the database
        int count = query.value(1).toInt();           // Count of deliveries

        // Add the count to the bar set
        set_1->append(count);

        // Update the maximum delivery count if necessary
        if (count > maxCount) {
            maxCount = count;
        }

        // Add the address to the address list
        addressNames.append(address);
    }

    // Append the bar set to the series
    series->append(set_1);

    // Create a chart to display the data
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Number of Deliveries by Address");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create an X-axis with the addresses
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(addressNames);  // Use the addresses as categories for the X-axis
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create a Y-axis to represent the delivery counts
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxCount);  // Set the maximum value to the highest count
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Enable the legend for the chart
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Set the bar labels to be visible and display them above the bars
    series->setLabelsVisible(true);  // Enable labels to be visible on the bars
    series->setLabelsPosition(QBarSeries::LabelsInsideEnd); // Position labels inside the bars

    // Create a chart view to display the chart
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Create a layout for the dialog and add the chart view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    // Set the layout for the dialog
    this->setLayout(layout);
}
void SAT::generateEmployeeLineChart() {
    int range1 = 0;  // 0 to 100
    int range2 = 0;  // 100 to 1000
    int range3 = 0;  // 1000+

    // Query the database to get all employees' salaries
    QSqlQuery query("SELECT SALAIREC FROM EMPLOYE");

    // Loop through the query results and categorize salaries into ranges
    while (query.next()) {
        int salary = query.value(0).toInt();

        // Categorize salary into ranges
        if (salary <= 100) {
            range1++;
        } else if (salary > 100 && salary <= 1000) {
            range2++;
        } else if (salary > 1000) {
            range3++;
        }
    }

    // Create a pie series to hold the data for the donut chart
    QPieSeries *series = new QPieSeries();

    // Add slices for each salary range with the number of employees
    QPieSlice *slice1 = series->append(QString("Salary 0-100 (%1 employees)").arg(range1), range1);
    QPieSlice *slice2 = series->append(QString("Salary 100-1000 (%1 employees)").arg(range2), range2);
    QPieSlice *slice3 = series->append(QString("Salary Over 1000 (%1 employees)").arg(range3), range3);

    // Set labels for each slice with the percentage and number of employees
    slice1->setLabel(QString("Salary 0-100 %1 employees (%2%)").arg(range1).arg(slice1->percentage() * 100, 0, 'f', 1));
    slice2->setLabel(QString("Salary 100-1000 %1 employees (%2%)").arg(range2).arg(slice2->percentage() * 100, 0, 'f', 1));
    slice3->setLabel(QString("Salary Over 1000 %1 employees (%2%)").arg(range3).arg(slice3->percentage() * 100, 0, 'f', 1));

    // Optionally add hover effect
    connect(series, &QPieSeries::hovered, this, [=](QPieSlice *slice, bool state) {
        if (state) {
            slice->setExploded(true);
            slice->setLabelVisible(true);
        } else {
            slice->setExploded(false);
            slice->setLabelVisible(false);
        }
    });

    // Create a chart to display the donut chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Salary Distribution");

    // Create a hole in the middle of the pie chart to turn it into a donut chart
    series->setHoleSize(0.35);  // 35% hole size, adjust for the desired thickness

    // Create a chart view to display the chart
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->setBackgroundBrush(QBrush(QColor("#eeeeee")));  // Change to dark color (e.g., black or dark gray)

    // Create a layout for the dialog and add the chart view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    // Set the layout for the dialog
    this->setLayout(layout);
}
void SAT::generateProductBarChart() {
    // Create a series to hold the data for the chart
    QBarSeries *series = new QBarSeries();

    // Create a bar set for the quantities
    QBarSet *set_1 = new QBarSet("Quantities");

    // Query the database to get product names and their available quantities
    QSqlQuery query("SELECT NOMT, QUANTITET FROM PRODUIT");

    // Create a list to hold the product names
    QStringList productNames;

    // Variable to hold the maximum quantity
    int maxQuantity = 0;

    // Loop through the query results
    while (query.next()) {
        QString productName = query.value(0).toString();  // Product name from the database
        int quantity = query.value(1).toInt();           // Quantity of the product

        // Add the quantity to the bar set
        set_1->append(quantity);

        // Update the maximum quantity if necessary
        if (quantity > maxQuantity) {
            maxQuantity = quantity;
        }

        // Add the product name to the product list
        productNames.append(productName);
    }

    // Append the bar set to the series
    series->append(set_1);

    // Create a chart to display the data
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Product Quantities Available");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create an X-axis with the product names
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(productNames);  // Use the product names as categories for the X-axis
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create a Y-axis to represent the quantities
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxQuantity);  // Set the maximum value to the highest quantity
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Enable the legend for the chart
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Set the bar labels to be visible and display them above the bars
    series->setLabelsVisible(true);  // Enable labels to be visible on the bars
    series->setLabelsPosition(QBarSeries::LabelsInsideEnd); // Position labels inside the bars

    // Create a chart view to display the chart
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Create a layout for the dialog and add the chart view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    // Set the layout for the dialog
    this->setLayout(layout);
}
void SAT::generateProductPriceBarChart() {
    // Variables to categorize product prices into ranges
    int range1 = 0;  // Price 0 to 50
    int range2 = 0;  // Price 50 to 200
    int range3 = 0;  // Price 200+

    // Query the database to get the prices
    QSqlQuery query("SELECT PRIXM FROM MATIERE");

    // Loop through the query results and categorize prices into ranges
    while (query.next()) {
        double price = query.value(0).toDouble();  // Price of the product

        // Categorize price into ranges
        if (price <= 50) {
            range1++;
        } else if (price > 50 && price <= 200) {
            range2++;
        } else if (price > 200) {
            range3++;
        }
    }

    // Create a pie series to hold the data for the chart
    QPieSeries *series = new QPieSeries();

    // Add slices for each price range with the count of products
    QPieSlice *slice1 = series->append(QString("0-50 (%1 products)").arg(range1), range1);
    QPieSlice *slice2 = series->append(QString("51-200 (%1 products)").arg(range2), range2);
    QPieSlice *slice3 = series->append(QString("200+ (%1 products)").arg(range3), range3);

    // Apply distinct colors to each slice
    slice1->setBrush(QColor(255, 99, 71));  // Red (for range 0-50)
    slice2->setBrush(QColor(60, 179, 113)); // Green (for range 51-200)
    slice3->setBrush(QColor(70, 130, 180)); // SteelBlue (for range 200+)

    // Optionally add hover effect
    connect(series, &QPieSeries::hovered, this, [=](QPieSlice *slice, bool state) {
        if (state) {
            slice->setExploded(true);
            slice->setLabelVisible(true);
        } else {
            slice->setExploded(false);
            slice->setLabelVisible(false);
        }
    });

    // Set percentage labels for each slice
    slice1->setLabel(QString("0-50 %1 products (%2%)").arg(range1).arg(slice1->percentage() * 100, 0, 'f', 1));
    slice2->setLabel(QString("51-200 %1 products (%2%)").arg(range2).arg(slice2->percentage() * 100, 0, 'f', 1));
    slice3->setLabel(QString("200+ %1 products (%2%)").arg(range3).arg(slice3->percentage() * 100, 0, 'f', 1));

    // Create a chart to display the pie chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Product Price Distribution");

    // Create a chart view to display the chart
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Create a layout for the dialog and add the chart view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    // Set the layout for the dialog
    this->setLayout(layout);
}
void SAT::generateEquipmentCostDonutChart() {
    int range1 = 0;  // Cost 0 to 100
    int range2 = 0;  // Cost 100 to 1000
    int range3 = 0;  // Cost 1000+

    // Query the database to get all equipment costs
    QSqlQuery query("SELECT COUT_EQ FROM EQUIPEMENT");

    // Loop through the query results and categorize equipment costs into ranges
    while (query.next()) {
        double cost = query.value(0).toDouble();

        // Categorize cost into ranges
        if (cost <= 100) {
            range1++;
        } else if (cost > 100 && cost <= 1000) {
            range2++;
        } else if (cost > 1000) {
            range3++;
        }
    }

    // Create a pie series to hold the data for the donut chart
    QPieSeries *series = new QPieSeries();

    // Add slices for each cost range with the number of equipment
    QPieSlice *slice1 = series->append(QString("Cost 0-100 (%1 items)").arg(range1), range1);
    QPieSlice *slice2 = series->append(QString("Cost 100-1000 (%1 items)").arg(range2), range2);
    QPieSlice *slice3 = series->append(QString("Cost Over 1000 (%1 items)").arg(range3), range3);

    // Set labels for each slice with the percentage and number of items
    slice1->setLabel(QString("Cost 0-100 %1 items (%2%)").arg(range1).arg(slice1->percentage() * 100, 0, 'f', 1));
    slice2->setLabel(QString("Cost 100-1000 %1 items (%2%)").arg(range2).arg(slice2->percentage() * 100, 0, 'f', 1));
    slice3->setLabel(QString("Cost Over 1000 %1 items (%2%)").arg(range3).arg(slice3->percentage() * 100, 0, 'f', 1));

    // Set distinct colors for each slice
    slice1->setBrush(QColor(255, 165, 0));   // Orange (for range 0-100)
     slice2->setBrush(QColor(34, 193, 195));  // Aqua (for range 100-1000)
     slice3->setBrush(QColor(253, 94, 83)); // SteelBlue (for range 1000+)

    // Optionally add hover effect
    connect(series, &QPieSeries::hovered, this, [=](QPieSlice *slice, bool state) {
        if (state) {
            slice->setExploded(true);
            slice->setLabelVisible(true);
        } else {
            slice->setExploded(false);
            slice->setLabelVisible(false);
        }
    });

    // Create a chart to display the donut chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Equipment Cost Distribution");

    // Create a hole in the middle of the pie chart to turn it into a donut chart
    series->setHoleSize(0.35);  // 35% hole size, adjust for the desired thickness

    // Create a chart view to display the chart
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Set background color for the chart (light gray)
    chart->setBackgroundBrush(QBrush(QColor("#f2f2f2")));

    // Create a layout for the dialog and add the chart view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartview);

    // Set the layout for the dialog
    this->setLayout(layout);
}



SAT::~SAT()
{
    delete ui;
}
