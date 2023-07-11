#include <SFML/Graphics.hpp>
#include <iostream>

class PauseScreen{
private:
    sf::Font fonte;
    sf::Text tituloPause;
    int opcaoSelec;
    bool pauseFlag=true;
    
public:
    PauseScreen(){
        opcaoSelec=0;
        if(!fonte.loadFromFile("Resources/fonts/TimesNewPixel.ttf")){
            std::cout << "Erro ao carregar a fonte." << std::endl;
        }
        


    }
    void setOpZero(){
        opcaoSelec=0;
    }
    bool getPauseFlag(){
        return pauseFlag;
    }
    void setPauseFlag(){
        pauseFlag=true;
    }

    void draw(sf::RenderWindow& window, int x, int y){
        
        tituloPause.setFont(fonte);
        tituloPause.setCharacterSize(50);
        tituloPause.setFillColor(sf::Color::White);
        tituloPause.setString("Jogo Pausado");
        float tituloW= tituloPause.getGlobalBounds().width;
        float tituloH= tituloPause.getGlobalBounds().height;
        tituloPause.setOrigin(tituloW/2, tituloH/2);
        tituloPause.setPosition(x, y-120);
        window.draw(tituloPause);
        sf::Color selectColor = sf::Color::Red;
        sf::Color normalColor = sf::Color::White;
        int fontSize=26;
        float opSpace = 52.0f;
        float opW;
        float opH;
        float posY=tituloPause.getPosition().y + tituloPause.getGlobalBounds().height +10.0f;
        std::string options[]={"Resume", "Options", "Credits", "Exit"};
        for(int i=0; i<4; i++){
            sf::Text textoOpt;
            textoOpt.setFont(fonte);
            textoOpt.setCharacterSize(fontSize);
            textoOpt.setString(options[i]);
            opW= textoOpt.getGlobalBounds().width;
            opH= textoOpt.getGlobalBounds().height;
            textoOpt.setOrigin(opW/2, opH/2);
            textoOpt.setPosition(x, posY);

            if(i==opcaoSelec){
                textoOpt.setCharacterSize(32);
                textoOpt.setFillColor(selectColor);
            }else{
                textoOpt.setCharacterSize(26);
                textoOpt.setFillColor(normalColor);
            }

            window.draw(textoOpt);
            posY+= opSpace;
        }

        window.display();

    }
    void pauseHandleInput(sf::Event event){
        if(event.type==sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::Up){
                opcaoSelec=(opcaoSelec-1+4)%4;
            }
            else if(event.key.code==sf::Keyboard::Down){
                opcaoSelec=(opcaoSelec+1)%4;
            }
            else if(event.key.code==sf::Keyboard::Enter){
                switch(opcaoSelec){
                    case 0:   //Resume
                        pauseFlag=false;
                        break;

                    case 1:   //Options
                        break;
                    
                    case 2:   //Credits
                        break;
                    
                    case 3:   //Exit
                        exit(-1);
                        break;
                    
                    default:
                        break;
                }   
            }
        }
    }
        
};