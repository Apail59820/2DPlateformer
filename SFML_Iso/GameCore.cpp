#include "GameCore.hpp"

GameEngineCore::GameEngineCore()
{
    m_windowWidth = 800;
    m_windowHeight = 600;
    m_windowTitle = "BaseRush";

    m_currentScene = std::make_unique<SpawnScene>(SpawnScene());

}

void GameEngineCore::Init()
{
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), m_windowTitle.c_str());

    m_eventsCore.Init(&m_window);
       
    m_currentScene->SetWindowRef(&m_window);
    m_currentScene->Init();
}

void GameEngineCore::Update()
{
    m_eventsCore.ProcessEvents();

    m_currentScene->Update();

    if (m_eventsCore.PGetWindowEvents()->Closed)
        m_window.close();
}

void GameEngineCore::Render()
{
    m_window.clear();

    m_currentScene->Render();

    m_window.display();
}

bool GameEngineCore::IsRunning()
{
    return m_window.isOpen();
}