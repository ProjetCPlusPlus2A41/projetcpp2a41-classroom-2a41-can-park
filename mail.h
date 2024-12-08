#ifndef MAIL_H
#define MAIL_H

#include <QDialog>

#include "client.h"  // Include QTimer

namespace Ui {
class mail;
}

class mail : public QDialog
{
    Q_OBJECT

public:
    explicit mail(QWidget *parent = nullptr);
    ~mail();

    void sendEmail(const QString &toEmail, const QString &subject, const QString &message);
    void sendEmailFromUI();
    void selectAttachmentFile();
Client Es;
private:
    Ui::mail *ui;
    QString attachmentFilePath;

};

#endif // MAIL_H
