#pragma once

#include <SFML/System.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* l_stateManager)
		: m_stateMgr(l_stateManager), m_transparent(false), m_transcendent(false) {}

	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& l_time) = 0;
	virtual void Draw() = 0;

	void SetTransparent(const bool& l_transparent)
	{
		m_transparent = l_transparent;
	}
	bool IsTransparent() const
	{
		return m_transparent;
	}

	void SetTranscendent(const bool& l_transcendent)
	{
		m_transcendent = l_transcendent;
	}
	bool IsTranscendent() const
	{
		return m_transcendent;
	}

	StateManager* GetStateManager()
	{
		return m_stateMgr;
	}
protected:
	StateManager* m_stateMgr;
	bool m_transparent;
	bool m_transcendent;
};