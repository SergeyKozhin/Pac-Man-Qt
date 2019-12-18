#include "inky.hpp"
#include <QBrush>
#include <QTimer>
#include <game.hpp>

Inky::Inky(Game* game) :
  Ghost(game, Field::RIGHT, config::SPRITE_START_X, config::INKY_START_Y)
{
  resetPos();
}

void Inky::resetPos()
{
  setPos(Field::Tile{11, 14}.toPoint() - QPointF(config::ENTITY_SIZE / 2, config::ENTITY_SIZE / 2)
         + QPointF(config::TILE_SIZE / 2, 0));

  currentDirection_ = Field::RIGHT;
  nextDirection_ = currentDirection_;
  state_ = CAGED;
  setDefault();
  updateDirection();
  nextFrame();
}

Field::Tile Inky::getTargetTile()
{
  Field::Tile refTile = game_->getPacmanTile().nextTile(game_->getPacmanDirection(), 2);
  Field::Tile blinkyTyle = game_->getGhosts().at("Blinky")->getTile();
  return {blinkyTyle.x + (refTile.x - blinkyTyle.x) * 2, blinkyTyle.y + (refTile.y - blinkyTyle.y) * 2};
}

Field::Tile Inky::getScatterTile()
{
  return {config::FIELD_SIZE_X, config::FIELD_SIZE_Y};
}

void Inky::setDefault()
{
  setPixmap(sheet_.copy(config::SPRITE_START_X, config::INKY_START_Y, config::ENTITY_SIZE, config::ENTITY_SIZE));
  currFrameX_ = config::SPRITE_START_X;
  currFrameY_ = config::INKY_START_Y;
}
