
#include "Game.h"
#include "Vector2.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  delete [] birds;
  delete [] pigs;
  birds = nullptr;
  pigs = nullptr;
}

bool Game::init()
{
  in_menu = true;
  in_game = false;
  player_win = false;
  player_lose = false;
  player_round = 5;
  player_score = 0;
  sf::Vector2f window_size(1080.0f, 720.0f);

  if (!font.loadFromFile("Data/Fonts/angrybirds-regular.ttf"))
  {
    std::cout << "Font did not load \n";
  }
  if (!menu_background_texture.loadFromFile(
    "Data/Images/menu.jpg"))
  {
    std::cout << "Background texture cannot be loaded\n";
  }
  menu_background.setTexture(menu_background_texture);
  menu_background.setScale(window_size.x / menu_background.getLocalBounds().width,
                      window_size.y / menu_background.getLocalBounds().height);

  menu_text.setString("[Enter] to start game\n"
                          "[Esc] to quit at anytime");
  menu_text.setFont(font);
  menu_text.setCharacterSize(30);
  menu_text.setFillColor(sf::Color::Black);
  menu_text.setPosition(10, 10);

  controls_text.setString("How to play:\n"
                          "Click and pull back the bird to release it\n"
                          "[Esc] to quit at anytime");
  controls_text.setFont(font);
  controls_text.setCharacterSize(25);
  controls_text.setFillColor(sf::Color::Black);
  controls_text.setPosition(10, 610);

  winner_text.setString("You Win!\n"
                        "[Enter] to return to menu");
  winner_text.setFont(font);
  winner_text.setCharacterSize(25);
  winner_text.setFillColor(sf::Color::Black);
  winner_text.setPosition(window.getSize().x / 2.0f - winner_text.getGlobalBounds().width / 2.0f,
                          window.getSize().y / 6.0f);

  loser_text.setString("You Lose!\n"
                        "[Enter] to return to menu");
  loser_text.setFont(font);
  loser_text.setCharacterSize(25);
  loser_text.setFillColor(sf::Color::Black);
  loser_text.setPosition(window.getSize().x / 2.0f - loser_text.getGlobalBounds().width / 2.0f,
                          window.getSize().y / 6.0f);

  score_text.setString("Score:");
  score_text.setFont(font);
  score_text.setCharacterSize((25));
  score_text.setFillColor(sf::Color::Black);
  score_text.setPosition(10, 10);

  score_text_number.setString(std::to_string(player_score));
  score_text_number.setFont(font);
  score_text_number.setCharacterSize(25);
  score_text_number.setFillColor(sf::Color::White);
  score_text_number.setPosition(score_text.getGlobalBounds().width + 10, 10);

  if (!level_background_texture.loadFromFile(
    "Data/Images/lvl3.png"))
  {
    std::cout << "Level 1 texture cannot be loaded\n";
  }
  level_background.setTexture(level_background_texture);
  level_background.setScale(window_size.x / level_background.getLocalBounds().width,
                           window_size.y / level_background.getLocalBounds().height);

  if (!level_floor_texture.loadFromFile("Data/Images/lvl3_floor.png"))
  {
    std::cout << "Level 1 texture floor cannot be loaded\n";
  }
  level_floor.setTexture((level_floor_texture));
  level_floor.setScale(window_size.x / level_background.getLocalBounds().width,
                       window_size.y / level_background.getLocalBounds().height);
  level_floor.setPosition(window_size.x - level_background.getLocalBounds().width,
                          window_size.y - level_background.getLocalBounds().height);

  if(!catapult_texture.loadFromFile("Data/Images/kenney_animalpackredux/catapult.png"))
  {
    std::cout << "Catapult texture failed to load\n";
  }
  catapult.setTexture(catapult_texture);
  catapult.setScale(0.2, 0.2);
  catapult.setPosition(catapult_position_x, catapult_position_y);

  birds = new Birds[bird_count];
  for (int i = 0; i < bird_count; i++)
  {
    birds[i].initialiseSprite(birds_texture, "Data/Images/kenney_animalpackredux/parrot.png");
    birds[i].getSprite()->setScale(0.25,0.25);
    birds[i].getSprite()->setPosition(catapult_position_x - 35.0f * i
                                      ,catapult_position_y + 00.f * i);

  }

  pigs = new Enemies[pig_count];
  for (int i = 0; i < pig_count; i++)
  {
    pigs[i].initialiseSprite(pigs_texture, "Data/Images/kenney_animalpackredux/pig.png");
    pigs[i].getSprite()->setScale(0.3,0.3);
    pigs[i].getSprite()->setPosition(pigs->pigs_position->x + 80.0f * i
                                     ,pigs->pigs_position->y + 0.0f * i);
  }
  return true;
}

