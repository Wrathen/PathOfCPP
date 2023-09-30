#include "PowerUp.h"
#include "../../Miscellaneous/Log.h"
#include "../../Managers/GameManager.h"
#include "../../Managers/CollisionManager.h"

#define NUMBER_OF_POWERUPS 32
static PowerUp* allPowerUps[NUMBER_OF_POWERUPS];

#define stats GAME.GetPlayer()->CStats
// Static Function
void PowerUp::InitAllPowerUps() {
	PowerUp* tempArray[] = { 
		new PowerUp { "Magic Finding", 
		"Increases Item Quantity by 10%.\nIncreases Item Rarity by 15%.",
		[] { stats->increasedItemQuantity += 0.1f; stats->increasedItemRarity += 0.15f; }},

		new PowerUp{ "Double Shot",
		"Doubles the amount of\n projectiles you fire.",
		[] { stats->numberOfProjectileMultiplier *= 2.0f; } },

		new PowerUp{ "Vampiric",
		"Increases Leech by 5%",
		[] { stats->leech += 5.0f; } },

		new PowerUp{ "Strength Seeker",
		"Increases Strength by 30%",
		[] { stats->strengthMultiplier += 0.30f; } },

		new PowerUp{ "Hasty",
		"Increases Move Speed by 8%\nIncreases Attack Speed by 12%",
		[] { stats->AddMoveSpeedMultiplier(0.08f); stats->attackSpeedMultiplier += 0.12f; }},

		new PowerUp{ "Lucky",
		"Increases Luck by 4%.",
		[] { stats->luck += 0.04f; }},

		new PowerUp{ "Plentiful Loot",
		"Chance to get double loot\nis increased by 0.25%",
		[] { stats->chanceToGetDoubleLoot += 0.025f; } },

		new PowerUp{ "Hazardous Results",
		"Increase Enemy Spawn Rate\n is increased by 0.25%\nAll non-boss enemies hit 18% harder.",
		[] { enemySpawnRateMultiplier += 0.025f; nonBossEnemyDamageMultiplier += 0.18f; } },

		new PowerUp{ "MANIAC!",
		"Increases Attack Speed by 25%",
		[] { stats->attackSpeedMultiplier += 0.25f; } },

		new PowerUp{ "Pull them over!",
		"Increases the magnetic range of coins by 3 units.\nCoins will move towards you.",
		[] { stats->hasCoinMagnet = true; stats->coinMagnetArea += 3.0f; } },

		new PowerUp{ "Last Stand",
		"Upon getting fatal damage, receive a Guardian Angel's aid\n, neglecting death. Can stack.",
		[] { ++stats->lastStandCount; } },

		new PowerUp{ "Healthy Diet",
		"Increases Maximum Health by 27%",
		[] {
			auto CHealth = GAME.GetPlayer()->CHealth;
			CHealth->SetHealthMultiplier(CHealth->GetHealthMultiplier() + 0.27f);
		}},

		new PowerUp{ "Hit two birds, with one stone",
		"Your projectiles are spread 30% more.",
		[] { stats->projectileSpreadMultiplier += 0.30f; } },

		new PowerUp{ "Sharing is Caring!",
		"Nearby enemies take 3% of the damage\n done to your main target.\nCan stack.",
		[] { stats->canCleave = true; stats->cleaveDamagePercentage += 0.03f; } },

		new PowerUp{ "Explody Chest",
		"Enemies have a 10% chance to explode on death\n dealing damage to nearby targets.\nCan stack.",
		[] { stats->hasExplodyChest = true; stats->explodyChestChance += 0.10f; } },

		new PowerUp{ "PIERCE!",
		"Your projectiles will pierce\nthrough 1 additional enemy.",
		[] { stats->SetPiercingAmount(stats->GetPiercingAmount() + 1); } },

		new PowerUp{ "Giant",
		"Increases Size by 30%.\nDecreases Move Speed by 4%.\nReceive 2% less damage from all sources.\n(Additive)",
		[] { stats->sizeMultiplier += 0.30f; stats->moveSpeedMultiplier -= 0.04f; stats->damageReductionAllSources += 0.02f; } },

		new PowerUp{ "Blizzard",
		"Critical Strikes has a 2% chance to spawn a Blizzard\ndealing 20% of your max life every 1.3 seconds",
		[] { stats->canCreateBlizzard = true; stats->blizzardCreationChanceOnCrit += 0.02f; } },

		new PowerUp{ "BLOODBORNE!",
		"Instantly kill nearby monsters.\nAll the loot is enhanced.",
		[] { float nearbyDistance = 800;
			 auto player = GAME.GetPlayer();
			 auto playerPos = player->transform.GetScreenPosition();
			 auto& allNearbyEnemies = CollisionMgr.spatialHash.QueryRange(playerPos.x, playerPos.y, nearbyDistance);
			 for (auto enemy : allNearbyEnemies) {
				 // @todo: Implement Entity Type and query based on type
				 // Below code is preventing projectiles getting destroyed.
				 if (!(enemy->flags & EntityFlags::IsMonster)) continue;
				 if (!enemy || enemy->isToBeDeleted) continue;
				 
				 // If the target entity has a Stats component, tag it's enhanced loot boolean to true.
				 if (Stats* enemyStats = enemy->GetComponent<Stats>())
					enemyStats->dropsEnhancedLoot = true;
				 
				 // Execute OnDeath events on enemy.
				 enemy->OnDeath();
			 }
		}},

		new PowerUp{ "Gold Goblin",
		"Lose 30% of your gold.\nIncrease all gold received by 10%.",
		[] { GAME.GetPlayer()->goldAmount *= 0.70f; stats->goldMultiplier += 0.10f; } },

		new PowerUp{ "LOOT, MORE LOOT!",
		"Decrease all damage done by 20%.\nIncrease loot chance by 14%",
		[] { stats->damageMultiplier -= 0.20f; stats->lootChanceMultiplier += 0.14f; } },

		new PowerUp{ "I am Speed",
		"Increase movement speed by 100%.",
		[] { stats->moveSpeedMultiplier += 1.00f; } },

		new PowerUp{ "Replica Headhunter",
		"3% chance when you kill a magic monster\ngain a random modifier.",
		[] { stats->hasReplicaHeadhunter = true; stats->chanceToGainRandomModOnReplicaHH += 0.03f; } },

		new PowerUp{ "Headhunter Leather Belt",
		"8% chance when you kill a rare monster\ngain a random modifier.",
		[] { stats->hasHeadhunter = true; stats->chanceToGainRandomModOnHH += 0.08f; } },

		new PowerUp{ "Double Crit Damage",
		"Critical Strikes deals 2 times more damage",
		[] { stats->critDamageMultiplier *= 2.0f; } },

		new PowerUp{ "Crit-ter",
		"Increases base critical chance by 4%\nIncreases critical chance multiplier\n by 60%",
		[] { stats->critChance += 0.04f; stats->critMultiplier += 0.60f; } },

		new PowerUp{ "Genius, or a fool",
		"Increase damage done by 100%.\nIncrease Attack Speed by 25%.\nDecrease enemy loot chance by 50%",
		[] { stats->damageMultiplier += 1.00f; stats->attackSpeedMultiplier += 0.25f; stats->lootChanceMultiplier -= 0.50f; } },

		new PowerUp{ "Satanic",
		"Increases leech by 3%.\nIncreases Attack Speed by 15%",
		[] { stats->leech += 0.03f; stats->attackSpeedMultiplier += 0.15f; } },

		new PowerUp{ "Guardian Angel",
		"Protects from all damage for 30 seconds.",
		[] { GAME.GetPlayer()->CHealth->SetGuardianAngel(30); }},

		new PowerUp{ "Quick Learner",
		"Increase all XP gain by 35%",
		[] { stats->xpMultiplier += 0.35f; } },

		new PowerUp{ "Make it harder",
		"Increase zone enemy level by 2.",
		[] { zoneMonsterLevelBonus += 2; } },

		new PowerUp{ "Sacrifice Gold",
		"Sacrifice 50% of your Gold.\nGain 50% Attack Speed.",
		[] { GAME.GetPlayer()->goldAmount *= 0.50f; stats->attackSpeedMultiplier += 0.50f; } }
	};

	static_assert(NUMBER_OF_POWERUPS == std::size(tempArray));
	memcpy(allPowerUps, tempArray, sizeof(allPowerUps));
}