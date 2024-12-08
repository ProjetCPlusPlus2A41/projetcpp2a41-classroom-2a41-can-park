#include "chatbot.h"
#include "ui_chatbot.h"
#include <QProcess>
#include <QDebug>

chatbot::chatbot(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatbot)
    , socket(new QTcpSocket(this))
    , pythonProcess(new QProcess(this)) // Initialize the QProcess
{
    ui->setupUi(this);

    // Define the Python interpreter and script path
    QString pythonPath = "python"; // Assurez-vous que 'python' est dans le PATH
    QString scriptPath = "C:/Users/haouas/Downloads/chatbot_server (1) (1).py"; // Chemin vers le script Python

    // Start the Python chatbot server
    pythonProcess->start(pythonPath, QStringList() << scriptPath);

    // Capture Python process output and errors
    connect(pythonProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        ui->chatDisplay->append("Python Output: " + pythonProcess->readAllStandardOutput());
    });
    connect(pythonProcess, &QProcess::readyReadStandardError, this, [this]() {
        ui->chatDisplay->append("Python Error: " + pythonProcess->readAllStandardError());
    });

    // Check if the Python script started successfully
    if (!pythonProcess->waitForStarted()) {
        ui->chatDisplay->append("Failed to start the Python chatbot server.");
        qDebug() << "Python Process Error:" << pythonProcess->errorString();
        return;
    }
    ui->chatDisplay->append("Chatbot server started successfully.");

    // Connect to the Python server
    socket->connectToHost("127.0.0.1", 5000);

    // Connect the socket's readyRead signal to our slot
    connect(socket, &QTcpSocket::readyRead, this, &chatbot::onSocketReadyRead);

    if (!socket->waitForConnected(3000)) {
        ui->chatDisplay->append("Failed to connect to the server.");
        qDebug() << "Socket Error:" << socket->errorString();
    } else {
        ui->chatDisplay->append("Connected to the chatbot server.");
    }

    // Connect send button
    connect(ui->sendButton, &QPushButton::clicked, this, &chatbot::on_sendButton_clicked);
}

chatbot::~chatbot() {
    // Terminate and clean up the Python process
    if (pythonProcess) {
        if (pythonProcess->state() != QProcess::NotRunning) {
            pythonProcess->terminate(); // Politely ask the process to exit
            if (!pythonProcess->waitForFinished(3000)) { // Wait for 3 seconds
                pythonProcess->kill(); // Force kill if it doesn't terminate
            }
        }
    }

    // Close and clean up the socket
    if (socket && socket->isOpen()) {
        socket->disconnectFromHost();
        socket->close();
    }

    delete ui;
}

void chatbot::onSocketReadyRead() {
    // Read the response from the server
    QByteArray response = socket->readAll();
    ui->chatDisplay->append("Bot: " + QString(response));
}

void chatbot::on_sendButton_clicked() {
    QString message = ui->messageInput->text(); // Assuming you have a text input
    if (socket && socket->isOpen()) {
        socket->write(message.toUtf8()); // Send the message to the server
        ui->messageInput->clear(); // Clear the input field
        ui->chatDisplay->append("You: " + message + "\n"); // Display the sent message
    } else {
        ui->chatDisplay->append("Socket is not connected.");
    }
}

void chatbot::closeEvent(QCloseEvent *event) {
    // Handle the cleanup when the chatbot window is closed
    if (pythonProcess) {
        if (pythonProcess->state() != QProcess::NotRunning) {
            pythonProcess->terminate();
            pythonProcess->waitForFinished(3000); // Wait for it to finish
        }
    }
    QDialog::closeEvent(event); // Call base class implementation
}
