#include "entity.hpp"
#include <QTimer>
#include "game.hpp"

Entity::Entity(Game* game, Field::Direction startDirection) :
  QObject(game),
  QGraphicsEllipseItem(),
  game_(game),
  currentDirection_(startDirection),
  nextDirection_(startDirection),
  timer_(new QTimer(this))
{
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

QPointF Entity::getCenter()
{
  return pos() + rect().center();
}

void Entity::start()
{
  timer_->start();
}

void Entity::stop()
{
  timer_->stop();
}
