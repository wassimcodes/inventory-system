#pragma once
#include <string>

class InventoryItem
{
protected:
    std::string m_name;
    int m_cost;
    InventoryItem* m_prevItem;
    InventoryItem* m_nextItem;

public:
    InventoryItem(std::string name, int cost, int initialStack);
    virtual ~InventoryItem();

    std::string GetName();
    int GetCost();
    InventoryItem* GetPrevItem();
    InventoryItem* GetNextItem();
    void SetPrevItem(InventoryItem* PrevItem);
    void SetNextItem(InventoryItem* NextItem);
    virtual std::string ToString();
};

//------------------------------------------------------------
class ConsumableItem : public InventoryItem
{
private:
    int m_stackCount;
    int const m_maxStackCount = 20;

public:
    ConsumableItem(std::string name, int cost, int initialStack);
    ~ConsumableItem();
    int GetStackCount();
    int AddStack(int count = 1);
    bool RemoveStack(int count = 1);
    std::string ToString();
};
//------------------------------------------------------------

enum class EquipmentSlot
{
    Torso,
    Head,
    Legs,
    Weapon1,
    Weapon2
};

//------------------------------------------------------------

class EquipmentItem : public InventoryItem
{
private:
    EquipmentSlot m_slot;

public:
    EquipmentItem(std::string name, int cost, EquipmentSlot slot);
    ~EquipmentItem();
    EquipmentSlot GetSlot();
    std::string GetSlotName();
    std::string ToString();
};
