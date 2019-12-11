#include "entity.hpp"
#include <QTimer>
#include "game.hpp"

Entity::Entity(Game* game, Field::Direction startDirection, qreal startSpeed, int startFrameX, int startFrameY) :
  QObject(game),
  QGraphicsPixmapItem(),
  game_(game),
  currentDirection_(startDirection),
  nextDirection_(startDirection),
  timer_(new QTimer(this)),
  currentSpeed_(startSpeed),
  sheet_(QPixmap(":/img/sprites.png").scaled(config::FIELD_SIZE_X_PX * 3, config::FIELD_SIZE_Y_PX)),
  currFrameX_(startFrameX),
  currFrameY_(startFrameY),
  tile_(getTile())
{
  setPixmap(sheet_.copy(currFrameX_, currFrameY_, config::ENTITY_SIZE, config::ENTITY_SIZE));
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

QPointF Entity::getCenter() const
{
  return pos() + boundingRect().center();
}

Field::Tile Entity::getTile() const
{
  return Field::toTile(getCenter());
}

void Entity::start()
{
  timer_->start(currentSpeed_);
}

void Entity::stop()
{
  timer_->stop();
}
