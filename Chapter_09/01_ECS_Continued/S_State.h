#pragma once

#include "S_Base.h"
#include "C_State.h"

class S_State : public S_Base
{
public:
	S_State(SystemManager* l_systemMgr);
	~S_State();

	void Update(float l_dT) override;
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
	void Notify(const Message& l_message) override;
private:
	void ChangeState(const EntityId& l_entity, const EntityState& l_state,
		const bool& l_force);
};