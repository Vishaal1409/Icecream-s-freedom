#include "Systems/Inventory.h"

Inventory::Inventory() {
    items.reserve(10);  // Reserve space for typical inventory size
}

void Inventory::AddItem(const std::string& itemID) {
    // Validation - don't add empty IDs or duplicates
    if (itemID.empty()) {
        return;  // Silently ignore empty item IDs
    }

    if (!HasItem(itemID)) {
        items.push_back(itemID);
    }
}

bool Inventory::RemoveItem(const std::string& itemID) {
    auto it = std::find(items.begin(), items.end(), itemID);
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

bool Inventory::HasItem(const std::string& itemID) const {
    return std::find(items.begin(), items.end(), itemID) != items.end();
}

int Inventory::GetItemCount() const {
    return static_cast<int>(items.size());
}

const std::vector<std::string>& Inventory::GetAllItems() const {
    return items;
}

void Inventory::Clear() {
    items.clear();
}

bool Inventory::IsEmpty() const {
    return items.empty();
}
