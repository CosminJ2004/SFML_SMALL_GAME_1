#include "Game.h"
//private functions
void Game::initializeVariables()
{
	this->window = nullptr;
    //game logic
    this->points = 0;
    this->health = 1000;
    
    this->endGame = false;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 1;
    this->mouseHeld1 = false;
    this->mouseHeld2 = false;
    this->mouseHeld3 = false;
    this->mouseHeld4 = false;

}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1200;
 
    this->window=new sf::RenderWindow(sf::VideoMode(1200, 800), "My first game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(60);
}


void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::GAME:: failed to load fonts" << "\n";
    }
}
void Game::initText()
{
    std::string pointsString = "Points: " + std::to_string(this->points);
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
   
    this->uiText.setString(pointsString);
    this->uiText.setPosition(15.f, 15.f);
    this->uiText.setStyle(sf::Text::Bold);
}
void Game::initScore()
{
    this->points=0;
    
}
void Game::initMusic()
{
    
    if (!this->music.openFromFile("Music/music21.mp3")) {
        std::cout << "Failed to load music" << std::endl;

    }
    else {
        music.setLoop(true);
        music.play(); // Play the music
    }
}
void Game::initPlayer()
{
    this->player = new Player();
    this->player->setPosition(10.f, 10.f);
    this->player->setHp(100);

    

}

void Game::initEnemies_top()
{
    texture1.loadFromFile("Textures/enemy1.png");


    this->enemy_top.setPosition(10.f, 10.f);
    //this->enemy_top.setSize(sf::Vector2f(100.f, 100.f));

  //  this->enemy_top.setFillColor(sf::Color::Cyan);
    //this->enemy_top.setOutlineColor(sf::Color::Green);
    //this->enemy_top.setOutlineThickness(1.f);


}
void Game::initEnemies_bottom()
{
    texture2.loadFromFile("Textures/enemy2.png");
    this->enemy_bottom.setPosition(10.f, 10.f);
    // this->enemy_bottom.setSize(sf::Vector2f(100.f, 100.f));

   //  this->enemy_bottom.setFillColor(sf::Color::Cyan);
     //this->enemy_top.setOutlineColor(sf::Color::Green);
     //this->enemy_top.setOutlineThickness(1.f);


}
void Game::initEnemies_left()
{
    texture3.loadFromFile("Textures/enemy3.png");
    this->enemy_left.setPosition(10.f, 10.f);

    // this->enemy_left.setSize(sf::Vector2f(100.f, 100.f));

    // this->enemy_left.setFillColor(sf::Color::Cyan);
     //this->enemy_top.setOutlineColor(sf::Color::Green);
     //this->enemy_top.setOutlineThickness(1.f);


}
void Game::initEnemies_right()
{
    texture4.loadFromFile("Textures/enemy4.png");
    texture5.loadFromFile("Textures/enemy5.png");
    texture6.loadFromFile("Textures/enemy6.png");
    bullet_texture.loadFromFile("Textures/bullet.png");
    this->enemy_right.setPosition(10.f, 10.f);
    //  this->enemy_right.setSize(sf::Vector2f(100.f, 100.f));

    //  this->enemy_right.setFillColor(sf::Color::Cyan);
      //this->enemy_top.setOutlineColor(sf::Color::Green);
      //this->enemy_top.setOutlineThickness(1.f);


}


