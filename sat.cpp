#include "sat.h"
#include "ui_sat.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include "client.h"

SAT::SAT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAT)
{
    ui->setupUi(this);

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

SAT::~SAT()
{
    delete ui;
}
