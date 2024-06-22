#pragma once
#include "Core/Game/Component/Components.h"
#include "Core/Game/Scene/Scene.h"
#include <Core/Managers/SceneManager.h>

#pragma region Interfaces
enum class AbilityCostType {
	NONE = 0,
	Mana = 1,
	Rage = 2,
	Energy = 3
};

// Collection of Abilities, tracks active abilities, and ability keybindings.
struct AbilitySystemComponent {
	/*
		*	Vector of all added abilities to this entity.
		*
		*	Vector indexes are used as "Input Slot ID".
		*	[0] = LMB, [1] = RMB, [2] = Q, [3] = W, [4] = E, [5] = R, [6] = T
		*
		*   First 7 indexes are reserved and can be empty strings.
		*   Rest of the indexes are abilities that are given and can be activated without the usage of inputs.
		*/
	std::vector<int32_t> abilities{ -1, -1, -1, -1, -1, -1, -1 };

	// Vector of all currently active ability instances by this entity.
	std::vector<struct IAbilityInstance*> activeAbilities;
};

struct IAbilityPayload
{
	unsigned char* buffer;
	unsigned long long size, index;

	IAbilityPayload(unsigned long long _size)
	{
		size = _size;
		buffer = (unsigned char*)malloc(_size);
		index = 0; // current reading index at the buffer.
	}

	template<typename VarType>
	VarType read(bool resetIndex = false)
	{
		if (resetIndex) index = 0;

		VarType value;
		memcpy(&value, &buffer[index], sizeof(VarType));
		index += sizeof(VarType);
		return value;
	}

	template<typename VarType>
	void pack(VarType x, bool resetIndex = false) {
		if (resetIndex) index = 0;

		unsigned char* p = (unsigned char*)&x;
		for (size_t i = 0; i < sizeof(VarType); ++i)
			buffer[index++] = p[i];
	}
};

// A single ability instance.
struct IAbilityInstance {
	// Generic Data
	std::string name = "Unnamed";
	int32_t ID = -1;

	Core::Entity entity;
	Core::Entity* source; // instigator of this ability
	Core::Entity* target; // target of this ability

	// Cost
	AbilityCostType costType = AbilityCostType::NONE;
	float cost = 0.0f;

	// Cooldown
	float baseCooldown = 0.0f; // in seconds
	long long cooldownResetTime = 0; // the time since epoch that the cooldown will reset at.

	// Lifetime
	float baseLifetime = 3.0f; // in seconds
	long long deathTime = 0; // the time since epoch that the this instance will die at.

	// Specifies that the ability can be re-casted while there already are active instances of the same ability.
	bool uniqueInstance = false;

	// Events
	std::function<void()> onBegin = nullptr;
	std::function<void()> onDestroy = nullptr; // called by AbilityComponent

	// Virtual Functions
	virtual void Init(Core::Entity* _source, Core::Entity* _target)
	{
		source = _source;
		target = _target;

		cooldownResetTime = Time::GetTimeMS() + (long long)(baseCooldown * 1000.0f);
		deathTime = Time::GetTimeMS() + (long long)(baseLifetime * 1000.0f);
	}

	// Destructor
	~IAbilityInstance() { if (onDestroy) onDestroy(); }

	// Utility
	bool IsValid() { return ID != -1; }
};
#pragma endregion

#pragma region Ability Payloads
struct AP_Fireball : IAbilityPayload
{
	static inline unsigned long long STRUCT_SIZE = sizeof(int) + sizeof(float) * 5 + sizeof(uint64_t) + sizeof(int);

	int32_t abilityID = 0;
	float posX, posY, speed, angle, damageAmount;
	uint64_t lifetime;
	int piercingAmount;

	AP_Fireball(float _posX, float _posY, float _speed = 200.0f, float _angle = 90.0f,
		float _damageAmount = 30.0f, uint64_t _lifetime = 3000, int _piercingAmount = 1) : 
		posX(_posX), posY(_posY), speed(_speed), angle(_angle), damageAmount(_damageAmount),
		lifetime(_lifetime), piercingAmount(_piercingAmount), 
		IAbilityPayload(STRUCT_SIZE)
	{};

	IAbilityPayload Pack()
	{
		IAbilityPayload payload(STRUCT_SIZE);
		payload.pack(abilityID); payload.pack(posX); payload.pack(posY); payload.pack(speed);
		payload.pack(angle); payload.pack(damageAmount); payload.pack(lifetime); payload.pack(piercingAmount);
		return payload;
	}
	// To future devs: 
	// Do not try to make this a oneliner. 
	// Compilers try to optimize it by randomly calling the functions 
	// which ruins the order of execution/deserialization.
	static AP_Fireball Unpack(IAbilityPayload& payload)
	{
		/*int32_t _abilityID = */payload.read<int32_t>(true);
		float _posX = payload.read<float>();
		float _posY = payload.read<float>();
		float _speed = payload.read<float>();
		float _angle = payload.read<float>();
		float _damageAmount = payload.read<float>();
		uint64_t _lifetime = payload.read<uint64_t>();
		int _piercingAmount = payload.read<int>();
		return AP_Fireball(_posX, _posY, _speed, _angle, _damageAmount, _lifetime, _piercingAmount);
	}
};
struct AP_Dash : IAbilityPayload
{
	static inline unsigned long long STRUCT_SIZE = sizeof(int) + sizeof(float);

	int32_t abilityID = 1;
	float angle;

	AP_Dash(float _angle) : angle(_angle),
		IAbilityPayload(STRUCT_SIZE)
	{};

	IAbilityPayload Pack()
	{
		IAbilityPayload payload(STRUCT_SIZE);
		payload.pack(abilityID); payload.pack(angle);
		return payload;
	}
	static AP_Dash Unpack(IAbilityPayload& payload)
	{
		/*int32_t _abilityID = */payload.read<int32_t>(true);
		float _angle = payload.read<float>();
		return AP_Dash(_angle);
	}
};
#pragma endregion

#pragma region Ability Instances
struct A_Fireball : IAbilityInstance 
{
	AP_Fireball payload;
	A_Fireball(IAbilityPayload& _payload) : payload(AP_Fireball::Unpack(_payload))
	{
		// Configs
		name = "Fireball";
		ID = 0;
		costType = AbilityCostType::Mana;
		cost = 10.0f;
		baseCooldown = 0.15f;
		baseLifetime = 10.0f;
	}

	void Init(Core::Entity* _source, Core::Entity* _target) override
	{
		IAbilityInstance::Init(_source, _target);

		// Create In-Common Components.
		Core::BaseScene* scene = Core::SceneMgr.GetCurrentScene();
		entity = Core::Entity(scene, scene->SpawnProjectile(payload.posX, payload.posY, payload.speed, payload.angle, payload.lifetime, payload.piercingAmount, payload.damageAmount));

		// Events
		onDestroy = [&]() { if (entity) entity.Delete(); };
	}
};

struct A_Dash : IAbilityInstance 
{
	AP_Dash payload;
	A_Dash(IAbilityPayload& _payload) : payload(AP_Dash::Unpack(_payload))
	{
		// Configs
		name = "Dash";
		ID = 1;
		costType = AbilityCostType::Mana;
		cost = 10.0f;
		baseCooldown = 0.5f;
		uniqueInstance = true;
	}

	void Init(Core::Entity* _source, Core::Entity* _target) override
	{
		IAbilityInstance::Init(_source, _target);

		// Events
		onBegin = []() {
			std::cout << "Dash OnBegin\n";
		};
		onDestroy = []() {
			std::cout << "Dash OnDestroy\n";
		};
	}
};
#pragma endregion