void Game::initBoss()
{
    this->boss = new Boss();
    this->boss->setPosition(10.f, 10.f);
    this->boss->setHp(100);

}
void Game::initWorld()
{
    if (!this->worldBackgroundTex.loadFromFile("Textures/background2.png"))
    {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
    }
    sf::Vector2u windowSize = this->window->getSize();

    // Get the size of the texture
    sf::Vector2u textureSize = this->worldBackgroundTex.getSize();

    // Calculate the scale factors to fit the background to the window
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    // Set the scale of the background
    this->worldBackground.setScale(scaleX, scaleY);
    this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initHealthBar()
{
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(10.f, 10.f);
    this->playerHpBar.setSize(sf::Vector2f(10.f * this->player->getHpMax(), 10.f));



}
void Game::spawnEnemy_top()
{
    /*
    * Spawns enemies and sets their color and positions
    * -sets a random position
    * -sets a random color
    * -adds enemy_top to the vectpr
    *
    */
    this->enemy_top.setPosition(
        static_cast<float>  (rand() % static_cast<int>(this->window->getSize().x - this->enemy_top.getGlobalBounds().width)), 0.f);
    //randomize enemy_top type
    int type = rand() % 6;
    switch (type)
    {
    case 0:
        this->enemy_top.setTexture(texture1, true);
      

        break;
    case 1:
        this->enemy_top.setTexture(texture2, true); 
        
        break;
    case 2:
        this->enemy_top.setTexture(texture3, true);
 
        break;
    case 3:
        this->enemy_top.setTexture(texture4, true); 
        
        break;
    case 4:
        this->enemy_top.setTexture(texture5, true);
    
        break;
    case 5:
        this->enemy_top.setTexture(texture6, true); 
        
        
        break;

    }



    //spawn the enemy_top
    this->enemies_top.push_back(this->enemy_top);

    //remove enemies 

}
void Game::spawnEnemy_bottom()
{
    /*
    * Spawns enemies and sets their color and positions
    * -sets a random position
    * -sets a random color
    * -adds enemy_bottom to the vectpr
    *
`    */
    this->enemy_bottom.setPosition(
        static_cast<float>  (rand() % static_cast<int>(this->window->getSize().x - this->enemy_bottom.getGlobalBounds().width)), this->window->getSize().y - this->enemy_bottom.getGlobalBounds().height);
    //randomize enemy_bottom typl
    int type = rand() % 6;
    switch (type)
    {
    case 0:
        this->enemy_bottom.setTexture(texture1, true); 

        break;
    case 1:
        this->enemy_bottom.setTexture(texture2, true);
        break;
    case 2:
        this->enemy_bottom.setTexture(texture3, true); 
        break;
    case 3:
        this->enemy_bottom.setTexture(texture4, true); 
        break;
    case 4:
        this->enemy_bottom.setTexture(texture5, true);
       
        break;
    case 5:
      
        this->enemy_bottom.setTexture(texture6, true);
        break;

    }



    //spawn the enemy_bottom
    this->enemies_bottom.push_back(this->enemy_bottom);

    //remove enemies 

}
void Game::spawnEnemy_left()
{
    /*
    * Spawns enemies and sets their color and positions
    * -sets a random position
    * -sets a random color
    * -adds enemy_bottom to the vectpr
    *
`    */
    this->enemy_left.setPosition(
        0.f,
        static_cast<float>  (rand() % static_cast<int>(this->window->getSize().y - this->enemy_left.getGlobalBounds().height)));
    //randomize enemy_bottom type
    int type = rand() % 5;
    switch (type)
    {
    case 0:
        this->enemy_left.setTexture(texture1, true); 

        break;
    case 1:
        this->enemy_left.setTexture(texture2, true); 
        break;
    case 2:
        this->enemy_left.setTexture(texture3, true);
        break;
    case 3:
        this->enemy_left.setTexture(texture4, true);
        break;
    case 4:
        this->enemy_left.setTexture(texture5, true);
        break;
    case 5:
        this->enemy_left.setTexture(texture6, true); 
        break;

    }



    //spawn the enemy_bottom
    this->enemies_left.push_back(this->enemy_left);

    //remove enemies 

}
void Game::spawnEnemy_right()
{
    /*
    * Spawns enemies and sets their color and positions
    * -sets a random position
    * -sets a random color
    * -adds enemy_bottom to the vectpr
    *
`    */
    this->enemy_right.setPosition(
        this->window->getSize().x,
        static_cast<float>  (rand() % static_cast<int>(this->window->getSize().y - this->enemy_right.getGlobalBounds().height)));
    //randomize enemy_bottom type
    int type = rand() % 6;

    switch (type)
    {
    case 0:
       
        this->enemy_right.setTexture(texture1, true);

        break;
    case 1:
        
        this->enemy_right.setTexture(texture2, true);
        break;
    case 2:
       
        this->enemy_right.setTexture(texture3, true);
        break;
    case 3:
        
        this->enemy_right.setTexture(texture4, true);
        break;
    case 4:
        
        this->enemy_right.setTexture(texture5, true);
        break;
    case 5:
      
        this->enemy_right.setTexture(texture6, true);
        break;

    }



    //spawn the enemy_bottom
    this->enemies_right.push_back(this->enemy_right);

    //remove enemies 

}

//const and dest
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
    this->initPlayer();
    this->initEnemies_top();
    this->initEnemies_bottom();
    this->initEnemies_left();
    this->initEnemies_right();
    this->initWorld();
    this->initFonts();
    this->initText();
    this->initMusic();
    this->initHealthBar();
    this->initBoss();
   


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

void Game::updateHealthBar()
{
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(10.f, 10.f);
    this->playerHpBar.setSize(sf::Vector2f(10.f * this->player->getHp(), 10.f));



}
void Game::drawBullet(sf::Vector2f pos1, sf::Vector2f pos2)
{
    this->bullet.setTexture(this->bullet_texture);
    //this->currentFrame = sf::IntRect(pos1.x, pos2.y,abs( pos2.x-pos1.x), abs(pos2.y-pos2.y));
    //this->bullet.setTextureRect(this->currentFrame);
    this->bullet.setPosition(pos1.x, pos2.y);
    this->draw(*this->window);
}
void Game::draw(sf::RenderWindow& window) const {
    
        window.draw(this->bullet);
    
}

void Game::updateScore()
{
    this->points += 1;
    std::string pointsString = "Points: " + std::to_string(this->points);
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);

    this->uiText.setString(pointsString);
    this->uiText.setPosition(15.f, 15.f);
    this->uiText.setStyle(sf::Text::Bold);

}
void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
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

