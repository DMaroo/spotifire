#include <QCoreApplication>
#include "SpotiFire.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  SpotiFire fw(&app);

  return app.exec();
}
