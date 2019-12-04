#include "game.hpp"
#include "pacman.hpp"
#include "config.hpp"

Game::Game(QWidget* parent) :
  QWidget(parent),
  view_(new QGraphicsView(this)),
  scene_(new QGraphicsScene(this)),
  pacman_(new Pacman(this)),
  blinky_(new Blinky(this)),
  pinky_(new Pinky(this)),
  inky_(new Inky(this)),
  clyde_(new Clyde(this))
{
  view_->setFixedSize(config::FIELD_SIZE_X_PX + 1, config::FIELD_SIZE_Y_PX + 1);
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setScene(scene_);

  scene_->setSceneRect(0, 0, config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX);
  scene_->setBackgroundBrush(
      QBrush(QImage(":/img/field.png").scaled(config::FIELD_SIZE_X_PX, config::FIELD_SIZE_Y_PX)));

  scene_->addItem(pacman_);
  pacman_->setFocus();

  scene_->addItem(blinky_);
  scene_->addItem(pinky_);
  scene_->addItem(inky_);
  scene_->addItem(clyde_);
}

void Game::start()
{
  view_->show();
}

Field::Tile Game::getPacmanTile()
{
  return Field::toTile(pacman_->getCenter());
}

Field::Direction Game::getPacmanDirection()
{
  return pacman_->getDirection();
}

Field::Tile Game::getBlinkyTile()
{
  return Field::toTile(blinky_->getCenter());
}
