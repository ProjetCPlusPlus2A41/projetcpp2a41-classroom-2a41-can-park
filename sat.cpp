#include "sat.h"
#include "ui_sat.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include "client.h"


SAT::SAT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAT)
{
    ui->setupUi(this);

    // Create an instance of the Client class
    Client client;

    // Variables to hold the counts of loyal and non-loyal clients
    int loyalClients = 0;
    int nonLoyalClients = 0;

    // Get the counts of loyal and non-loyal clients
    client.countLoyalAndNonLoyalClients(loyalClients, nonLoyalClients);

    // Create a pie chart (example)
    QPieSeries *series = new QPieSeries();

    // Append data to the pie series using the client counts
    QPieSlice *slice1 = series->append("Loyal Clients", loyalClients);
    QPieSlice *slice2 = series->append("Non-Loyal Clients", nonLoyalClients);

    // You can set label format to display the percentage
    slice1->setLabel(QString("%1 %").arg(slice1->percentage() * 100, 0, 'f', 1));  // Format the label as percentage
    slice2->setLabel(QString("%1 %").arg(slice2->percentage() * 100, 0, 'f', 1));  // Format the label as percentage

    // Create a chart and set it up
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Clients Fidèles vs Clients Non Fidèles");

    // Create a chart view
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Manually create a QVBoxLayout if no layout exists in the UI file
    QVBoxLayout *layout = new QVBoxLayout(this);  // Use 'this' as the parent widget
    layout->addWidget(chartview);  // Add the chart view to the layout

    // Set the layout for the dialog
    this->setLayout(layout);  // Set the layout for the dialog (optional if it's the parent layout)
}

SAT::~SAT()
{
    delete ui;
}
//QString username = "yassinebensaad567.com"; // Replace with your email
//QString appPassword = "rgki mwew mtbq momy";
