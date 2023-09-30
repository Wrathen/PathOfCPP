#pragma once
#include "Ability.h"

class Dash : public IAbility {
public:
	Dash(Entity* _caster) : IAbility(_caster) {}

	virtual void Start() {}
	virtual void Update() {}
	virtual void Delete() {}
};