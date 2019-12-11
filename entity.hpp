#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <QGraphicsPixmapItem>
#include "field.hpp"

class Game;

class Entity : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Entity(Game* game, Field::Direction startDirection, qreal startSpeed, int startFrameX, int startFrameY);
  QPointF getCenter() const;
  Field::Tile getTile() const;

public slots:
  void start();
  void stop();

private slots:
  virtual void tick() = 0;

protected:
  Game* game_;
  Field::Direction currentDirection_;
  Field::Direction nextDirection_;
  QTimer* timer_;
  qreal currentSpeed_;
  QPixmap sheet_;

  int currFrameX_;
  int currFrameY_;

  Field::Tile tile_;

  virtual void nextFrame() = 0;
  virtual void updateDirection() = 0;
};

#endif // ENTITY_HPP
