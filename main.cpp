#include <QApplication>
#include "game.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Game game(&a);
  game.show();

  return a.exec();
}
