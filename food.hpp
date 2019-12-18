#ifndef FOOD_HPP
#define FOOD_HPP

#include <QObject>
#include <QGraphicsEllipseItem>
#include "field.hpp"

class Game;

class Food : public QObject, public QGraphicsEllipseItem
{
public:
  enum class Type
  {
    PELLET,
    BIG_PELLET
  };

  Food(Game* game, const Field::Tile& tile, Type type);
  Type getType() const;
  Field::Tile getTile() const;

private:
  Game* game_;
  Type type_;
  Field::Tile tile_;
};

#endif // FOOD_HPP
