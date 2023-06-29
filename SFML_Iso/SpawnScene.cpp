#include "SpawnScene.hpp"

SpawnScene::SpawnScene()
{
	Dbg::Log("[SpawnScene]     :     Spawn Scene CTOR called.");
}

SpawnScene::~SpawnScene()
{
	Dbg::Log("[SpawnScene]     :     Spawn Scene DTOR called.");
}

void SpawnScene::Init()
{
	LoadActors();

	m_mapLoader = std::make_shared<tmx::MapLoader>("../Assets/Maps/");

	m_mapLoader->load("test.tmx");
}

void SpawnScene::Update()
{
	for (auto i = 0; i < m_gameActors.size(); ++i) {
		m_gameActors[i]->Update();
	}
}

void SpawnScene::Render()
{

	m_window->draw(*m_mapLoader);

	for (auto i = 0; i < m_gameActors.size(); ++i) {
		m_gameActors[i]->Render();
	}
}

void SpawnScene::LoadActors()
{

	m_gameActors.push_back(std::make_shared<GPlayerActor>(GPlayerActor()));
	int t_gActorsAmount = 0;

	for (auto i = 0; i < m_gameActors.size(); ++i) {
		m_gameActors[i]->Init();
		m_gameActors[i]->SetWindowRef(m_window);
		++t_gActorsAmount;
	}
	
	Dbg::Log("[SpawnScene.LoadActors]     :     Loaded %d actors.", t_gActorsAmount);
}