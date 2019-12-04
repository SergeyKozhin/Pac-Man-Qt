#include "inky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Inky::Inky(Game* game) :
  Ghost(game, Field::LEFT)
{
  setRect(0, 0, config::ENTITY_SIZE, config::ENTITY_SIZE);
  setPos(Field::toPoint({13, 11}) - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setBrush(QBrush(Qt::cyan));

  timer_->start(1000. / config::GHOST_SPEED);
}

Field::Tile Inky::getTargetTile()
{
  Field::Tile refTile = game_->getPacmanTile().nextTile(game_->getPacmanDirection(), 2);
  Field::Tile blinkyTyle = game_->getBlinkyTile();
  return {blinkyTyle.x + (refTile.x - blinkyTyle.x) * 2, blinkyTyle.y + (refTile.y - blinkyTyle.y) * 2};
}

Field::Tile Inky::getScatterTile()
{
  return {config::FIELD_SIZE_X, config::FIELD_SIZE_Y};
}
