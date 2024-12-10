#include "chatserver.h"
#include "serverworker.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{

}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::incomingConnection(qintptr sockDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(sockDescriptor)) {
        worker->deleteLater();
        return ;
    }

    m_clients.append(worker);
    qDebug() << "来了老弟...............";
    emit logMessage("新的用户连接上了");
}
