#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config
{
  static const int FACTOR = 4;

  static const int ORIGINAL_TILE_SIZE = 8;
  static const int TILE_SIZE = FACTOR * ORIGINAL_TILE_SIZE;

  static const int FIELD_SIZE_X = 28;
  static const int FIELD_SIZE_X_PX = FIELD_SIZE_X * TILE_SIZE;
  static const int FIELD_SIZE_Y = 31;
  static const int FIELD_SIZE_Y_PX = FIELD_SIZE_Y * TILE_SIZE;

  static const int ENTITY_SIZE = TILE_SIZE * 2;

  static const int ORIGINAL_PACMAN_SPEED = 80;
  static const int PACMAN_SPEED = ORIGINAL_PACMAN_SPEED * FACTOR;
  static const int GHOST_SPEED = PACMAN_SPEED * 0.95;
} // namespace config

#endif // CONFIG_HPP
