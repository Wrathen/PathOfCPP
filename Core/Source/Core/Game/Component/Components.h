#pragma once
#include <unordered_map>
#include <entt.hpp>
#include "Core/Miscellaneous/Vector.h"
#include "Core/Miscellaneous/Timer.h"

enum class EntityType {
	NONE = 0,
	Player = 1,
	Monster = 2,
	NPC = 3,
	Portal = 4,
	Projectile = 5,
	VFX = 6
};
enum class MonsterRarity {
	Common = 0,
	Magic = 1,
	Rare = 2,
	Unique = 3,
	Count = 4
};
enum AbilityCostType {
	NONE = 0,
	Mana = 1,
	Rage = 2,
	Energy = 3
};

struct PlayerComponent {
	Timer attackTimer;
};

struct PortalComponent {
	std::string nextZone = std::string();
	bool isEnabled = true;

	PortalComponent() = default;
	PortalComponent(const PortalComponent&) = default;
	PortalComponent(const std::string& _nextZone) : nextZone(_nextZone) {}
};

struct EntityDetailsComponent {
	std::string name = "Unknown";
	EntityType type = EntityType::NONE;

	EntityDetailsComponent() = default;
	EntityDetailsComponent(const EntityDetailsComponent&) = default;
	EntityDetailsComponent(const std::string& _name, EntityType _type) : name(_name), type(_type) {}
};

struct TransformComponent {
	Vector2 position = Vector2(0, 0);
	Vector2 scale = Vector2(1, 1);
	Vector2 velocity = Vector2(0, 0);

	float rotation = 0;
	float scaleModifier = 1.0f;
	bool isAbsolutePositioned = false;
	bool isVelocityLocked = false; // Toggle to lock velocity at the current value and prevent changes.

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(Vector2 _position) : position(_position) {};
	TransformComponent(Vector2 _position, Vector2 _scale) : position(_position), scale(_scale) {};
	TransformComponent(Vector2 _position, Vector2 _scale, Vector2 _velocity) : position(_position), scale(_scale), velocity(_velocity) {};
};

struct HealthComponent {
	float health = 1;
	float maxHealth = 1;
	float healthMultiplier = 1.0f;

	HealthComponent() = default;
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(float _maxHealth) : health(_maxHealth), maxHealth(_maxHealth) {};
	HealthComponent(float _health, float _maxHealth, float _healthMultiplier)
		: health(_health), maxHealth(_maxHealth), healthMultiplier(_healthMultiplier) {};
};

struct BoxColliderComponent {
	Vector2 offset = { 0, 0 };
	size_t w = 16;
	size_t h = 16;
	bool isCentered = true; // This offsets the calculations to the center of the transform.
};

struct StatsComponent {
	// General Stats
	unsigned int level = 1;

	// Player-only --> will change the structure later
	float xp = 0;
	float maxXP = 2.4f;

	// Attributes
	int strength = 24;
	int dexterity = 27;
	int intelligence = -6;

	// Offensive
	float attackPower = 5;
	float haste = 0;
	float versatility = 0;

	// Projectiles
	unsigned int numberOfProjectiles = 1;
	float projectileSpeed = 35.00f;

	// Utility
	float moveSpeed = 300.0f;

	// Combat
	int totalKills = 0;

	// Attacking
	float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
	bool isAttacking = false;

	// Monster Specific
	bool dropsEnhancedLoot = false;

	// Power-Up Modifiers
	float increasedItemQuantity = 1.0f;
	float increasedItemRarity = 1.0f;
	float numberOfProjectileMultiplier = 1.0f;
	float leech = 0.0f;
	float strengthMultiplier = 1.0f;
	float moveSpeedMultiplier = 1.0f;
	float attackSpeedMultiplier = 1.0f;
	float luck = 1.0f;
	float chanceToGetDoubleLoot = 0.0f;
	bool hasCoinMagnet = false;
	float coinMagnetArea = 0.0f;
	int lastStandCount = 0;
	float projectileSpread = 0.20f;
	float projectileSpreadMultiplier = 1.0f;
	bool canCleave = false;
	float cleaveDamagePercentage = 0.0f;
	bool hasExplodyChest = false;
	float explodyChestChance = 0.0f;
	int piercingAmount = 1;
	float sizeMultiplier = 1.0f;
	float damageReductionAllSources = 0.0f;
	bool canCreateBlizzard = false;
	float blizzardCreationChanceOnCrit = 0.0f;
	float goldMultiplier = 1.0f;
	float damageMultiplier = 1.0f;
	float lootChanceMultiplier = 1.0f;
	bool hasReplicaHeadhunter = false;
	float chanceToGainRandomModOnReplicaHH = 0.0f;
	bool hasHeadhunter = true;
	float chanceToGainRandomModOnHH = 0.0f;
	float critDamageMultiplier = 1.0f;
	float critChance = 10.0f;
	float critMultiplier = 1.0f;
	float xpMultiplier = 1.0f;
};

struct MonsterDetailsComponent {
	MonsterRarity rarity = MonsterRarity::Common;
	unsigned int monsterID = 0;
	float lootChance = 4.12f;

	MonsterDetailsComponent() = default;
	MonsterDetailsComponent(const MonsterDetailsComponent&) = default;
	MonsterDetailsComponent(MonsterRarity _rarity, unsigned int _monsterID) : rarity(_rarity), monsterID(_monsterID) {};
};

struct MoveTowardsTargetComponent {
	entt::entity target = entt::null;
	bool isEnabled = true;
};

struct ProjectileComponent {
	uint64_t lifetime = 3000;
	int piercingAmount = 1;
	float damageAmount = 1;
};

struct BreachMonsterComponent {
	// temp, remove it
	float someVariableToAvoidCrashes = 0;
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
	std::vector<std::string> abilities{ "", "", "", "", "", "", "" };

	// Vector of all currently active ability instances by this entity.
	std::vector<struct AbilityComponent*> activeAbilities;
};

// A single ability.
struct AbilityComponent {
	// Generic
	int ID;
	std::string name;

	// Cost
	AbilityCostType costType;
	float cost;

	// Cooldown
	float baseCooldown;
	long long cooldownResetTime; // the time since epoch that the cooldown will reset at.

	// Specifies that the ability can be re-casted while there already are active instances of the same ability.
	bool uniqueInstance = true;
	
	AbilityComponent(int _ID, const std::string& _name, AbilityCostType _costType, float _cost, float _baseCooldown, long long _cooldownResetTime = 0, bool _uniqueInstance = true) :
					 ID(_ID), name(_name), costType(_costType), cost(_cost), baseCooldown(_baseCooldown), cooldownResetTime(_cooldownResetTime), uniqueInstance(_uniqueInstance) {}
};