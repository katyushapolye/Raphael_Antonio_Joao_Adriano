#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <vector>

class AudioHandler{
private:
    std::map<std::string, sf::SoundBuffer*> soundBuffers;
    std::map<std::string, sf::Music*> musicList;
    std::vector<sf::Sound*> sounds;
public:
    AudioHandler(){
        sf::Listener::setGlobalVolume(100.0f);
    }
    
    void loadMusic(const std::string& musicName, const std::string& fileName){
        sf::Music* music = new sf::Music();
        if(music->openFromFile(fileName)){
            musicList[musicName]= music;
        }
        else{
            //tratando erros
            std::cout<<"Nao existe um arquivo com esse nome"<<std::endl;
            delete music;
            music=nullptr;
            exit(-1);  
        }

        
    }

    void playMusic(const std::string& musicName, bool isInLoop){
        std::map<std::string, sf::Music*>::iterator musicIt= musicList.find(musicName);
        if(musicIt != musicList.end()){
            sf::Music* music = musicIt->second;
            music->setLoop(isInLoop);
            music->play();
        }
        else{
            //tratando erro
            std::cout<<"Musica não encontrada ou não adicionada"<<std::endl;
            exit(-1);
        }
    }

    void stopMusic(const std::string& musicName){
        sf::Music* music = musicList[musicName];
        if(music){
            music->stop();
        }

    }
    void stopAllMusics(){
        for(std::pair<const std::string, sf::Music*>&pair : musicList){
            sf::Music* music = pair.second;
            music->stop();
        }
    }

    void loadSound(const std::string& soundName, const std::string& fileName){
        sf::SoundBuffer* buffer= new sf::SoundBuffer();
        if(buffer->loadFromFile(fileName)){
            soundBuffers[soundName]=buffer;
        }
        else{
            //tratando erros
            std::cout<<"Nao existe um arquivo com esse nome"<<std::endl;
            delete buffer;
            buffer=nullptr;
            exit(-1);  
        }
    }

    void playSound(const std::string& soundName){
        sf::SoundBuffer* buffer = soundBuffers[soundName];
        if(buffer){
            sf::Sound* sound= new sf::Sound(*buffer);
            sound->play();
            sounds.push_back(sound);
        }

        sounds.erase(std::remove_if(sounds.begin(), sounds.end(),[](sf::Sound* sound){return sound->getStatus()== sf::Sound::Stopped;}),sounds.end());
    }

    void stopAllSounds(){
        for(sf::Sound* sound: sounds){
            sound->stop();
            delete sound;
        }
        sounds.clear();
    }
};


