#include "game.hpp"
#include "pacman.hpp"
#include "config.hpp"
#include "food.hpp"

Game::Game(QWidget* parent) :
  QWidget(parent),
  view_(new QGraphicsView(this)),
  scene_(new QGraphicsScene(this)),
  pacman_(new Pacman(this)),
  ghosts_(
      {{"Blinky", new Blinky(this)}, {"Pinky", new Pinky(this)}, {"Inky", new Inky(this)}, {"Clyde", new Clyde(this)}}),
  score_(0)
{
  srand(time(0));

  view_->setFixedSize(config::FIELD_SIZE_X_PX + 1, config::FIELD_SIZE_Y_PX + 1);
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setScene(scene_);

  scene_->setSceneRect(0, 0, config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX);
  scene_->setBackgroundBrush(
      QBrush(QImage(":/img/field.png").scaled(config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX)));

  for (int i = 0; i < config::FIELD_SIZE_Y; ++i)
  {
    for (int j = 0; j < config::FIELD_SIZE_Y; ++j)
    {
      const Field::Tile tile = {i, j};
      if (tile.getType() == Field::Tile::Type::PELLET || tile.getType() == Field::Tile::Type::PELLET_BLOCK)
      {
        scene_->addItem(new Food(this, tile, Food::Type::PELLET));
      }
      else if (tile.getType() == Field::Tile::Type::BIG_PELLET)
      {
        scene_->addItem(new Food(this, tile, Food::Type::BIG_PELLET));
      }
    }
  }

  scene_->addItem(pacman_);
  pacman_->setFocus();

  connect(this, SIGNAL(start()), pacman_, SLOT(start()));
  connect(this, SIGNAL(stop()), pacman_, SLOT(stop()));

  for (auto ghost : ghosts_)
  {
    scene_->addItem(ghost.second);
    connect(this, SIGNAL(start()), ghost.second, SLOT(start()));
    connect(this, SIGNAL(stop()), ghost.second, SLOT(stop()));
  }

  view_->show();
}

Field::Tile Game::getPacmanTile() const
{
  return Field::toTile(pacman_->getCenter());
}

Field::Direction Game::getPacmanDirection() const
{
  return pacman_->getDirection();
}

const std::map<std::string, Ghost*>& Game::getGhosts() const
{
  return ghosts_;
}

void Game::increseScore(int score)
{
  score_ += score;
}
