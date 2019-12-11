#include "clyde.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Clyde::Clyde(Game* game) :
  Ghost(game, Field::LEFT, config::SPRITE_START_X, config::CLYDE_START_Y)
{
  setPos(Field::Tile{13, 11}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setDefault();
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

void Clyde::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::CLYDE_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
}
