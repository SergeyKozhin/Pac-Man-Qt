#ifndef FIELD_HPP
#define FIELD_HPP

#include <QPointF>
#include "config.hpp"

class Field
{
public:
  enum Direction
  {
    UP,
    LEFT,
    DOWN,
    RIGHT
  };


  struct Tile
  {
    enum Type
    {
      PELLET,
      WALL,
      EMPTY,
      PELLET_BLOCK,
      BLOCK,
      SLOWDOWN,
      BIG_PELLET,
      GHOST_ONLY
    };

    int x, y;

    int distSqr(const Tile& rhs) const;
    Tile nextTile(Direction direction, int dist = 1) const;
    QPointF toPoint() const;
    Type getType() const;
    bool operator==(const Tile& rhs) const;
    bool operator!=(const Tile& rhs) const;
  };

  static bool canGo(const Tile& tile, Direction direction);
  static Tile toTile(const QPointF& point);
  static QPointF getOffset(const QPointF& point, Direction direction);
  static bool isVertiacl(Direction direction);
  static bool isHorizontal(Direction direction);
  static Direction opposite(Direction direction);
  static bool onField(const QPointF& point);

private:
  const static int field_[config::FIELD_SIZE_Y][config::FIELD_SIZE_X];
};

#endif // FIELD_HPP
