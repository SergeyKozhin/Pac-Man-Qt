#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <QGraphicsItem>
#include "field.hpp"

class Game;

class Entity : public QObject, public QGraphicsEllipseItem
{
  Q_OBJECT
public:
  Entity(Game* game, Field::Direction startDirection);
  QPointF getCenter();

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
};

#endif // ENTITY_HPP
