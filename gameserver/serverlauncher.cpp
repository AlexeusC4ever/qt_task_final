// example-24-server.cpp

#include <QApplication>

#include "server-dlg.h"

int main(int nArgC, char *apszArgV[])
{
  QApplication app(nArgC, apszArgV);
  //
  ServerDialog dialog;
  //
  return dialog.exec();
}    // main()

// End of File
