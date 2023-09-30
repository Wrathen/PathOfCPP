#pragma once
#include "Ability.h"

class Dash : public IAbility {
public:
	Dash(Entity* _caster) : IAbility(_caster, "Dash") {}

	virtual void Start() {}
	virtual void Update() {}
	virtual void Delete() {}
};