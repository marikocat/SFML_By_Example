#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate()
{
	GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::MainMenu, "MainMenu.interface", "MainMenu");
	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.f, 168.f));
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	evMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
}

void State_MainMenu::OnDestroy()
{
	m_stateMgr->GetContext()->m_guiManager->
		RemoveInterface(StateType::MainMenu, "MainMenu");
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
	evMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
}

void State_MainMenu::Activate()
{
	auto& play = *m_stateMgr->GetContext()->m_guiManager->
		GetInterface(StateType::MainMenu, "MainMenu")->
		GetElement("Play");
	if (m_stateMgr->HasState(StateType::Game)) {
		// Resume
		play.SetText("Resume");
	}
	else {
		// Play
		play.SetText("Play");
	}
}

void State_MainMenu::Deactivate() {}
void State_MainMenu::Update(const sf::Time& l_time) {}

void State_MainMenu::Draw() {}

void State_MainMenu::Play(EventDetails* l_details)
{
	m_stateMgr->SwitchTo(StateType::Game);
}
void State_MainMenu::Quit(EventDetails* l_details)
{
	m_stateMgr->GetContext()->m_wind->Close();
}