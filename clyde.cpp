#include "clyde.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Clyde::Clyde(Game* game) :
  Ghost(game, Field::LEFT)
{
  setRect(0, 0, config::ENTITY_SIZE, config::ENTITY_SIZE);
  setPos(Field::toPoint({13, 11}) - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setBrush(QBrush(Qt::gray));

  timer_->start(1000. / config::GHOST_SPEED);
}

Field::Tile Clyde::getTargetTile()
{
  Field::Tile pacmanTile = game_->getPacmanTile();
  if (Field::toTile(getCenter()).distSqr(pacmanTile) >= 64)
  {
    return pacmanTile;
  }

  return getScatterTile();
}

Field::Tile Clyde::getScatterTile()
{
  return {0, config::FIELD_SIZE_Y};
}
