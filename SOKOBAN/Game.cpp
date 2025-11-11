#include "Game.h"
#include <iostream>
using namespace std;

sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

Game::Game() :
    window(sf::VideoMode::getDesktopMode(), "Sokoban", sf::Style::Fullscreen),
    currentMap(nullptr),
    gameState(GameState::MENU),
    showWinMessage(false),
    showGameOverMessage(false),
    originalSize(800, 800),
    scaleX(1.0f),
    scaleY(1.0f),
    offsetX(0.0f),
    offsetY(0.0f) {

    window.setFramerateLimit(60);
    Animation::animationSpeed = 0.1f;

    // Setup fullscreen view
    setupFullscreen();

    // Load resources
    if (!backgroundMusic.openFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
        cerr << "Failed to load background music!" << endl;
    }

    if (!moveSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
        cerr << "Failed to load move sound!" << endl;
    }
    moveSound.setBuffer(moveSoundBuffer);

    if (!winSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
        cerr << "Failed to load win sound!" << endl;
    }
    winSound.setBuffer(winSoundBuffer);

    if (!gameOverSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg")) {
        cerr << "Failed to load game over sound!" << endl;
    }
    gameOverSound.setBuffer(gameOverSoundBuffer);

    if (!winTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win.png")) {
        cerr << "Failed to load win message texture!" << endl;
    }
    winSprite.setTexture(winTexture);
    winSprite.setPosition(0, 0);

    if (!gameOverTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\gameover.png")) {
        cerr << "Failed to load game over texture!" << endl;
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);

    menu.loadResources();

    std::cout << "=== FULLSCREEN MODE ===" << std::endl;
    std::cout << "Screen Resolution: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    std::cout << "Game Resolution: " << originalSize.x << "x" << originalSize.y << std::endl;
    std::cout << "Scale: " << scaleX << "x" << scaleY << std::endl;
    std::cout << "Offset: (" << offsetX << ", " << offsetY << ")" << std::endl;
    std::cout << "Press ESC to exit fullscreen" << std::endl;
}

Game::~Game() {
    cleanupGame();
}

void Game::setupFullscreen() {
    // Lấy kích thước màn hình thực tế
    sf::Vector2u screenSize = window.getSize();

    // Tính tỷ lệ scale để giữ aspect ratio (800:800 = 1:1)
    float screenRatio = static_cast<float>(screenSize.x) / static_cast<float>(screenSize.y);
    float gameRatio = static_cast<float>(originalSize.x) / static_cast<float>(originalSize.y);

    if (screenRatio > gameRatio) {
        // Màn hình rộng hơn -> letterbox trái phải
        scaleY = static_cast<float>(screenSize.y) / static_cast<float>(originalSize.y);
        scaleX = scaleY;
        offsetX = (screenSize.x - (originalSize.x * scaleX)) / 2.0f;
        offsetY = 0.0f;
    }
    else {
        // Màn hình cao hơn -> letterbox trên dưới
        scaleX = static_cast<float>(screenSize.x) / static_cast<float>(originalSize.x);
        scaleY = scaleX;
        offsetX = 0.0f;
        offsetY = (screenSize.y - (originalSize.y * scaleY)) / 2.0f;
    }

    // Tạo view với kích thước gốc
    gameView.setSize(static_cast<float>(originalSize.x), static_cast<float>(originalSize.y));
    gameView.setCenter(static_cast<float>(originalSize.x) / 2.0f, static_cast<float>(originalSize.y) / 2.0f);

    // Tính viewport (phần hiển thị trên màn hình, tính theo tỷ lệ 0-1)
    float viewportX = offsetX / static_cast<float>(screenSize.x);
    float viewportY = offsetY / static_cast<float>(screenSize.y);
    float viewportWidth = (originalSize.x * scaleX) / static_cast<float>(screenSize.x);
    float viewportHeight = (originalSize.y * scaleY) / static_cast<float>(screenSize.y);

    gameView.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));

    window.setView(gameView);
}

void Game::updateView() {
    window.setView(gameView);
}

sf::Vector2i Game::getScaledMousePosition(const sf::Vector2i& mousePos) {
    // Chuyển đổi tọa độ chuột từ màn hình thực -> tọa độ game (800x800)
    float scaledX = (mousePos.x - offsetX) / scaleX;
    float scaledY = (mousePos.y - offsetY) / scaleY;

    // Clamp để đảm bảo trong phạm vi game
    scaledX = std::max(0.0f, std::min(scaledX, static_cast<float>(originalSize.x)));
    scaledY = std::max(0.0f, std::min(scaledY, static_cast<float>(originalSize.y)));

    return sf::Vector2i(static_cast<int>(scaledX), static_cast<int>(scaledY));
}

