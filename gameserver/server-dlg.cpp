// server-dlg.cpp

#include "server-dlg.h"

#include <QTcpServer>
#include <QTcpSocket>

ServerDialog::ServerDialog()
{
  setupUi(this);
  //
  connect(
    m_pButtonClose, SIGNAL(clicked()), this, SLOT(close()));
  //
  m_pServer = new QTcpServer(this);
  connect(
    m_pServer, &QTcpServer::newConnection,
    this, &ServerDialog::on_newConnection);
  if (!m_pServer->listen(QHostAddress::Any, 45569))
  {
    QString strErrors = m_pTextEditErrors->toPlainText();
    strErrors += QString("Error: ") + m_pServer->errorString() + '\n';
    //
    m_pTextEditErrors->setPlainText(strErrors);
  }
}    // ServerDialog()

void ServerDialog::on_newConnection()
{
  QTcpSocket *pClientSocket = m_pServer->nextPendingConnection();
  connect(
    pClientSocket, &QAbstractSocket::disconnected,
    pClientSocket, &QObject::deleteLater);
  connect(
    pClientSocket, &QIODevice::readyRead,
    this, &ServerDialog::on_readyRead);
}

void ServerDialog::on_readyRead()
{
  QTcpSocket *pClientSocket =
    qobject_cast <QTcpSocket *> (sender());
  if (!pClientSocket)
    return;
  //
  QDataStream inout(pClientSocket);
  inout.startTransaction();
  QString strChatLine;
  inout >> strChatLine;
  if (!inout.commitTransaction())
    return;
  //
  QString strChat =
    m_pTextEditChat->toPlainText() +
    pClientSocket->peerAddress().toString() +
    "> " + strChatLine + '\n';
  inout << strChat;
  m_pTextEditChat->setPlainText(strChat);
  //
  pClientSocket->disconnectFromHost();
}    // on_readyRead()

// End of File
