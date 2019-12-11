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

  static const int ORIGINAL_PELLET_SIZE = 2;
  static const int PELLET_SIZE = ORIGINAL_PELLET_SIZE * FACTOR;
  static const int BIG_PELETE_SIZE = PELLET_SIZE * 4;

  static const int ORIGIANL_SPRITE_START_X = 450;
  static const int ORIGIANL_PACMAN_START_Y = 0;
  static const int SPRITE_START_X = ORIGIANL_SPRITE_START_X * FACTOR;
  static const int PACMAN_START_Y = ORIGIANL_PACMAN_START_Y * FACTOR;
  static const int BLINKY_START_Y = PACMAN_START_Y + ENTITY_SIZE * 4;
  static const int PINKY_START_Y = PACMAN_START_Y + ENTITY_SIZE * 5;
  static const int INKY_START_Y = PACMAN_START_Y + ENTITY_SIZE * 6;
  static const int CLYDE_START_Y = PACMAN_START_Y + ENTITY_SIZE * 7;

} // namespace config

#endif // CONFIG_HPP
