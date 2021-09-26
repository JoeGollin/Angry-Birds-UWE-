//
// Created by JoeGollin on 19/03/2021.
//

#include "Enemies.h"
#include <iostream>

Enemies::Enemies()
{
  pigs_position = new Vector2(700,550);
}

Enemies::~Enemies()
{

}

bool Enemies::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << " failed to load \n";
  }
  sprite = new sf::Sprite(texture);
  return true;
}

sf::Sprite* Enemies::getSprite()
{
  return sprite;
}

bool Enemies::getVisibility() const
{
  return is_visible;
}

void Enemies::setVisibility(bool value)
{
  is_visible = value;
}
