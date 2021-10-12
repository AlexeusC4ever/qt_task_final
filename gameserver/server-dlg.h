// server-dlg.h

#ifndef SERVER_DLG_H__
#define SERVER_DLG_H__

#include "ui_server-dlg.h"

#include <QDialog>

class QTcpServer;

class ServerDialog : public QDialog, public Ui::ServerDialog
{
  Q_OBJECT
  //
public:
  //
  ServerDialog();
  //
private slots:
  //
  void on_newConnection();
  void on_readyRead();
  //
private:
  //
  QTcpServer *m_pServer;
};    // class ServerDialog

#endif    // SERVER_DLG_H__

// End of File