void Game::updateEnemies_top()
{
    /**
    @return void
    updates the enemy_top spawn timer and spawns enemies
    when the total amount of enemies is smaller than the maximum
    moves the enemies down
    removes the enemies at the edger of the screen
    **/
    /// update the timer for enemy_top spawning
    if (this->enemies_top.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {//spawn the enemy and reset the timer
            this->spawnEnemy_top();

            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //moving and uodateting enemies

    for (int i = 0;i < this->enemies_top.size();i++)
    {
        bool deleted_1 = false;

        this->enemies_top[i].move(0.f, 5.f);


        if (this->enemies_top[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies_top.erase(this->enemies_top.begin() + i);


        }



    }
    bool deleted_1 = false;
    for (size_t i = 0;i < this->enemies_top.size() && deleted_1 == false;i++)
    {
        if (this->enemies_top[i].getGlobalBounds().intersects(this->player->getBounds()))
        {
            this->enemies_top.erase(this->enemies_top.begin() + i);
            deleted_1 = true;
            std::cout << "hit" << "\n";
            this->player->loseHp(1);
            this->updateHealthBar();

        }
    }
    //check if clicked upon
    //this->mouseHeld = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld1 == false)
        {
            this->mouseHeld1 = true;
            bool deleted_1 = false;
            for (size_t i = 0; i < this->enemies_top.size() && deleted_1 == false; i++)
            {



                if (this->enemies_top[i].getGlobalBounds().contains(this->mousePosView))
                {

                    

                   //delete the enemy
                    this->drawBullet(this->player->getPos(), this->enemies_top[i].getPosition());
                    this->updateScore();
                    deleted_1 = true;
                    this->enemies_top.erase(this->enemies_top.begin() + i);

                }
            }
        }
       
       
    }
    else {
        this->mouseHeld1 = false;
    }




}
void Game::updateEnemies_left()
{
    /**
    @return void
    updates the enemy_top spawn timer and spawns enemies
    when the total amount of enemies is smaller than the maximum
    moves the enemies down
    removes the enemies at the edger of the screen
    **/
    /// update the timer for enemy_top spawning
    if (this->enemies_left.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {//spawn the enemy and reset the timer
            this->spawnEnemy_left();

            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //moving and uodateting enemies

    for (int i = 0;i < this->enemies_left.size();i++)
    {
        bool deleted_2 = false;

        this->enemies_left[i].move(5.f, 0.f);


        if (this->enemies_left[i].getPosition().x > this->window->getSize().x)
        {
            this->enemies_left.erase(this->enemies_left.begin() + i);


        }

    }
    bool deleted_2 = false;
    for (size_t i = 0;i < this->enemies_left.size() && deleted_2 == false;i++)
    {
        if (this->enemies_left[i].getGlobalBounds().intersects(this->player->getBounds()))
        {
            this->enemies_left.erase(this->enemies_left.begin() + i);
            deleted_2 = true;
            std::cout << "hit" << "\n";
            this->player->loseHp(1);
            this->updateHealthBar();
        }
    }
    //check if clicked upon;
    //this->mouseHeld = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
         
        if (this->mouseHeld2 == false)
        {
            
            this->mouseHeld2 = true;
            bool deleted_2 = false;

            for (size_t i = 0; i < this->enemies_left.size() && deleted_2 == false; i++)
            {


                if (this->enemies_left[i].getGlobalBounds().contains(this->mousePosView))
                {

                    this->drawBullet(this->player->getPos(), this->enemies_left[i].getPosition());
                    this->updateScore();
                    deleted_2 = true;
                    this->enemies_left.erase(this->enemies_left.begin() + i);

                }
            }
        }
        
        
    }
    else {
        this->mouseHeld2 = false;
    }




}
void Game::updateEnemies_bottom()
{
    /**
    @return void
    updates the enemy spawn timer and spawns enemies
    when the total amount of enemies is smaller than the maximum
    moves the enemies down
    removes the enemies at the edger of the screen
    **/
    /// update the timer for enemy spawning
    if (this->enemies_bottom.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {//spawn the enemy and reset the timer
            this->spawnEnemy_bottom();

            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //moving and uodateting enemies

    for (int i = 0;i < this->enemies_bottom.size();i++)
    {
        bool deleted_3 = false;

        this->enemies_bottom[i].move(0.f, -5.f);

        if (this->enemies_bottom[i].getPosition().y + this->enemies_bottom[i].getLocalBounds().height < 0)
        {
            this->enemies_bottom.erase(this->enemies_bottom.begin() + i);


        }

    }
    bool deleted_3 = false;
    for (size_t i = 0;i < this->enemies_bottom.size() && deleted_3 == false;i++)
    {
        if (this->enemies_bottom[i].getGlobalBounds().intersects(this->player->getBounds()))
        {
            this->enemies_bottom.erase(this->enemies_bottom.begin() + i);
            deleted_3 = true;
            std::cout << "hit" << "\n";
            this->player->loseHp(1);
            this->updateHealthBar();
        }
    }
    //check if clicked upon
   // this->mouseHeld = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld3 == false)
        {
            this->mouseHeld3 = true;
            bool deleted_3 = false;
            for (size_t i = 0; i < this->enemies_bottom.size() && deleted_3 == false; i++)
            {


                if (this->enemies_bottom[i].getGlobalBounds().contains(this->mousePosView))
                {

                    this->drawBullet(this->player->getPos(), this->enemies_bottom[i].getPosition());
                    //delete the enemy
                    this->updateScore();
                    deleted_3 = true;
                    this->enemies_bottom.erase(this->enemies_bottom.begin() + i);

                }
            }
        }
        
      
    }
    else {
        this->mouseHeld3 = false;
    }




}
void Game::updateEnemies_right()
{
    /**
    @return void
    updates the enemy spawn timer and spawns enemies
    when the total amount of enemies is smaller than the maximum
    moves the enemies down
    removes the enemies at the edger of the screen
    **/
    /// update the timer for enemy spawning
    if (this->enemies_right.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {//spawn the enemy and reset the timer
            this->spawnEnemy_right();

            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //moving and uodateting enemies

    for (int i = 0;i < this->enemies_right.size();i++)
    {
        bool deleted_4 = false;

        this->enemies_right[i].move(-5.f, 0.f);

        if (this->enemies_right[i].getPosition().x + this->enemies_right[i].getLocalBounds().width < 0)
        {
            this->enemies_right.erase(this->enemies_right.begin() + i);


        }

    }
    bool deleted_4 = false;
    for (size_t i = 0;i < this->enemies_right.size() && deleted_4 == false;i++)
    {

        if (this->enemies_right[i].getGlobalBounds().intersects(this->player->getBounds()))
        {
            this->enemies_right.erase(this->enemies_right.begin() + i);
            deleted_4 = true;
            std::cout << "hit" << "\n";
            this->player->loseHp(1);
            this->updateHealthBar();
        }
    }
    //check if clicked upon
    //this->mouseHeld = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld4 == false)
        {
            this->mouseHeld4 = true;
            deleted_4 = false;
            for (size_t i = 0; i < this->enemies_right.size() && deleted_4 == false; i++)
            {


                if (this->enemies_right[i].getGlobalBounds().contains(this->mousePosView))
                {

                    

                    //delete the enemy
                    this->drawBullet(this->player->getPos(), this->enemies_right[i].getPosition());
                    this->updateScore();
                    deleted_4 = true;
                    this->enemies_right.erase(this->enemies_right.begin() + i);

                }
            }
        }
        
        
    }
    else {
        this->mouseHeld4 = false;
    }




}
void Game::updatePlayer()
{
    this->player->update();
}
//functions
void Game::update()
{
    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePositions();
        //this->updateText();
        this->updateEnemies_top();
        
        this->updateEnemies_bottom();
       
        this->updateEnemies_left();
            
        this->updateEnemies_right();

        //this->updateInput();
        this->updatePlayer();
        //this->updateScore();
    }
    if(this->health<=0)
    {
        this->endGame = true;
    }

}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : this->enemies_top)
    {
        target.draw(e);
    }
    for (auto& e : this->enemies_bottom)
    {
        target.draw(e);
    }
    for (auto& e : this->enemies_left)
    {
        target.draw(e);
    }
    for (auto& e : this->enemies_right)
    {
        target.draw(e);
    }

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderHealthBar(sf::RenderTarget& target)
{
    target.draw(this->playerHpBar);
   
}
void Game::renderBullet(sf::RenderTarget& target)
{
    target.draw(this->bullet);
   
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
    this->renderWorld();

    //Draw all the stuffs
    this->player->render(*this->window);
   this->boss->render(*this->window);
    this->draw(*this->window);

    //draw game obj
   
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    this->renderHealthBar(*this->window);
   
    

    this->window->display();
    


}
