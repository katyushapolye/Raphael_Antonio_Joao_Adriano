#include <SFML/Graphics.hpp>
#include <iostream>

class PauseScreen{
private:
    sf::Font fonte;
    sf::Text tituloPause;
    enum PauseMenuState{
        Credits,
        Exit,
        nOptions
    };
    
    PauseMenuState pauseMenuState;
    //sf::Text opcoes;
    //sf::Text creditos;
    //sf::Text sair;
public:
    PauseScreen(){
        pauseMenuState=Credits;
        //sf::RectangleShape resumeButton;
        //sf::RectangleShape creditsButton;
        //sf::RectangleShape exitButton;
        
        
        if(!fonte.loadFromFile("Resources/fonts/TimesNewPixel.ttf")){
            std::cout << "Erro ao carregar a fonte." << std::endl;
        }
        tituloPause.setFont(fonte);
        tituloPause.setCharacterSize(50);
        tituloPause.setFillColor(sf::Color::White);
        tituloPause.setString("Jogo Pausado");
        float tituloW= tituloPause.getGlobalBounds().width;
        float tituloH= tituloPause.getGlobalBounds().height;
        tituloPause.setOrigin(tituloW/2, tituloH/2);
        tituloPause.setPosition(216, 40);
        //resumeButton.setSize(sf::Vector2f(40,20));
        //creditsButton.setSize(sf::Vector2f(40,20));
        //exitButton.setSize(sf::Vector2f(40,20));
        //float buttonW= resumeButton.getGlobalBounds().width;
        //float buttonH= resumeButton.getGlobalBounds().height;
        //resumeButton.setOrigin(buttonW/2, buttonH/2);
        //creditsButton.setOrigin(buttonW/2, buttonH/2);
        //exitButton.setOrigin(buttonW/2, buttonH/2);
        //resumeButton.setPosition(216, 60);
        //creditsButton.setPosition(216, 80);
        //exitButton.setPosition(216, 100);


    }

    void draw(sf::RenderWindow& window){
        window.draw(tituloPause);   
        //sf::Event e;
        //while(window.pollEvent(e)){
        //    if(e.type==sf::Event::KeyPressed){
        //        if(e.key.code==sf::Keyboard::Up){
        //            
        //            pauseMenuState = static_cast<PauseMenuState>((pauseMenuState + nOptions - 1) % nOptions);
        //        }
        //        else if(e.key.code==sf::Keyboard::Down){
//
        //            pauseMenuState = static_cast<PauseMenuState>((pauseMenuState + 1) % nOptions);
        //        }
//
        //        else if(e.key.code==sf::Keyboard::Enter){
//
        //            switch(pauseMenuState){
        //                case Credits:
        //                    break;
        //                
        //                case Exit:
        //                    exit(-1);
        //                    break;
        //                default:
        //                    break;
//
        //            }
//
        //        }
        //        else if(e.key.code==sf::Keyboard::Escape){
        //            return;
        //        }
        //            
        //    }
        //}
    }

};