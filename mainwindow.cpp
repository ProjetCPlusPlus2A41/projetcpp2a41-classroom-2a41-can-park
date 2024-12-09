#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "menu.h"
#include "employee.h"
#include <QTime>
#include"mail.h"
#include "facerecongnitionapp.h"  // Include the FaceRecognitionApp header

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->A->setPlaceholderText("Email");
    ui->B->setPlaceholderText("Mot de Passe");
    connect(ui->login, &QPushButton::clicked, this, &MainWindow::on_pushButton_login_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_pushButton_cancel_clicked);
    ui->label_3->setTextInteractionFlags(Qt::NoTextInteraction);
    ui->label_4->setTextInteractionFlags(Qt::NoTextInteraction);
    connect(ui->oublie, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->retourner, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->envoi, &QPushButton::clicked, this, &MainWindow::handleLogin);
    FaceRecognitionApp *faceApp = new FaceRecognitionApp(this);
    connect(ui->faceentry, &QPushButton::clicked, faceApp, &FaceRecognitionApp::startFaceRecognition);
    connect(faceApp, &FaceRecognitionApp::faceRecognized, this, &MainWindow::onFaceRecognized);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_login_clicked() {
    QString email = ui->A->text().trimmed();
    QString password = ui->B->text().trimmed();

    QSqlQuery query;
    query.prepare("SELECT PRENOME, NOME FROM EMPLOYE WHERE EMAILE = :email AND IDE = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QString prenom = query.value("PRENOME").toString();
            QString nom = query.value("NOME").toString();

            // Récupérer les initiales
            QString initiales = prenom.left(1).toUpper() + nom.left(1).toUpper();

            QMessageBox::information(this, "Succès", "Connexion réussie.");
            this->close();

            // Ouvrir le menu avec les initiales
            Menu *menu = new Menu();
            menu->setInitials(initiales); // Passer les initiales au menu
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->show();
        } else {
            QMessageBox::warning(this, "Échec", "Adresse e-mail ou mot de passe incorrect.");
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Une erreur s'est produite lors de l'authentification.");
    }
}
void MainWindow::handleLogin() {
    QString email = ui->email->text(); // Récupérer l'email de l'utilisateur
    QString secretCode = ui->nouv->text(); // Récupérer le code secret de l'utilisateur

    // Vérification de l'email et du code secret dans la base de données
    QSqlQuery query;
    query.prepare("SELECT IDE, PRENOME, NOME FROM EMPLOYE WHERE EMAILE = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Erreur de connexion à la base de données.");
        return;
    }

    if (query.next()) {
        QString storedCodeSecret = "canpak"; // Récupérer le code secret stocké
        QString prenom = query.value("PRENOME").toString(); // Récupérer le prénom
        QString nom = query.value("NOME").toString(); // Récupérer le nom

        if (storedCodeSecret == secretCode) {
            // Vérifier que le nouvel ID n'existe pas déjà dans la base de données
            int newId;
            bool idExists = true;
            while (idExists) {
                newId = QTime::currentTime().msec();  // Use milliseconds as a random seed
                QSqlQuery checkQuery;
                checkQuery.prepare("SELECT IDE FROM EMPLOYE WHERE IDE = :newId");
                checkQuery.bindValue(":newId", newId);

                if (!checkQuery.exec()) {
                    QMessageBox::warning(this, "Erreur", "Erreur lors de la vérification de l'ID.");
                    return;
                }

                if (!checkQuery.next()) {
                    idExists = false; // L'ID n'existe pas, on peut continuer
                }
            }

            // Mise à jour de l'ID dans la base de données
            query.prepare("UPDATE EMPLOYE SET IDE = :newId WHERE EMAILE = :email");
            query.bindValue(":newId", newId);
            query.bindValue(":email", email);

            if (query.exec()) {
                // Si la mise à jour est réussie, envoyer un email avec le nouvel ID
                QString subject = "Votre nouveau ID";
                QString message = QString("Bonjour %1 %2,\n\nVotre nouveau ID est : %3")
                                     .arg(prenom).arg(nom).arg(newId);

                mail emailSender; // Assuming this is a mail class that you use to send emails
                emailSender.sendEmail(email, subject, message); // Envoi du mail avec la fonction définie précédemment

                QMessageBox::information(this, "Succès", "Votre ID a été mis à jour et un email a été envoyé.");
                // Rediriger ou fermer la fenêtre de connexion
            } else {
                QMessageBox::warning(this, "Erreur", "Impossible de mettre à jour l'ID dans la base de données.");
            }
        } else {
            QMessageBox::warning(this, "Erreur", "Le code secret est incorrect.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec cet email.");
    }
}

void MainWindow::onFaceRecognized(QString recognizedId) {
    if (recognizedId=="Aucun visage reconnu") {
        QMessageBox::warning(this, "Erreur", "Aucun visage reconnu");

        return;
    }

    // Utilisez l'ID extrait du nom de l'image pour interroger la base de données
    QSqlQuery query;
    query.prepare("SELECT PRENOME, NOME FROM EMPLOYE WHERE IDE = :id");
    query.bindValue(":id", recognizedId);

    if (query.exec()) {
        if (query.next()) {
            QString prenom = query.value("PRENOME").toString();
            QString nom = query.value("NOME").toString();

            // Récupérer les initiales
            QString initiales = prenom.left(1).toUpper() + nom.left(1).toUpper();

            QMessageBox::information(this, "Succès", "Connexion réussie.");
            this->close();

            // Ouvrir le menu avec les initiales
            Menu *menu = new Menu();
            menu->setInitials(initiales); // Passer les initiales au menu
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->show();
        } else {
            QMessageBox::warning(this, "Échec", "Aucun employé trouvé pour cet ID.");
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de la recherche dans la base de données.");
    }
}


void MainWindow::on_pushButton_cancel_clicked(){

    this->close();
}
