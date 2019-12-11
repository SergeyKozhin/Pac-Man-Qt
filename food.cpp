#include "food.hpp"
#include "game.hpp"

Food::Food(Game* game, const Field::Tile& tile, Food::Type type) :
  QObject(game),
  QGraphicsEllipseItem(),
  game_(game),
  type_(type)
{
  if (type == Type::PELLET)
  {
    setRect(0, 0, config::PELLET_SIZE, config::PELLET_SIZE);
  }
  else if (type == Type::BIG_PELLET)
  {
    setRect(0, 0, config::BIG_PELETE_SIZE, config::BIG_PELETE_SIZE);
  }
  setPos(tile.toPoint() - rect().center());

  setBrush(QBrush(Qt::yellow));
}

Food::Type Food::getType() const
{
  return type_;
}