void Game::update(float dt)
{
  sf::Vector2f click = window.mapPixelToCoords(sf::Mouse::getPosition(window));

  for (int i = 0; i < bird_count; i++)
  {
    for (int j = 0; j < pig_count; j++)
    {
      // Control Bird
      if (birds[i].getClicked())
      {
        birds[i].getSprite()->setPosition(click.x, click.y);
      }

      if(!birds[i].getClicked())
      {
        if(birds[i].getFired())
        {
          birds[i].gravity += 0.001f;
          birds[i].getSprite()->move(birds[i].birds_direction->x *
                                       bird_speed * dt,
                                     birds[i].birds_direction->y +
                                       birds[i].gravity * bird_speed * dt);

        }
      }


      // Collision Section
      if (birds[i].getSprite()->getPosition().x +
            birds[i].getSprite()->getGlobalBounds().width
          >= window.getSize().x) // Collide with right of screen
      {
        birds[i].birds_direction->x = -birds[i].birds_direction->x;
      }
      if (birds[i].getSprite()->getPosition().y +
            birds[i].getSprite()->getGlobalBounds().height
          >= window.getSize().y)  // Collide with bottom of screen
      {
        if (birds[i].getVisibility())
        {
          birds[i].setVisibility(false);
          player_round -= 1;
          birds[i].birds_direction->y = -birds[i].birds_direction->y;
        }
      }

      if (collisionCheck(*birds[i].getSprite(), *pigs[j].getSprite())
          && birds[i].getVisibility() && pigs[j].getVisibility())
      {
        score_text_number.setString(std::to_string(player_score));
        window.draw(score_text_number);
        player_score += 100;
        player_round -= 1;
        pigs[i].setVisibility(false);
        birds[i].setVisibility(false);
      }

      // Game Conditions
      if(player_round == 0)
      {
        in_game     = false;
        player_lose = true;
      }

      if (!pigs[j].getVisibility() && player_score == pig_count * 100)
      {
        in_game    = false;
        player_win = true;
      }
    }

  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_background);
    window.draw(menu_text);
    window.draw(controls_text);
  }
  if (in_game)
  {
    window.draw(level_background);
    window.draw(catapult);
    window.draw(level_floor);
    window.draw(score_text);
    window.draw(score_text_number);

    for (int i = 0; i < bird_count; i++)
    {
      if(birds[i].getVisibility())
      {
        window.draw(*birds[i].getSprite());
      }
    }
    for (int i = 0; i < pig_count; i++)
    {
      if(pigs[i].getVisibility())
      {
        window.draw(*pigs[i].getSprite());
      }
    }
  }
  if (player_win)
  {
    window.draw(menu_background);
    window.draw(winner_text);
  }
  if (player_lose)
  {
    window.draw(menu_background);
    window.draw(loser_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  for (int i = 0; i < bird_count; i++)
  {
    if (collisionClickCheck(click, *birds[i].getSprite()))
    {
      birds[i].setClicked(true);
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  for (int i = 0; i < bird_count; i++)
  {
    sf::Vector2i click = sf::Mouse::getPosition(window);
    float click_x = click.x;
    float click_y = click.y;
    if (birds[i].getClicked())
    {
      if(click_x <= catapult_position_x) // If click is to the left of slingshot
      {
        float launch_vector_x = std::abs(click_x - catapult_position_x);
        birds[i].birds_direction->x = launch_vector_x;
        if(click_y < catapult_position_y) // If click is above slingshot
        {
          float launch_vector_y = std::abs(click_y - catapult_position_y);
          birds[i].birds_direction->y = launch_vector_y;
        }
        else if(click_y >= catapult_position_y) // If click is below slingshot
        {
          float launch_vector_y = -std::abs(click_y - catapult_position_y);
          birds[i].birds_direction->y = launch_vector_y;
        }
      }
      else if(click_x > catapult_position_x) // If click is to the right of slingshot
      {
        float launch_vector_x = -std::abs(click_x + catapult_position_x);
        birds[i].birds_direction->x = launch_vector_x;
        if(click_y < catapult_position_y) // If click is above slingshot
        {
          float launch_vector_y = std::abs(click_y- catapult_position_y);
          birds[i].birds_direction->y = launch_vector_y;
        }
        else if(click_y >= catapult_position_y) // If click is below slingshot
        {
          float launch_vector_y = -std::abs(click_y - catapult_position_y);
          birds[i].birds_direction->y = launch_vector_y;
        }
      }
      birds[i].birds_direction->normalise();
      birds[i].setFired(true);
      birds[i].setClicked(false);
    }
  }

}

void Game::keyPressed(sf::Event event)
{
  if (in_menu)
  {
    init();
    if(event.key.code == sf::Keyboard::Escape) // Close Game
    {
      window.close();
    }
    if(event.key.code == sf::Keyboard::Enter) // Start Game
    {
      in_menu = false;
      in_game = true;
    }
  }
  if (in_game)
  {
    if(event.key.code == sf::Keyboard::Escape) // Return To Menu
    {
      in_game = false;
      in_menu = true;
    }
    if(event.key.code == sf::Keyboard::R)
    {
      init();
    }
  }
  if (player_lose || player_win)
  {
    if(event.key.code == sf::Keyboard::Enter) // Return To Menu
    {
      player_lose = false;
      player_win = false;
      in_menu = true;
    }
    if(event.key.code == sf::Keyboard::Escape) // Close Game
    {
      window.close();
    }
  }
}

void Game::keyReleased(sf::Event event)
{

}

bool Game::collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2) // Sprite Collision
{
  if(sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()))
  {
    return true;
  }
  else
  {
    return false;
  }
}


bool Game::collisionClickCheck(sf::Vector2i click, sf::Sprite sprite) // Mouse Collision
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2f click = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.contains(click))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}


