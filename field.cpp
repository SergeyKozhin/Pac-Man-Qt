#include "field.hpp"

const int Field::field_[config::FIELD_SIZE_Y][config::FIELD_SIZE_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 6, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 6, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 2, 4, 4, 4, 4, 4, 4, 2, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {5, 5, 5, 5, 2, 2, 0, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 0, 5, 5, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 6, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 6, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 3, 3, 4, 4, 3, 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

bool Field::canGo(const Field::Tile& tile, Field::Direction direction)
{
  switch (direction)
  {
  case UP:
    return (field_[(tile.y - 1 + config::FIELD_SIZE_Y) % config::FIELD_SIZE_Y][tile.x] != 1);
  case LEFT:
    return (field_[tile.y][(tile.x - 1 + config::FIELD_SIZE_X) % config::FIELD_SIZE_X] != 1);
  case DOWN:
    return (field_[(tile.y + 1) % config::FIELD_SIZE_Y][tile.x] != 1);
  case RIGHT:
    return (field_[tile.y][(tile.x + 1) % config::FIELD_SIZE_X] != 1);
  }

  return false;
}

QPointF Field::Tile::toPoint() const
{
  return QPointF(x * config::TILE_SIZE + config::TILE_SIZE / 2, y * config::TILE_SIZE + config::TILE_SIZE / 2);
}

Field::Tile Field::toTile(const QPointF& point)
{
  return {static_cast<int>(point.x()) / config::TILE_SIZE, static_cast<int>(point.y()) / config::TILE_SIZE};
}

QPointF Field::getOffset(const QPointF& point, Field::Direction direction)
{
  switch (direction)
  {
  case UP:
    if (point.y() < (-config::ENTITY_SIZE / 2))
    {
      return QPointF(0, config::FIELD_SIZE_Y_PX + config::ENTITY_SIZE);
    }

    return QPointF(0, -1);
  case LEFT:
    if (point.x() < (-config::ENTITY_SIZE / 2))
    {
      return QPointF(config::FIELD_SIZE_X_PX + config::ENTITY_SIZE, 0);
    }

    return QPointF(-1, 0);
  case DOWN:
    if (point.y() > (config::FIELD_SIZE_Y_PX + config::ENTITY_SIZE / 2))
    {
      return QPointF(0, -config::FIELD_SIZE_Y_PX - config::ENTITY_SIZE);
    }

    return QPointF(0, 1);
  case RIGHT:
    if (point.x() > (config::FIELD_SIZE_X_PX + config::ENTITY_SIZE / 2))
    {
      return QPointF(-config::FIELD_SIZE_X_PX - config::ENTITY_SIZE, 0);
    }

    return QPointF(1, 0);
  }

  return QPointF(0, 0);
}

bool Field::isVertiacl(Field::Direction direction)
{
  if (direction == UP || direction == DOWN)
  {
    return true;
  }

  return false;
}

bool Field::isHorizontal(Field::Direction direction)
{
  return !isVertiacl(direction);
}

Field::Direction Field::opposite(Field::Direction direction)
{
  switch (direction)
  {
  case UP:
    return DOWN;
  case LEFT:
    return RIGHT;
  case DOWN:
    return UP;
  case RIGHT:
    return LEFT;
  }

  return UP;
}

bool Field::onField(const QPointF& point)
{
  return point.x() > 0 && point.x() < config::FIELD_SIZE_X_PX && point.y() > 0 && point.y() < config::FIELD_SIZE_Y_PX;
}

int Field::Tile::distSqr(const Field::Tile& rhs) const
{
  return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
}

Field::Tile Field::Tile::nextTile(Field::Direction direction, int dist) const
{
  switch (direction)
  {
  case UP:
    return {x, y - dist};
  case LEFT:
    return {x - dist, y};
  case DOWN:
    return {x, y + dist};
  case RIGHT:
    return {x + dist, y};
  }

  return *this;
}

Field::Tile::Type Field::Tile::getType() const
{
  return static_cast<Type>(field_[y][x]);
}

bool Field::Tile::operator==(const Field::Tile& rhs) const
{
  return (x == rhs.x) && (y == rhs.y);
}

bool Field::Tile::operator!=(const Field::Tile& rhs) const
{
  return !(*this == rhs);
}
