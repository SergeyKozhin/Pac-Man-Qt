#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "pacman.hpp"
#include "blinky.hpp"
#include "pinky.hpp"
#include "inky.hpp"
#include "clyde.hpp"

class Game : public QWidget
{
  Q_OBJECT
public:
  Game(QWidget* parent = nullptr);
  void start();
  Field::Tile getPacmanTile();
  Field::Direction getPacmanDirection();
  Field::Tile getBlinkyTile();

private:
  QGraphicsView* view_;
  QGraphicsScene* scene_;
  Pacman* pacman_;
  Blinky* blinky_;
  Pinky* pinky_;
  Inky* inky_;
  Clyde* clyde_;
};

#endif // GAME_HPP