void Game::run() {
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // THÊM: Cho phép thoát fullscreen bằng ESC khi ở menu
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (gameState == GameState::MENU) {
                window.close();
            }
        }

        if (gameState == GameState::MENU) {
            // Chuyển đổi tọa độ chuột trước khi gửi cho menu
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i scaledPos = getScaledMousePosition(sf::Mouse::getPosition(window));
                sf::Event scaledEvent = event;
                scaledEvent.mouseButton.x = scaledPos.x;
                scaledEvent.mouseButton.y = scaledPos.y;
                menu.handleEvent(scaledEvent, window);
            }
            else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i scaledPos = getScaledMousePosition(sf::Mouse::getPosition(window));
                sf::Event scaledEvent = event;
                scaledEvent.mouseMove.x = scaledPos.x;
                scaledEvent.mouseMove.y = scaledPos.y;
                menu.handleEvent(scaledEvent, window);
            }
            else {
                menu.handleEvent(event, window);
            }
        }
        else if (gameState == GameState::PLAYING) {
            if (showWinMessage || showGameOverMessage) {
                if (event.type == sf::Event::KeyPressed) {
                    gameState = GameState::MENU;
                    menu.setState(MenuState::MENU);
                    cleanupGame();
                    showWinMessage = false;
                    showGameOverMessage = false;
                    backgroundMusic.play();
                }
            }
            else {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        gameState = GameState::MENU;
                        menu.setState(MenuState::MENU);
                        cleanupGame();
                    }
                    else if (event.key.code == sf::Keyboard::R) {
                        initializeGame();
                    }
                    else if (event.key.code == sf::Keyboard::U) {
                        if (currentMap) {
                            currentMap->undo();
                            cout << "Undo! Con lai " << currentMap->getMoveCount() << " nuoc di." << endl;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::T) {
                        if (currentMap) {
                            bool teleported = currentMap->tryTeleport();
                            if (teleported) {
                                playMoveSound();
                            }
                        }
                    }
                    else if (currentMap) {
                        bool moved = false;
                        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                            moved = currentMap->tryMovePlayer(0, -1);
                        }
                        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                            moved = currentMap->tryMovePlayer(0, 1);
                        }
                        else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                            moved = currentMap->tryMovePlayer(-1, 0);
                        }
                        else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                            moved = currentMap->tryMovePlayer(1, 0);
                        }
                        else if (event.key.code == sf::Keyboard::H) {
                            if (currentMap && !currentMap->getIsAutoSolving()) {
                                std::cout << "\nDang tim kiem solution voi BFS..." << std::endl;
                                if (currentMap->solveBFS(200)) {
                                    currentMap->startAutoSolve();
                                }
                                else {
                                    std::cout << "Khong tim thay solution!" << std::endl;
                                }
                            }
                        }
                        else if (event.key.code == sf::Keyboard::J) {
                            if (currentMap) {
                                currentMap->stopAutoSolve();
                                std::cout << "Da dung auto-solve" << std::endl;
                            }
                        }

                        if (moved) {
                            playMoveSound();
                        }
                    }
                }
            }
        }
    }
}

void Game::playMoveSound() {
    moveSound.play();
}

void Game::update() {
    float deltaTime = deltaClock.restart().asSeconds();

    if (gameState == GameState::MENU) {
        menu.update();

        MenuState menuState = menu.getState();
        if (menuState == MenuState::PLAYING) {
            gameState = GameState::PLAYING;
            initializeGame();
            if (currentMap && currentMap->getPlayer()) {
                currentMap->getPlayer()->update(deltaTime);
            }
            showWinMessage = false;
            showGameOverMessage = false;
        }
        else if (menuState == MenuState::EXIT) {
            window.close();
        }
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap && currentMap->getPlayer()) {
            currentMap->getPlayer()->update(deltaTime);
        }

        if (currentMap && currentMap->getGameOver() && !showGameOverMessage) {
            showGameOverMessage = true;
            gameOverSound.play();
            backgroundMusic.stop();
            cout << "Game Over! Nhan R de choi lai hoac ESC de quay ve Menu." << endl;
        }

        if (currentMap && currentMap->checkWin() && !showWinMessage && !showGameOverMessage) {
            showWinMessage = true;
            winSound.play();
            backgroundMusic.stop();
            cout << "Chuc mung! Ban da chien thang!" << endl;
        }

        if (currentMap && currentMap->getIsAutoSolving()) {
            static sf::Clock autoSolveClock;
            if (autoSolveClock.getElapsedTime().asSeconds() >= 0.3f) {
                currentMap->executeNextSolutionStep();
                autoSolveClock.restart();
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Đặt view để vẽ với tỷ lệ đúng
    updateView();

    window.draw(backgroundSprite);

    if (gameState == GameState::MENU) {
        menu.draw(window);
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap) {
            currentMap->draw(window);

            if (showGameOverMessage) {
                sf::RectangleShape overlay(sf::Vector2f(800, 800));
                overlay.setFillColor(sf::Color(0, 0, 0, 180));
                window.draw(overlay);

                window.draw(gameOverSprite);

                sf::Font font;
                if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text instruction;
                    instruction.setFont(font);
                    instruction.setString("Nhan R de choi lai | ESC de quay ve Menu");
                    instruction.setCharacterSize(18);
                    instruction.setFillColor(sf::Color::Red);
                    instruction.setPosition(270, 765);
                    window.draw(instruction);
                }
            }

            if (showWinMessage) {
                sf::RectangleShape overlay(sf::Vector2f(800, 800));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));
                window.draw(overlay);

                window.draw(winSprite);

                sf::Font font;
                if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text instruction;
                    instruction.setFont(font);
                    instruction.setString("Nhan phim bat ky de quay ve Menu");
                    instruction.setCharacterSize(18);
                    instruction.setFillColor(sf::Color::Green);
                    instruction.setPosition(280, 765);
                    window.draw(instruction);
                }
            }
        }
    }

    window.display();
}

void Game::initializeGame() {
    cleanupGame();

    int selectedMap = menu.getSelectedMap();
    if (selectedMap < 0) {
        selectedMap = 0;
    }

    std::string mapFileName = "map" + std::to_string(selectedMap + 1) + ".txt";
    std::cout << "Loading map: " << mapFileName << std::endl;

    currentMap = new Map(mapFileName, 32);
    std::cout << "Game initialized with " << mapFileName << "!" << std::endl;
}

void Game::cleanupGame() {
    if (currentMap) {
        delete currentMap;
        currentMap = nullptr;
    }
}