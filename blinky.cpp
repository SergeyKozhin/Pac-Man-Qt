#include "blinky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Blinky::Blinky(Game* game) :
  Ghost(game, Field::LEFT)
{
  setRect(0, 0, config::ENTITY_SIZE, config::ENTITY_SIZE);
  setPos(Field::toPoint({13, 11}) - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setBrush(QBrush(Qt::red));

  timer_->start(1000. / config::GHOST_SPEED);
}

Field::Tile Blinky::getTargetTile()
{
  return game_->getPacmanTile();
}

Field::Tile Blinky::getScatterTile()
{
  return {config::FIELD_SIZE_X, 0};
}
