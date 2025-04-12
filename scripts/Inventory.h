#pragma once
#include "InventoryItem.h"
#include "Character.h"
#include <iostream>

class Inventory
{
private:
    InventoryItem* m_head;
    InventoryItem* m_tail;
    InventoryItem* m_current;

public:
    Inventory();
    ~Inventory();
    void AddItem(InventoryItem* item);
    void RemoveCurrentItem();
    void SelectNextItem();
    void SelectPreviousItem();
    void DisplayCurrentItem();
    void DisplayAll();
    void EquipCurrentItem(Character& player);
    void InsertItemAfterCurrent(InventoryItem* item);
    InventoryItem* GetCurrentItem();
};
