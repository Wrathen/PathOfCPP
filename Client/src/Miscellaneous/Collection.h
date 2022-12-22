#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "GUID.h"
#include "Log.h"

template <typename T>
class Collection
{
private:
    std::unordered_map<GUID, T*> itemList;
    std::vector<T*> toBeDeletedList;

public:
    // Main Functions
    void Add(T* item) {
        if (!item) return;

        static GUID guid;
        item->AssignGUID(guid);
        itemList[guid++] = item;
    }

    void Remove(T* item) {
        if (!item) return;
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

protected:
    Collection<T>() {}
    Collection<T>(Collection<T> const&) = delete;
    void operator=(Collection<T> const&) = delete;
    ~Collection<T>() {
        //Debug(typeid(T).name());
        // I don't know how to enforce this Delete function on each item type, YET.
        // But, so far, I've used this only in Entity, UIElement and Collider's respective managers.
        for (auto& item : itemList) item.second->Delete();
        itemList.clear();
    }

    void Update() { DeleteAllQueued(); }
    void Delete(T* item) {
        if (!item) return;

        //Debug("Deleted " + item->ToString());
        itemList.erase(item->guid);

        delete item;
    }
    void DeleteAllQueued() {
        for (auto it = toBeDeletedList.rbegin(); it != toBeDeletedList.rend(); ++it) Delete(*it);
        toBeDeletedList.clear();
    }
};