#include "pinky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Pinky::Pinky(Game* game) :
  Ghost(game, Field::LEFT, config::SPRITE_START_X, config::PINKY_START_Y)
{
  setPos(Field::Tile{13, 11}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  setDefault();
}

Field::Tile Pinky::getTargetTile()
{
  return game_->getPacmanTile().nextTile(game_->getPacmanDirection(), 4);
}

Field::Tile Pinky::getScatterTile()
{
  return {0, 0};
}

void Pinky::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::PINKY_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
}
