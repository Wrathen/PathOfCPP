#include "DatabaseManager.h"
#include "../Miscellaneous/ErrorHandler.h"
#include <string>

// Ctor & Dtor ~~ Handle opening&closing of the Database Connection.
void DatabaseManager::Init() { 
	if (sqlite3_open("Assets/Databases/PoC.db", &db) != SQLITE_OK)
		Abort("Couldn't connect to the Database.\n\nDatabase file might be corrupt.", "Runtime Error");
}
DatabaseManager::~DatabaseManager() { if (db) sqlite3_close(db); }

// Main Functions
void DatabaseManager::PrintTable(const char* tableName) {
	printf("Printing %s Table:\n", tableName);

	std::string query = std::string("SELECT * FROM ") + tableName + ";";

	printf("Executing Query: '%s'\n", query.c_str());

	sqlite3_exec(db, query.c_str(), [](void* data, int argc, char** argv, char** azColName)
		{
			for (int i = 0; i < argc; i++)
				printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

			return 0;
		}, 0, 0);
}