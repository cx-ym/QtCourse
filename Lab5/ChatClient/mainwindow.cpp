#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    m_chatClient = new ChatClient(this);

    connect(m_chatClient, &ChatClient::connected, this, &MainWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::messageRecieved, this, &MainWindow::messageRecieved);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    m_chatClient->connectToServer(QHostAddress(ui->serverEdit->text()), 1967);
}


void MainWindow::on_sayButton_clicked()
{
    if (!ui->saylineEdit->text().isEmpty()) {
        m_chatClient->sendMessage(ui->saylineEdit->text());
    }
}


void MainWindow::on_logoutButton_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->loginPage);

}

void MainWindow::connectedToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    m_chatClient->sendMessage(ui->usernameEdit->text(), "login");
}

void MainWindow::messageRecieved(const QString &text)
{
    ui->roomtextEdit->append(text);
}

