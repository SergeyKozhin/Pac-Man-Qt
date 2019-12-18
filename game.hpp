#ifndef GAME_HPP
#define GAME_HPP

#include <map>
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
  Game(QApplication* app, QWidget* parent = nullptr);
  Field::Tile getPacmanTile() const;
  Field::Direction getPacmanDirection() const;
  const std::map<std::string, Ghost*>& getGhosts() const;
  void increseScore(int score);
  void decreaseDots();
  void gameOver();
  void reset();
  bool getIsOver() const;

signals:
  void start();
  void stop();

private:
  QApplication* app_;
  QGraphicsView* view_;
  QGraphicsScene* scene_;
  Pacman* pacman_;
  std::map<std::string, Ghost*> ghosts_;
  QGraphicsTextItem* textScore_;
  QGraphicsTextItem* textLive_;
  int score_;
  int lives_;
  int dotsLeft_;
  bool isOver_;

};

#endif // GAME_HPP
