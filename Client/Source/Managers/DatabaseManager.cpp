#include "DatabaseManager.h"
#include "../Miscellaneous/ErrorHandler.h"
#include "../Miscellaneous/Random.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<DB_ItemModifier> DatabaseManager::GetAllItemModifiers(DB_ItemModPoolTypes modPoolType, uint32_t itemLevel) {
	// Do SQL query to retrieve all eligible DB_ItemModifiers for this ModPoolType and item level range.
	std::ostringstream query;
	query << "SELECT BaseItemModifiers.ID, Name, Tier, CoefMinValue1, CoefMaxValue1, CoefMinValue2, CoefMaxValue2," <<
			 " CoefMinValue3, CoefMaxValue3, Weight, MinLevel, MaxLevel, Format" << 
			 " FROM BaseItemModifiers" << 
			 " INNER JOIN BaseItemModPool" <<
			 " ON BaseItemModPool.ModPoolTypeID = " << (int)modPoolType <<
			 " AND BaseItemModifiers.TypeID = BaseItemModPool.ModifierTypeID" <<
			 " AND BaseItemModifiers.MinLevel <= " << itemLevel;

	// Print out Query
	//std::cout << "\n" << query.str().c_str();
	
	// Create a temp vector to hold all item modifiers.
	std::vector<DB_ItemModifier> eligibleItemModifiers{};

	// Execute the query.
	char* errorMsg;
	int resultCode = sqlite3_exec(db, query.str().c_str(), [](void* data, int argc, char** argv, char** azColName)
		{
			// Error Handling
			if (argc != 13)
				Abort("Provided argument count wasn't 13. This is against the design of BaseItemModifier Database Structure.", "Fatal Error");
			
			// Parse the Data and Create the ItemModifier
			DB_ItemModifier modifier(
				std::atoi(argv[0]),			// ID              --  integer
				argv[1],					// Name            --  string
				std::atoi(argv[2]),			// Tier            --  integer
				(float)std::atof(argv[3]),  // CoefMinValue1   --  float
				(float)std::atof(argv[4]),  // CoefMaxValue1   --  float
				(float)std::atof(argv[5]),  // CoefMinValue2   --  float
				(float)std::atof(argv[6]),  // CoefMaxValue2   --  float
				(float)std::atof(argv[7]),  // CoefMinValue3   --  float
				(float)std::atof(argv[8]),  // CoefMaxValue3   --  float
				std::atoi(argv[9]),			// Weight          --  int
				std::atoi(argv[10]),		// MinLevel        --  int 
				std::atoi(argv[11]),		// MaxLevel        --  int
				argv[12]					// Format          --  string
			);

			// Place the ItemModifier into the eligibleItemModifiers vector.
			((std::vector<DB_ItemModifier>*)data)->emplace_back(modifier);

			return 0;
		}, &eligibleItemModifiers, &errorMsg);

	// Error Handling.
	if (resultCode != 0)
		printf("\n\nresult: %d\nerror msg: %s", resultCode, errorMsg);

	return eligibleItemModifiers;
}
DB_ItemModifier DatabaseManager::GetRandomItemModifier(DB_ItemModPoolTypes modPoolType, uint32_t itemLevel) {
	auto allModifiers = GetAllItemModifiers(modPoolType, itemLevel);
	
	WeightedRandom<int> wr;

	// Put all eligible modifiers into the WeightedRandom vector.
	for (size_t i = 0; i < allModifiers.size(); ++i)
		wr.Add(i, allModifiers[i].Weight);

	// Pick a random one.
	// [@todo] for loop 10k times isn't necessary, just doing it to see that its really weighted random, and it works.
	for (int i = 0; i < 10000; ++i) {
		DB_ItemModifier randomItemModifier = allModifiers[wr.GetRandom()];
		randomItemModifier.PrintToConsole();
	}

	return allModifiers[wr.GetRandom()];
}

// Ctor & Dtor ~~ Handle opening&closing of the Database Connection.
void DatabaseManager::Init() { 
	if (sqlite3_open("Assets/Databases/PoC.db", &db) != SQLITE_OK)
		Abort("Couldn't connect to the Database.\n\nDatabase file might be corrupt.", "Runtime Error");

	// Testing stuff
	GetRandomItemModifier(DB_ItemModPoolTypes::BodyArmourSTR, 100);
}
DatabaseManager::~DatabaseManager() { if (db) sqlite3_close(db); }

// Main Functions
void DatabaseManager::PrintTable(const char* tableName) {
	std::string query = std::string("SELECT * FROM ") + tableName + ";";

	printf("Executing Query: '%s'\n", query.c_str());

	sqlite3_exec(db, query.c_str(), [](void* data, int argc, char** argv, char** azColName)
		{
			for (int i = 0; i < argc; i++)
				printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

			return 0;
		}, 0, 0);
}