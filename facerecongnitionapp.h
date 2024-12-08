#ifndef FACERECOGNITIONAPP_H
#define FACERECOGNITIONAPP_H
#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

class FaceRecognitionApp : public QObject {
    Q_OBJECT

public:
    FaceRecognitionApp(QObject *parent = nullptr) : QObject(parent) {}

    void startFaceRecognition() {
        // Créer un QProcess pour exécuter le script Python
        QProcess *process = new QProcess(this);

        // Définir la commande Python et le chemin du script
        QString program = "python"; // Assurez-vous que python est dans le PATH ou donnez le chemin complet
        QStringList arguments;
        arguments << "C:/Users/haouas/Downloads/facial_recognition.py"; // Chemin vers votre script Python

        // Démarrer le processus
        process->start(program, arguments);

        // Connexion au signal 'finished' pour gérer la fin du processus
        connect(process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                this, &FaceRecognitionApp::onFaceRecognitionFinished);

        // Connexion pour récupérer la sortie standard du processus (message de résultat)
        connect(process, &QProcess::readyReadStandardOutput, this, &FaceRecognitionApp::onReadyReadStandardOutput);
    }

signals:
    void faceRecognized(QString employeeId);  // Signal pour notifier lorsque le visage est reconnu avec l'ID de l'employé

private slots:
    void onFaceRecognitionFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::NormalExit) {
            qDebug() << "Le processus de reconnaissance faciale a réussi !";
        } else {
            qDebug() << "Le processus de reconnaissance faciale a échoué !";
        }
    }

    void onReadyReadStandardOutput() {
        QProcess *process = qobject_cast<QProcess*>(sender());
            QString output = process->readAllStandardOutput().trimmed();

            // Utilisation de QString::fromUtf8 pour garantir que l'encodage UTF-8 est respecté
            output = QString::fromUtf8(output.toUtf8());

            if (output == "Aucun visage reconnu") {
                qDebug() << "Aucun visage reconnu";
                QMessageBox::information(nullptr, "Reconnaissance faciale", "Aucun visage reconnu.");
            } else if (output.startsWith("Reconnaissance réussie! Nom:")) {
                QString recognizedName = output.mid(10); // Extraire le nom après "Reconnaissance réussie! Nom:"
                qDebug() << "Visage reconnu: " << recognizedName;

                // Extraire l'ID à partir du nom du fichier (par exemple "8.jpg")
                QString recognizedId = recognizedName.left(recognizedName.lastIndexOf('.'));  // "8" from "8.jpg"

                // Émettre un signal avec l'ID reconnu
                emit faceRecognized(recognizedId);  // Émettre un signal pour notifier que le visage a été reconnu avec l'ID
            } else {
                QString recognizedName = output.mid(22); // Extraire le nom après "Reconnaissance réussie! Nom:"
                qDebug() << "Visage reconnu: " << recognizedName;

                // Extraire l'ID à partir du nom du fichier (par exemple "8.jpg")
                QString recognizedId = recognizedName.left(recognizedName.lastIndexOf('.'));  // "8" from "8.jpg"

                // Émettre un signal avec l'ID reconnu
                emit faceRecognized(recognizedId);  // Émettre un signal pour notifier que le visage a été reconnu avec l'ID
            }
        }
};
#endif // FACERECOGNITIONAPP_H
