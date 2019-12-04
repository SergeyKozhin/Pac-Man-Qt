#include "pinky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Pinky::Pinky(Game* game) :
  Ghost(game, Field::LEFT)
{
  setRect(0, 0, config::ENTITY_SIZE, config::ENTITY_SIZE);
  setPos(Field::toPoint({13, 11}) - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setBrush(QBrush(Qt::magenta));

  timer_->start(1000. / config::GHOST_SPEED);
}

Field::Tile Pinky::getTargetTile()
{
  return game_->getPacmanTile().nextTile(game_->getPacmanDirection(), 4);
}

Field::Tile Pinky::getScatterTile()
{
  return {0, 0};
}
