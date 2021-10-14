// server-dlg.h

#ifndef SERVER_DLG_H__
#define SERVER_DLG_H__

#include "ui_server-dlg.h"

#include <QDialog>

class QTcpServer;
class QTcpSocket;

class ServerDialog : public QDialog, public Ui::ServerDialog
{
  Q_OBJECT
  //
public:
  //
  ServerDialog();
  void giveMove(int clientId);
  void sendPlayerId(int clientId);
  //

public slots:
  void sendPoints();
  void playerDisconnected();

private slots:
  //
  void on_newConnection();
  void on_readyRead();
  //

private:
  //
  QTcpServer *m_pServer;
  std::vector<QTcpSocket *> m_players;
  int m_playersCount;
  int m_playersMount;
  int m_currentPLyer;
  int m_pointIndex;
  int m_gameEndedCheck;
};    // class ServerDialog

#endif    // SERVER_DLG_H__

// End of File
