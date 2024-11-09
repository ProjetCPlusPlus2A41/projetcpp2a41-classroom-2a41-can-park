#include "sat.h"  // Include the correct header file
#include "ui_sat.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>  // Include QVBoxLayout for manual layout creation

SAT::SAT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAT)
{
    ui->setupUi(this);

    // Create a pie chart (example)
    QPieSeries *series = new QPieSeries();

    // Append data to the pie series
    QPieSlice *slice1 = series->append("Data 1", 10);
    QPieSlice *slice2 = series->append("Data 2", 20);
    QPieSlice *slice3 = series->append("Data 3", 30);

    // You can set label format to display the percentage
    slice1->setLabel(QString("%1 %").arg(slice1->percentage() * 100, 0, 'f', 1));  // Format the label as percentage
    slice2->setLabel(QString("%1 %").arg(slice2->percentage() * 100, 0, 'f', 1));  // Format the label as percentage
    slice3->setLabel(QString("%1 %").arg(slice3->percentage() * 100, 0, 'f', 1));  // Format the label as percentage

    // Create a chart and set it up
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sample Pie Chart with Percentages");

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
