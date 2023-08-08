#pragma once
#include "Component.h"

static float enemySpawnRateMultiplier = 1.0f;
static float nonBossEnemyDamageMultiplier = 1.0f;
static float zoneMonsterLevelBonus = 0;

class Stats: public Component {
public:
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
    float moveSpeed = 25.0f;

	// Combat
	int totalKills = 0;

    // Attacking
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;

	// Monster Specific
	bool dropsEnhancedLoot = false;

	// Power-Up Modifiers
	static float enemySpawnRateMultiplier;
	static float nonBossEnemyDamageMultiplier;
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

	// Power-up Modifier Functions
	float inline GetLeech() const { return leech; }
	float inline GetIIQ() const { return increasedItemQuantity; }
	float inline GetIIR() const { return increasedItemRarity; }
	float inline GetChanceToDoubleLoot() const { return chanceToGetDoubleLoot; }
	bool inline HasCoinMagnet() const { return hasCoinMagnet; } // To:Do
	float inline GetCoinMagnetArea() const { return coinMagnetArea; } // To:Do
	int inline GetLastStandCount() const { return lastStandCount; }
	bool inline CanCleave() const { return canCleave; } // To:Do
	float inline GetCleaveDamagePercentage() const { return cleaveDamagePercentage; }; // To:Do
	bool inline HasExplodyChest() const { return hasExplodyChest; } // To:Do
	float inline GetExplodyChestChance() const { return explodyChestChance; } // To:Do
	float inline GetDamageReduction() const { return damageReductionAllSources; } // To:Do
	bool inline CanCreateBlizzard() const { return canCreateBlizzard; } // To:Do
	float inline GetBlizzardCreationChanceOnCrit() const { return blizzardCreationChanceOnCrit; } // To:Do
	float inline GetGoldMultiplier() const { return goldMultiplier; }// To:Do
	float inline GetLootChanceMultiplier() const { return lootChanceMultiplier; }// To:Do
	bool inline HasReplicaHH() const { return hasReplicaHeadhunter; }// To:Do
	bool inline HasHH() const { return hasHeadhunter; }// To:Do
	float inline GetReplicaHHChance() const { return chanceToGainRandomModOnReplicaHH; }// To:Do
	float inline GetHHChance() const { return chanceToGainRandomModOnHH; }// To:Do
	float inline GetCritDamageMultiplier() const { return critDamageMultiplier; }// To:Do
	float inline GetXPMultiplier() const { return xpMultiplier; }// To:Do

	// Getters
	unsigned int inline GetNumberOfProjectiles() const { return numberOfProjectiles * numberOfProjectileMultiplier; }
	unsigned int inline GetLevel() const { return level; }
	float inline GetStrength() const { return strength * strengthMultiplier; }
	float inline GetXP() const { return xp; }
	float inline GetMaxXP() const { return maxXP; }
	float inline GetMoveSpeed() const { return moveSpeed * moveSpeedMultiplier; }
	float inline GetAttackPower() const { return attackPower; }
	float inline GetHaste() const { return haste; }
	float inline GetCritChance() const { return critChance * critMultiplier; }
	float inline GetCritMultiplier() const { return critMultiplier; }
	float inline GetVersatility() const { return versatility; }
	float inline GetProjectileSpeed() const { return projectileSpeed; }
	float inline GetProjectileSpread() const { return projectileSpread * projectileSpreadMultiplier; }
	float inline GetAttackSpeed() const { return attackSpeed / attackSpeedMultiplier; }
	float inline GetSizeMultiplier() const { return sizeMultiplier; }
	float inline GetDamageAmount() const { return (GetAttackPower() + GetStrength() / 24) * damageMultiplier; }
	int inline GetPiercingAmount() const { return piercingAmount; }
	bool inline GetAttackingState() const { return isAttacking; }

	// Setters
	void SetLevel(unsigned int value) { level = value; }
	void SetXP(float value) { xp = value; }
	void SetMaxXP(float value) { maxXP = value; }
	void SetMoveSpeed(float value) { moveSpeed = value; }
	void SetAttackPower(float value) { attackPower = value; }
	void SetHaste(float value) { haste = value; }
	void SetCritChance(float value) { critChance = value; }
	void SetCritMultiplier(float value) { critMultiplier = value; }
	void SetProjectileSpeed(float value) { projectileSpeed = value; }
	void SetAttackSpeed(float value) { attackSpeed = value; }
	void SetAttackingState(bool value) { isAttacking = value; }
	void SetSizeMultiplier(float value) { sizeMultiplier = value; source->transform.SetScaleModifier(value); }
	void SetNumberOfProjectiles(unsigned int value) { numberOfProjectiles = value; }
	void SetPiercingAmount(int value) { piercingAmount = value; }

	void ResetPowerUps() {
		// To-Do Change all of the structure here.
		// Stats that are associated with Powerups should be named with prefix P_
		// Below code is temporary

		SetSizeMultiplier(1.0f);
		source->transform.SetScale(2.2f, 2.2f);
		level = 1;
		xp = 0;
		maxXP = 2.4f;
		strength = 24;
		dexterity = 27;
		intelligence = -6;
		attackPower = 5;
		haste = 0;
		versatility = 0;
		numberOfProjectiles = 1;
		projectileSpeed = 600.00f;
		moveSpeed = 300.0f;
		totalKills = 0;
		attackSpeed = 0.3f;

		numberOfProjectileMultiplier = 1.0f;
		leech = 0.0f;
		strengthMultiplier = 1.0f;
		moveSpeedMultiplier = 1.0f;
		attackSpeedMultiplier = 1.0f;
		luck = 1.0f;
		chanceToGetDoubleLoot = 0.0f;
		hasCoinMagnet = false;
		coinMagnetArea = 0.0f;
		lastStandCount = 0;
		projectileSpread = 0.20f;
		projectileSpreadMultiplier = 1.0f;
		canCleave = false;
		cleaveDamagePercentage = 0.0f;
		hasExplodyChest = false;
		explodyChestChance = 0.0f;
		piercingAmount = 1;
		sizeMultiplier = 1.0f;
		damageReductionAllSources = 0.0f;
		canCreateBlizzard = false;
		blizzardCreationChanceOnCrit = 0.0f;
		goldMultiplier = 1.0f;
		damageMultiplier = 1.0f;
		lootChanceMultiplier = 1.0f;
		hasReplicaHeadhunter = false;
		chanceToGainRandomModOnReplicaHH = 0.0f;
		hasHeadhunter = true;
		chanceToGainRandomModOnHH = 0.0f;
		critDamageMultiplier = 1.0f;
		critChance = 10.0f;
		critMultiplier = 1.0f;
		xpMultiplier = 1.0f;
	}

	// Enforced Method by Component Base Class
	void Start() { }
	void Delete() { delete this; }
};