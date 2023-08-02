#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "GUID.h"
#include "Log.h"

template <typename T>
class Collection {
private:
	std::vector<T*> itemList;
	std::vector<T*> toBeDeletedList;

public:
	// Dirty means that the collection needs to be updated in such unique way.
	// For example, UIManager uses this in order to sort the collection list
	// to react to Z-Index.
	bool isDirty = false;



	// Main Functions
	void Add(T* item) {
		if (!item) return;

		static GUID guid;
		item->AssignGUID(++guid);
		itemList.insert(itemList.end(), item);

		// Set the isDirty Flag to true so if the collection holder want to react, they can.
		isDirty = true;
	}

	void Remove(T* item) {
		if (!item || item->isToBeDeleted) return;
		item->isToBeDeleted = true;
		toBeDeletedList.push_back(item);
	}
	T* Get(GUID guid) {
		auto item = itemList.find(guid);
		return item != itemList.end() ? item->second : nullptr;
	}

	// Utility
	void PrintAll() {
		for (auto& item : itemList)
			Debug(item.second->ToString());
	}
	auto GetAll() { return &itemList; }

	Collection<T>(int reserveSize) {
		Debug("Hey, a new collection have arrived! " + std::string(typeid(T).name()));

		itemList = std::vector<T*>();
		itemList.reserve(reserveSize);
	}
	Collection<T>(Collection<T> const&) = delete;
	void operator=(Collection<T> const&) = delete;
	~Collection<T>() {
		//Debug(typeid(T).name());
		// I don't know how to enforce this Delete function on each item type, YET.
		// But, so far, I've used this only in Entity, UIElement and Collider's respective managers.
		for (auto& item : itemList) item->Delete();
		itemList.clear();
	}

	void Update() { if (!toBeDeletedList.empty()) DeleteAllQueued(); }
	void Delete(T* item) {
		if (!item) return;

		auto position = std::find(itemList.begin(), itemList.end(), item);
		if (position == itemList.end()) {
			Warn("Somehow, the item was not found in Collection::Delete");
			Warn(typeid(T).name());
			return;
		}

		//Debug("Deleting " + item->ToString());
		itemList.erase(position);
		delete item;
	}
	void DeleteAllQueued() {
		for (auto it = toBeDeletedList.rbegin(); it != toBeDeletedList.rend(); ++it) Delete(*it);
		toBeDeletedList.clear();

		// Set the isDirty Flag to true so if the collection holder want to react, they can.
		isDirty = true;
	}
};