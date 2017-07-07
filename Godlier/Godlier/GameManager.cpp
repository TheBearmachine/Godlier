#include "GameManager.h"
#include "GameStatePlaying.h"

static const char* TITLE = "Godlier";

GameManager::GameManager() :
	m_clock(), m_window(), m_eventManager()
{

	m_eventManager.registerObserver(this, sf::Event::EventType::KeyPressed);
}

GameManager::~GameManager()
{
	m_eventManager.unregisterObserver(this, sf::Event::EventType::KeyPressed);
}

void GameManager::run()
{
	if (!initalizeGame())
	{
		printf("Failed to initialize the game.\n");
		exit(-1);
	}
	gameLoop();
}

void GameManager::observe(const sf::Event & _event)
{
	switch (_event.type)
	{
	case sf::Event::EventType::Closed:
		close();
		break;
	case sf::Event::EventType::KeyPressed:
		if (_event.key.code == sf::Keyboard::Escape)
		{
			close();
		}

	default:
		break;
	}
}

bool GameManager::initalizeGame()
{
	if (!initalizeWindow())
	{
		printf("Failed to initalize window");
		return false;
	}
	srand((unsigned int)time(NULL));
	return true;
}

bool GameManager::initalizeWindow()
{
	sf::VideoMode video = sf::VideoMode::getDesktopMode();

	video.getDesktopMode();
	if (!video.isValid())
		return false;

	m_window.create(video, TITLE, sf::Style::Fullscreen);
	if (!m_window.isOpen())
		return false;

	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);

	return true;
}

void GameManager::close()
{
	m_window.close();
}

void GameManager::gameLoop()
{
	m_clock.restart();

	GameStatePlaying gameStatePlaying(&m_window, &m_eventManager);
	gameStatePlaying.setup();
	m_currentGameState = &gameStatePlaying;

	//mGameState->setup();
	while (m_window.isOpen())
	{

		m_currentGameState->handleEvents();
		m_currentGameState->update(m_clock);
		m_currentGameState->render();
	}
}

