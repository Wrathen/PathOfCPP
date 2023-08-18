#include "ItemModifier.h"
#include <sstream>
#include "../../Miscellaneous/ErrorHandler.h"
#include "../../Miscellaneous/Random.h"

namespace Database {
	std::vector<ItemModifier> GetAllItemModifiers(ItemModPoolTypes modPoolType, uint32_t itemLevel, int optionalFlag) {
		// Do SQL query to retrieve all eligible DB_ItemModifiers for this ModPoolType and item level range.
		std::ostringstream query;
		query << "SELECT BaseItemModifiers.ID, BaseItemModifiers.Name, Tier, TypeID, BaseItemModifiers.Flags," <<
			" CoefMinValue1, CoefMaxValue1, CoefMinValue2, CoefMaxValue2," <<
			" CoefMinValue3, CoefMaxValue3, Weight, ItemLevel, Format" <<
			" FROM BaseItemModifiers" <<
			" INNER JOIN BaseItemModPool" <<
			" ON BaseItemModPool.ModPoolTypeID = " << (int)modPoolType <<
			" AND BaseItemModifiers.TypeID = BaseItemModPool.ModifierTypeID" <<
			" AND BaseItemModifiers.ItemLevel <= " << itemLevel;

		// If there is Flag Filtering enabled. (i.e. filtering for Prefixes only, or Suffixes!)
		if (optionalFlag != -1) {
			query << " INNER JOIN BaseItemModifierTypes" <<
					 " ON BaseItemModifiers.TypeID = BaseItemModifierTypes.ID" <<
					 " AND BaseItemModifiers.Flags = " << optionalFlag;
		}

		// Create a temp vector to hold all item modifiers.
		std::vector<ItemModifier> eligibleItemModifiers{};

		// Execute the query.
		DB.ExecuteQuery(query.str().c_str(), [](void* data, int argc, char** argv, char** azColName)
		{
			// Error Handling
			if (argc != 14)
				Abort("Provided argument count wasn't 14. This is against the design of BaseItemModifier Database Structure.", "Fatal Error");

			// Parse the Data and Create the ItemModifier
			ItemModifier modifier(
				std::atoi(argv[0]),			// ID              --  int
				argv[1],					// Name            --  string
				std::atoi(argv[2]),			// Tier            --  int
				std::atoi(argv[3]),			// TypeID          --  int
				std::atoi(argv[4]),			// Flags           --  int
				(float)std::atof(argv[5]),  // CoefMinValue1   --  float
				(float)std::atof(argv[6]),  // CoefMaxValue1   --  float
				(float)std::atof(argv[7]),  // CoefMinValue2   --  float
				(float)std::atof(argv[8]),  // CoefMaxValue2   --  float
				(float)std::atof(argv[9]),  // CoefMinValue3   --  float
				(float)std::atof(argv[10]), // CoefMaxValue3   --  float
				std::atoi(argv[11]),		// Weight          --  int
				std::atoi(argv[12]),		// ItemLevel       --  int 
				argv[13]					// Format          --  string
			);

			// Place the ItemModifier into the eligibleItemModifiers vector.
			((std::vector<ItemModifier>*)data)->emplace_back(modifier);

			return 0;
		}, &eligibleItemModifiers);

		return eligibleItemModifiers;
	}
	ItemModifier GetRandomItemModifier(ItemModPoolTypes modPoolType, uint32_t itemLevel) {
		std::vector<ItemModifier> allModifiers = GetAllItemModifiers(modPoolType, itemLevel);

		WeightedRandom<int> wr;

		// Put all eligible modifiers into the WeightedRandom vector.
		for (size_t i = 0; i < allModifiers.size(); ++i)
			wr.Add(i, allModifiers[i].Weight);

		return allModifiers[wr.GetRandom()];
	}
	ItemModifier GetRandomItemModifier(std::vector<ItemModifier>& itemModifiers) {
		WeightedRandom<int> wr;

		// Put all eligible modifiers into the WeightedRandom vector.
		for (size_t i = 0; i < itemModifiers.size(); ++i)
			wr.Add(i, itemModifiers[i].Weight);

		return itemModifiers[wr.GetRandom()];
	}
	std::vector<ItemModifier> GetRandomItemModifiers(std::vector<ItemModifier>& itemModifiers, uint32_t count) {
		if (itemModifiers.size() <= count) {
			// [@Todo] enable below back.
			//Abort("GetRandomItemModifiers function called with TOO MANY COUNTS!", "Runtime Error!");
			count = itemModifiers.size() - 1;
		}
		std::vector<ItemModifier> randomItemModifiers{};
		WeightedRandom<int> wr;

		// Put all eligible modifiers into the WeightedRandom vector.
		for (size_t i = 0; i < itemModifiers.size(); ++i)
			wr.Add(i, itemModifiers[i].Weight);

		// Fill the vector with random item modifiers.
		while (randomItemModifiers.size() != count) {
			Database::ItemModifier& randomMod = itemModifiers[wr.GetRandom()];

			// Check whether we already have this type of modifier.
			bool similarModExists = false;
			for (size_t j = 0; j < randomItemModifiers.size(); ++j) {
				if (randomItemModifiers[j].TypeID == randomMod.TypeID) {
					similarModExists = true;
					break;
				}
			}

			// If we passed the check, this randomly picked mod is fine and we can emplace it.
			if (!similarModExists)
				randomItemModifiers.push_back(randomMod);
		}

		return randomItemModifiers;
	}
}