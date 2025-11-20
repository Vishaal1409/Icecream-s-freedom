#pragma once

#include <string>
#include <vector>
#include <algorithm>

/**
 * Inventory Class - Demonstrates ENCAPSULATION and DATA MANAGEMENT
 *
 * Manages player's collected items using private data structures
 * with controlled public access methods.
 */
class Inventory {
private:
    // ENCAPSULATION - Private data storage
    std::vector<std::string> items;

public:
    Inventory();
    ~Inventory() = default;

    // ENCAPSULATION - Public interface for inventory management
    void AddItem(const std::string& itemID);
    bool RemoveItem(const std::string& itemID);
    bool HasItem(const std::string& itemID) const;
    int GetItemCount() const;
    const std::vector<std::string>& GetAllItems() const;
    void Clear();

    // Utility methods
    bool IsEmpty() const;
};
