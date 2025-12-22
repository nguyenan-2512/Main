#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "HashTable.h"

struct StringHash {
    std::size_t operator()(const std::string& str) const {
        std::size_t hash = 0;
        for (char c : str) {
            hash = hash * 31 + static_cast<std::size_t>(c);
        }
        return hash;
    }
};

class ResourceManager {
private:
    static ResourceManager* instance;

    HashTable<std::string, sf::Texture*, StringHash> textures;
    HashTable<std::string, sf::SoundBuffer*, StringHash> soundBuffers;
    ResourceManager() : textures(100), soundBuffers(50) {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

public:
    static ResourceManager* getInstance() {
        if (!instance) {
            instance = new ResourceManager();
        }
        return instance;
    }

    static void destroy() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }

    ~ResourceManager() {
        for (auto it = textures.begin(); it != textures.end(); ++it) {
            delete it->value;
        }
        textures.clear();

        for (auto it = soundBuffers.begin(); it != soundBuffers.end(); ++it) {
            delete it->value;
        }
        soundBuffers.clear();
    }

    sf::Texture* loadTexture(const std::string& key, const std::string& filePath) {
        sf::Texture* existingTex;
        if (textures.find(key, existingTex)) {
            return existingTex;
        }

        sf::Texture* tex = new sf::Texture();
        if (!tex->loadFromFile(filePath)) {
            delete tex;
            return nullptr;
        }

        tex->setSmooth(true);
        textures.insert(key, tex);
        return tex;
    }

    sf::Texture* getTexture(const std::string& key) {
        sf::Texture* tex;
        if (textures.find(key, tex)) {
            return tex;
        }
        return nullptr;
    }

    sf::SoundBuffer* loadSound(const std::string& key, const std::string& filePath) {
        sf::SoundBuffer* existingBuf;
        if (soundBuffers.find(key, existingBuf)) {
            return existingBuf;
        }

        sf::SoundBuffer* buf = new sf::SoundBuffer();
        if (!buf->loadFromFile(filePath)) {
            delete buf;
            return nullptr;
        }

        soundBuffers.insert(key, buf);
        return buf;
    }

    sf::SoundBuffer* getSound(const std::string& key) {
        sf::SoundBuffer* buf;
        if (soundBuffers.find(key, buf)) {
            return buf;
        }
        return nullptr;
    }

    void loadAllGameResources() {
        loadTexture("wall", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\da1.png");
        loadTexture("floor", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\co.png");
        loadTexture("player", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\playersheet2.png");
        loadTexture("box", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thunggo.png");
        loadTexture("box_on_goal", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\godung.png");
        loadTexture("steel_box", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thungsat.png");
        loadTexture("goal", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png");
        loadTexture("water", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nuoc222.png");
        loadTexture("bridge", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\caudoc.png");
        loadTexture("sand", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\cat.png");
        loadTexture("trap_active", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png");
        loadTexture("trap_inactive", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\huynutbam.png");
        loadTexture("button_unpressed", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\konutbam1.png");
        loadTexture("button_pressed", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nutbam1.png");
        loadTexture("obstacle", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png");
        loadTexture("teleport", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.jpg");

        loadSound("step", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg");
        loadSound("win", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg");
        loadSound("gameover", "D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg");

    }
};

ResourceManager* ResourceManager::instance = nullptr;