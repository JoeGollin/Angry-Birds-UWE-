//
// Created by JoeGollin on 19/03/2021.
//

#include "Birds.h"
#include <iostream>

Birds::Birds()
{
  birds_position = new Vector2(120, 560);
  birds_direction = new Vector2(0, 0);
}

Birds::~Birds()
{

}

bool Birds::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << " failed to load \n";
  }
  sprite = new sf::Sprite(texture);
  return true;
}

sf::Sprite* Birds::getSprite()
{
  return sprite;
}

bool Birds::getVisibility() const
{
  return is_visible;
}

void Birds::setVisibility(bool value)
{
  is_visible = value;
}

bool Birds::getClicked() const
{
  return is_clicked;
}

void Birds::setClicked(bool value)
{
  is_clicked = value;
}

bool Birds::getFired() const
{
  return is_fired;
}

void Birds::setFired(bool value)
{
  is_fired = value;
}
