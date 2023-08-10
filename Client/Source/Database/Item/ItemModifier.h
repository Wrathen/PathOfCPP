#pragma once
#include "../../Managers/DatabaseManager.h"
#include <string>

// Namespace Global Typedefs
namespace Database {
	enum class ItemModPoolTypes {
		BodyArmourSTR = 1,
		BodyArmourDEX,
		BodyArmourINT,
		BodyArmourSTRDEX,
		BodyArmourSTRINT,
		BodyArmourDEXINT,
		BodyArmourSTRDEXINT,
		WeaponClaw,
		WeaponDagger,
		WeaponWand,
		WeaponSword1H,
		WeaponRapier,
		WeaponAxe1H,
		WeaponMace1H,
		WeaponSceptre,
		WeaponRuneDagger,
		WeaponBow,
		WeaponStaff,
		WeaponSword2H,
		WeaponAxe2H,
		WeaponMace2H,
		WeaponWarstaff,
		WeaponFishingRod,
		WeaponQuiver,
		WeaponShield
	};
	enum class ItemModifierTypes {
		IncArmour = 1,
		IncArmour_IncSBR,
		FlatArmour,
		FlatArmour_FlatMaxLife,
		FlatMaxLife,
		PhysReflectToMeleeAttackers,
		AdditionalPhysReduction,
		IncSBR,
		ReducedAttributeRequirements,
		FlatStrength,
		FlatFireResistance,
		FlatLightningResistance,
		FlatColdResistance,
		FlatChaosResistance,
		FlatLifeRegen,
		IncEvasion,
		IncEvasion_IncSBR,
		FlatEvasion,
		FlatEvasion_FlatMaxLife,
		FlatDexterity,
		FlatChanceToSuppressSpellDamage,
		IncEnergyShield,
		IncEnergyShield_IncSBR,
		FlatMaxEnergyShield,
		FlatMaxEnergyShield_FlatMaxLife,
		FlatMaxEnergyShield_FlatMaxMana,
		FlatMaxMana,
		FlatFasterStartOfEnergyShieldRecharge,
		FlatIntelligence,
		IncArmourEvasion,
		IncArmourEvasion_IncSBR,
		FlatArmour_FlatEvasion,
		IncArmourEnergyShield,
		IncArmourEnergyShield_IncSBR,
		FlatArmour_FlatMaxEnergyShield,
		IncEvasionEnergyShield,
		IncEvasionEnergyShield_IncSBR,
		FlatEvasion_FlatMaxEnergyShield,
		IncArmourEvasionEnergyShield,
		IncArmourEvasionEnergyShield_IncSBR
	};
	struct ItemModifier {
		int ID;
		std::string Name;
		int TypeID;
		int Tier;
		float CoefMinValue1;
		float CoefMaxValue1;
		float CoefMinValue2;
		float CoefMaxValue2;
		float CoefMinValue3;
		float CoefMaxValue3;
		int Weight;
		int MinLevel;
		int MaxLevel;
		std::string Format;

		// Constructor
		ItemModifier() = default;
		ItemModifier(int _ID, std::string _Name, int _TypeID, int _Tier,
						float _CoefMinValue1, float _CoefMaxValue1, float _CoefMinValue2, float _CoefMaxValue2,
						float _CoefMinValue3, float _CoefMaxValue3, int _Weight, int _MinLevel, int _MaxLevel, std::string _Format) :
			ID(_ID), Name(_Name), Tier(_Tier), TypeID(_TypeID), CoefMinValue1(_CoefMinValue1), CoefMaxValue1(_CoefMaxValue1),
			CoefMinValue2(_CoefMinValue2), CoefMaxValue2(_CoefMaxValue2), CoefMinValue3(_CoefMinValue3), CoefMaxValue3(_CoefMaxValue3),
			Weight(_Weight), MinLevel(_MinLevel), MaxLevel(_MaxLevel), Format(_Format) {}
		
		void PrintToConsole() {
			printf("[%d] %s - Weight: %d - Format: %s\n", ID, Name.c_str(), Weight, Format.c_str());
		}
	};
}