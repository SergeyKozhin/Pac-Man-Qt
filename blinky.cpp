#include "blinky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Blinky::Blinky(Game* game) : Ghost(game, Field::LEFT, config::SPRITE_START_X, config::BLINKY_START_Y)
{
  setPos(Field::Tile{13, 11}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setDefault();
}

Field::Tile Blinky::getTargetTile()
{
  return game_->getPacmanTile();
}

Field::Tile Blinky::getScatterTile()
{
  return {config::FIELD_SIZE_X, 0};
}

void Blinky::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::BLINKY_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
}
