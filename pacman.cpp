#include "pacman.hpp"
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>

Pacman::Pacman(Game* game) :
  Entity(game, Field::RIGHT)
{
  setRect(0, 0, config::ENTITY_SIZE, config::ENTITY_SIZE);
  setPos(Field::toPoint({13, 23}) - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));
  setBrush(QBrush(Qt::yellow));

  setFlag(QGraphicsItem::ItemIsFocusable);

  timer_->start(1000. / config::PACMAN_SPEED);
}

void Pacman::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
  {
  case Qt::Key_Up:
    nextDirection_ = Field::UP;
    break;
  case Qt::Key_Left:
    nextDirection_ = Field::LEFT;
    break;
  case Qt::Key_Down:
    nextDirection_ = Field::DOWN;
    break;
  case Qt::Key_Right:
    nextDirection_ = Field::RIGHT;
    break;
  }

  state = MOVING;
}

Field::Direction Pacman::getDirection()
{
  return currentDirection_;
}

void Pacman::tick()
{
  Field::Tile tile = Field::toTile(getCenter());
  if (Field::onField(getCenter()) && nextDirection_ != currentDirection_ && Field::canGo(tile, nextDirection_))
  {
    currentDirection_ = nextDirection_;
  }
  if (getCenter() == Field::toPoint(tile) && !Field::canGo(tile, currentDirection_))
  {
    state = STANDING;
  }

  if (state == MOVING)
  {
    setPos(pos() + Field::getOffset(getCenter(), currentDirection_));
    align();
  }
}

void Pacman::align()
{
  if (Field::isVertiacl(currentDirection_))
  {
    int currX = static_cast<int>(getCenter().x());
    if (currX % config::TILE_SIZE > config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::LEFT));
    }
    else if (currX % config::TILE_SIZE != config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::RIGHT));
    }
  }
  else
  {
    int currY = static_cast<int>(getCenter().y());
    if (currY % config::TILE_SIZE > config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::UP));
    }
    else if (currY % config::TILE_SIZE != config::TILE_SIZE / 2)
    {
      setPos(pos() + Field::getOffset(getCenter(), Field::DOWN));
    }
  }
}
