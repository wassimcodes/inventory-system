#include "InventoryItem.h"
#include <iostream>

InventoryItem::InventoryItem(std::string name, int cost, int initialStack)
{
	m_name = name;
	m_cost = cost;
	m_prevItem = nullptr;
	m_nextItem = nullptr;
    std::cout << "InventoryItem created: " << ToString() << std::endl;

}

InventoryItem::~InventoryItem()
{
    std::cout << "InventoryItem destroyed: " << ToString() << std::endl;
}

std::string InventoryItem::GetName()
{
    return m_name;
}

int InventoryItem::GetCost()
{
    return m_cost;
}

InventoryItem* InventoryItem::GetPrevItem()
{
    return m_prevItem;
}

InventoryItem* InventoryItem::GetNextItem()
{
    return m_nextItem;
}

void InventoryItem::SetPrevItem(InventoryItem* prevItem)
{
    m_prevItem = prevItem;
}

void InventoryItem::SetNextItem(InventoryItem* nextItem)
{
    m_nextItem = nextItem;
}

std::string InventoryItem::ToString()
{
    return "Name: " + m_name + ", Cost: " + std::to_string(m_cost);
}



ConsumableItem::ConsumableItem(std::string name, int cost, int initialStack)
    : InventoryItem(name, cost, initialStack), m_stackCount(initialStack)
{
    if (m_stackCount < 1)
    {
        m_stackCount = 1;
    }
    if (m_stackCount > m_maxStackCount)
    {
        m_stackCount = m_maxStackCount;
    }
    std::cout << "ConsumableItem created: " << ToString() << std::endl;
}

ConsumableItem::~ConsumableItem()
{
    std::cout << "ConsumableItem destroyed: " << ToString() << std::endl;
}

int ConsumableItem::GetStackCount()
{
    return m_stackCount;
}

int ConsumableItem::AddStack(int count)
{
    m_stackCount += count;
    if (m_stackCount > m_maxStackCount)
    {
        int excess = m_stackCount - m_maxStackCount;
        m_stackCount = m_maxStackCount;
        return excess;
    }
    return 0;
}

bool ConsumableItem::RemoveStack(int count)
{
    m_stackCount -= count;
    if (m_stackCount < 0)
    {
        m_stackCount = 0;
    }
    return m_stackCount == 0;
}

std::string ConsumableItem::ToString()
{
    return InventoryItem::ToString() + ", Stack: " + std::to_string(m_stackCount) + "/" + std::to_string(m_maxStackCount);

}

EquipmentItem::EquipmentItem(std::string name, int cost, EquipmentSlot slot)
    : InventoryItem(name, cost, 0), m_slot(slot)
{
	std::cout << "EquipmentItem created: " << ToString() << std::endl;
}

EquipmentItem::~EquipmentItem()
{
	std::cout << "EquipmentItem destroyed: " << ToString() << std::endl;
}

EquipmentSlot EquipmentItem::GetSlot()
{
    return m_slot;
}

std::string EquipmentItem::GetSlotName()
{
    switch (m_slot)
    {
    case EquipmentSlot::Torso: return "Torso";
    case EquipmentSlot::Head: return "Head";
    case EquipmentSlot::Legs: return "Legs";
    case EquipmentSlot::Weapon1: return "Weapon1";
    case EquipmentSlot::Weapon2: return "Weapon2";
    default: return "Unknown";
    }
}

std::string EquipmentItem::ToString()
{
    return InventoryItem::ToString() + ", Slot: " + GetSlotName();
}


