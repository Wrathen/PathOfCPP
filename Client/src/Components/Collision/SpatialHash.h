// Shout-out to https://chat.openai.com
// So the code here is awful. Many hours wasted with the openai, but it was fun.
// After all, I'm doing this for fun&education. Fun makes me keep going.
// Had to fix a lot of stuff that the AI gave me initially, but it was like
// Looking at someone else's code, trying to understand what's going on.
// Then spotting the issue that causing the stuff not doing what you want
// Was a nice experience. I'll never rely on the AI though, it took WAAAAY longer than it should have :D
// Instead, I can use the AI to learn or ask how to approach certain topics.
// Or even, ask whether there's some room for improvement on the code, both in style and optimization stuff.
// The suggestions it provides are INSANE. Loving it!
// #notsponsored

// Will tidy this in the future.
// I don't like the style below nor the code repeats. Looks clean, but overclustered, if that's a word.

#pragma once
#include <vector>
#include "../../Entities/Entity.h"

class SpatialHash {
public:
    // Constructor
    SpatialHash(int width, int height, float cellSize) :
        m_cellSize(cellSize),
        m_width(width),
        m_height(height),
        m_numCellsX(static_cast<int>(width / cellSize)),
        m_numCellsY(static_cast<int>(height / cellSize)),
        m_hash(m_numCellsX* m_numCellsY) {}

    // Insert an entity into the hash
    void Insert(Entity* entity) {
        auto entityPos = entity->transform.GetScreenPosition();

        if (entityPos.x <= -m_width / 2) return;
        else if (entityPos.x >= m_width / 2) return;
        else if (entityPos.y <= -m_height / 2) return;
        else if (entityPos.y >= m_height / 2) return;

        int cellX = static_cast<int>(entityPos.x / m_cellSize);
        int cellY = static_cast<int>(entityPos.y / m_cellSize);

        // Shift the cell indices by the number of cells in the negative direction
        // to ensure that they are always positive
        cellX += m_numCellsX / 2;
        cellY += m_numCellsY / 2;

        int cellIndex = cellY * m_numCellsX + cellX;
        m_hash[cellIndex].push_back(entity);

        //Debug("Pushed " + std::to_string(cellX) + ", " + std::to_string(cellY) + " into the index: " + std::to_string(cellIndex));
    }

    // Remove an entity from the hash
    void Remove(Entity* entity) {
        auto entityPos = entity->transform.GetScreenPosition();
        int cellX = static_cast<int>(entityPos.x / m_cellSize);
        int cellY = static_cast<int>(entityPos.y / m_cellSize);
        int cellIndex = cellY * m_numCellsX + cellX;
        auto& cell = m_hash[cellIndex];
        cell.erase(std::remove(cell.begin(), cell.end(), entity), cell.end());
    }

    // Query the hash for all entities within a certain rectangle
    std::vector<Entity*> Query(int x, int y, int width, int height) {
        std::vector<Entity*> result;

        if (x <= -m_width / 2) return result;
        else if (x >= m_width / 2) return result;
        else if (y <= -m_height / 2) return result;
        else if (y >= m_height / 2) return result;

        // Calculate the indices of the cells in the region
        int minCellX = static_cast<int>(x / m_cellSize);
        int maxCellX = static_cast<int>((x + width - 1) / m_cellSize);
        int minCellY = static_cast<int>(y / m_cellSize);
        int maxCellY = static_cast<int>((y + height - 1) / m_cellSize);

        // Shift the cell indices by the number of cells in the negative direction
        // to ensure that they are always positive
        minCellX += m_numCellsX / 2;
        maxCellX += m_numCellsX / 2;
        minCellY += m_numCellsY / 2;
        maxCellY += m_numCellsY / 2;

        minCellX = std::max(0, minCellX);
        maxCellX = std::min(m_numCellsX - 1, maxCellX);
        minCellY = std::max(0, minCellY);
        maxCellY = std::min(m_numCellsY - 1, maxCellY);

        // Iterate over the cells in the region
        for (int i = minCellX; i <= maxCellX; i++) {
            for (int j = minCellY; j <= maxCellY; j++) {
                 auto& cell = m_hash[i + j * m_numCellsX];
                 result.insert(result.end(), cell.begin(), cell.end());
            }
        }

        return result;
    }

    // Query the hash for all entities within a certain distance of a point
    std::vector<Entity*> QueryRange(int x, int y, float radius) {
        std::vector<Entity*> result;

        if (x <= -m_width / 2) return result;
        else if (x >= m_width / 2) return result;
        else if (y <= -m_height / 2) return result;
        else if (y >= m_height / 2) return result;

        // Determine the min and max cell indices to search
        int minCellX = static_cast<int>((x - radius) / m_cellSize);
        int maxCellX = static_cast<int>((x + radius) / m_cellSize);
        int minCellY = static_cast<int>((y - radius) / m_cellSize);
        int maxCellY = static_cast<int>((y + radius) / m_cellSize);

        // Shift the cell indices by the number of cells in the negative direction
        // to ensure that they are always positive
        minCellX += m_numCellsX / 2;
        maxCellX += m_numCellsX / 2;
        minCellY += m_numCellsY / 2;
        maxCellY += m_numCellsY / 2;

        minCellX = std::max(0, minCellX);
        maxCellX = std::min(m_numCellsX - 1, maxCellX);
        minCellY = std::max(0, minCellY);
        maxCellY = std::min(m_numCellsY - 1, maxCellY);

        // Search the cells for entities within the range
        for (int cellY = minCellY; cellY <= maxCellY; cellY++) {
            for (int cellX = minCellX; cellX <= maxCellX; cellX++) {
                int cellIndex = cellY * m_numCellsX + cellX;
                auto& cell = m_hash[cellIndex];

                for (Entity* entity : cell) {
                    auto entityPos = entity->transform.GetScreenPosition();
                    float dx = std::abs(entityPos.x - x);
                    float dy = std::abs(entityPos.y - y);
                    if (dy - dx <= radius) result.push_back(entity);
                }
            }
        }

        return result;
    }

    // Clear the hash table
    void Clear() { for (auto& cell : m_hash) cell.clear(); }

    // Get all the entities in the hash table
    std::vector<Entity*> GetAll(){
        std::vector<Entity*> result;
        result.reserve(m_cellSize); // Pre-allocate enough space for all the entities
        for (auto& cell : m_hash)
            result.insert(result.end(), cell.begin(), cell.end());
        return result;
    }

private:
    // The size of each cell in the hash
    float m_cellSize;

    // The number of cells in the x and y directions
    int m_width;
    int m_height;
    int m_numCellsX;
    int m_numCellsY;

    // The hash table, mapping cell indices to lists of entity pointers
    std::vector<std::vector<Entity*>> m_hash;
};