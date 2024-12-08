#ifndef CHATBOT_H
#define CHATBOT_H

#include <QDialog>
#include <QTcpSocket>
#include <QProcess> // Include QProcess
QT_BEGIN_NAMESPACE
namespace Ui {
class chatbot;
}
QT_END_NAMESPACE

class chatbot : public QDialog
{
    Q_OBJECT

public:
    explicit chatbot(QWidget *parent = nullptr);
    ~chatbot();
    void on_sendButton_clicked();
    void onSocketReadyRead();
    void closeEvent(QCloseEvent *event) ;

private:
    Ui::chatbot *ui;
    QTcpSocket *socket;
    QProcess *pythonProcess; // Add this line for QProcess
};

#endif // CHATBOT_H

