#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "GUID.h"
#include "Log.h"

template <typename T>
class Collection {
private:
	std::vector<std::shared_ptr<T>> itemList;
	std::vector<T*> toBeDeletedList;
	GUID GUIDCounter;

public:
	// Dirty means that the collection needs to be updated in such unique way.
	// For example, UIManager uses this in order to sort the collection list
	// to react to Z-Index.
	bool isDirty = false;

	// Main Functions
	
	void Add(T* item) {
		if (!item || item->isToBeDeleted) return;

		// Assign GUID.
		item->AssignGUID(++GUIDCounter);

		// Place this pepega into our main highway.
		itemList.emplace_back(item);

		// Set the isDirty Flag to true so if the collection holder want to react, they can.
		isDirty = true;
	}

	// Creates a new item, puts it in the collection and returns it.
	std::shared_ptr<T> Create() {
		// Create one item.
		auto& item = itemList.emplace_back();

		// Assign GUID.
		item->AssignGUID(++GUIDCounter);

		// Set the isDirty Flag to true so if the collection holder want to react, they can.
		isDirty = true;

		// Return the newly created item. This returns a copy, not the reference.
		return item;
	}

	// Removes a given item from the collection.
	void Remove(T* item) {
		if (!item || item->isToBeDeleted) return;
		item->isToBeDeleted = true;
		toBeDeletedList.push_back(item);
	}

	// Gets an item from the collection based on GUID.
	std::shared_ptr<T> Get(GUID guid) {
		auto it = std::find_if(itemList.begin(), itemList.end(), [&](std::shared_ptr<T> const& object) { return object->guid == guid; });
		return it != itemList.end() ? *it : nullptr;
	}

	// This is mainly used by league encounters that create their own monsters.
	// When you create a new monster, you emplace the monster into the latest index of the storage vector.
	// So what we could do is, just check the latest monster and if that is what we seek, we can just O(1) return.
	// Otherwise, we search throughout the array.
	std::shared_ptr<T> GetFast(GUID guid) {
		if (itemList[itemList.size() - 1]->guid == guid)
			return itemList[itemList.size() - 1];

		return Get(guid);
	}

	// Utility
	void PrintAll() {
		for (auto& item : itemList)
			Debug(item->ToString());
	}
	auto& GetAll() { return itemList; }

	// CTOR && DTORs
	Collection<T>(int reserveSize) {
		itemList = std::vector<std::shared_ptr<T>>();
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

private:
	void Delete(T* item) {
		if (!item) return;

		auto it = std::find_if(itemList.begin(), itemList.end(), [&](std::shared_ptr<T> const& object) { return object.get() == item; });
		if (it == itemList.end()) {
			Warn("Somehow, the item was not found in Collection::Delete");
			Warn(typeid(T).name());
			return;
		}
		 
		itemList.erase(it);

		//Debug("Deleting " + item->ToString());
		//delete item; // We no longer need this since we switched to smart pointers.
	}

public:
	// Update the collection.
	void Update() { if (!toBeDeletedList.empty()) DeleteAllQueued(); }

	// Deletes the items from the main collection based on the ToBeDeleted List.
	void DeleteAllQueued() {
		// Delete each queued item.
		for (auto it = toBeDeletedList.rbegin(); it != toBeDeletedList.rend(); ++it)
			Delete(*it);

		// Clear the List.
		toBeDeletedList.clear();

		// Set the isDirty Flag to true so if the collection holder want to react, they can.
		isDirty = true;
	}
};