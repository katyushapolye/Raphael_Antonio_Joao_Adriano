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
        sf::Listener::setGlobalVolume(40.0f);
    }
    
    void loadMusic(const std::string& musicName, const std::string& fileName){
        sf::Music* music = new sf::Music();
        if(music->openFromFile(fileName)){
            musicList[musicName]= music;
        }
        else{
            //tratando erros
            delete music;
            music=nullptr;
            std::cerr << "Erro: Nao existe um arquivo com esse nome" << std::endl;
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
            std::cerr << "Erro: Musica não encontrada ou não adicionada" << std::endl;
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
            delete buffer;
            buffer=nullptr; 
            std::cerr << "Erro: Nao existe um arquivo com esse nome" << std::endl;
        }
    }


    void playSound(const std::string& soundName){
        sf::SoundBuffer* buffer = soundBuffers[soundName];
        if (buffer){
            sf::Sound* sound = new sf::Sound(*buffer);
            sound->play();
            sounds.push_back(sound);
        }else{
            // Tratando erro
            std::cerr << "Erro: Som não encontrado ou não adicionado" << std::endl;
        }

        sounds.erase(
            std::remove_if(sounds.begin(), sounds.end(),
                [](sf::Sound* sound) {
                    return sound->getStatus() == sf::Sound::Stopped;
                }
            ),
            sounds.end()
        );
    }


    void stopAllSounds(){
        for(sf::Sound* sound: sounds){
            sound->stop();
            delete sound;
        }
        sounds.clear();
    }

    void stopSound(sf::Sound* sound){
        //talvez n seja utilizado
        auto soundIt = std::find(sounds.begin(), sounds.end(), sound);
        if (soundIt != sounds.end()){
            (*soundIt)->stop();
        }else{
            // Tratando erro
            std::cerr << "Erro: Som não encontrado" << std::endl;
        }
    }



    void pauseMusic(const std::string& musicName){
        std::map<std::string, sf::Music*>::iterator musicIt = musicList.find(musicName);
        if (musicIt != musicList.end()){
            sf::Music* music = musicIt->second;
            music->pause();
        }else{
            
            std::cerr << "Erro: Música não encontrada ou não adicionada" << std::endl;
        }
    }

    void pauseAllSounds(){
        for (sf::Sound* sound : sounds){
            sound->pause();
        }
    }
    void pauseAll(){
        for (auto& pair : musicList){
            sf::Music* music = pair.second;
            if (music->getStatus() == sf::SoundSource::Playing){
                music->pause();
            }
        }

        for (sf::Sound* sound : sounds){
            if (sound->getStatus() == sf::SoundSource::Playing){
                sound->pause();
            }
        }
    }

    void resumeAll(){
        for (auto& pair : musicList){
            sf::Music* music = pair.second;
            if (music->getStatus() == sf::SoundSource::Paused){
                music->play();
            }
        }

        for (sf::Sound* sound : sounds){
            if (sound->getStatus() == sf::SoundSource::Paused){
                sound->play();
            }
        }
    }
    //esse valor volumeFixo pode ser altererado na função de input no Game.cpp
    void increaseVolume(float volumeFixo){
        float currentVolume = sf::Listener::getGlobalVolume();
        float newVolume = currentVolume + volumeFixo;
        if(newVolume>100.0f){
            newVolume=100.0f;
        }
        sf::Listener::setGlobalVolume(newVolume);
    }

    void decreaseVolume(float volumeFixo){
        float currentVolume = sf::Listener::getGlobalVolume();
        float newVolume = currentVolume - volumeFixo;
        if(newVolume<0.0f){
            newVolume=0.0f;
        }
        sf::Listener::setGlobalVolume(newVolume);
    }
    //exemplo -> decreaseVolume(10.0f)

};



