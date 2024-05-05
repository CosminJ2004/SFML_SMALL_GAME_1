#include "Game.h"
//private functions
void Game::initializeVariables()
{
	this->window = nullptr;
    //game logic
    this->points = 0;
    this->health = 100;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer= this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->endGame = false;



}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
 
    this->window=new sf::RenderWindow(sf::VideoMode(800, 600), "My first game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(60);
}
void Game::initEnemies()
{

    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);


}
void Game::initFonts()
{
    if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::GAME:: failed to load fonts" << "\n";
    }
}
void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}
//const and dest
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
    this->initEnemies();
    this->initFonts();
    this->initText();


}

Game::~Game()
{
	delete this->window;

}
//accesors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}



void Game::updateMousePositions()
{
  //return void
    //update the mouse positions
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << this->points<<"\n"
        <<"Health: "<<this->health;

    this->uiText.setString(ss.str());

}

void Game::updateEnemies()
{
    /**
    @return void
    updates the enemy spawn timer and spawns enemies
    when the total amount of enemies is smaller than the maximum
    moves the enemies down
    removes the enemies at the edger of the screen
    **/
    /// update the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {//spawn the enemy and reset the timer
         this->spawnEnemy();
        this->enemySpawnTimer = 0.f;
         }
        else
           this->enemySpawnTimer+=1.f;
    }
    //moving and uodateting enemies

    for( int i=0;i<this->enemies.size();i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 5.f);

        if (this->enemies[i].getPosition().y>this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";

        }

    }
    //check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
              

                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    
                    //gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                    this->points += 10;
                    else  if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else  if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else  if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;
                    std::cout << "Points: " << this->points << "\n";
                   
                    
                    //delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
    
   


}

void Game::pollEvents()
{
    //event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                this->window->close();

        default:
            break;
        }
    }
}

//functions
void Game::update()
{
    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePositions();

        this->updateText();
        this->updateEnemies();
    }
    if(this->health<=0)
    {
        this->endGame = true;
    }

}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::render()
{
    /*
    * @return void
    * clear old frame
    * redner objects
    * display frame in window
    * renders the game objects
    */
    this->window->clear();

    //draw game obj
   
    this->renderEnemies(*this->window);
    this->renderText(*this->window);


    this->window->display();
    


}
void Game::spawnEnemy()
{
    /*
    * Spawns enemies and sets their color and positions
    * -sets a random position
    * -sets a random color
    * -adds enemy to the vectpr
    * 
    */
    this->enemy.setPosition(
      static_cast<float>  (rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),0.f);
    //randomize enemy type
    int type = rand() % 5;
    switch (type)
    {
    case 0:
        this->enemy.setFillColor(sf::Color::Magenta);
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        break;
    case 1:
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        break;
    case 2:
        this->enemy.setFillColor(sf::Color::Red);
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        break;
    case 3:
        this->enemy.setFillColor(sf::Color::Cyan);
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        break;
    case 4:
        this->enemy.setFillColor(sf::Color::Green);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    default:
        this->enemy.setFillColor(sf::Color::Yellow);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
        
    }
    
  

    //spawn the enemy
    this->enemies.push_back(this->enemy);

    //remove enemies 

}