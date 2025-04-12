#include "Inventory.h"

Inventory::Inventory()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_current = nullptr;
	std::cout << "Inventory created." << std::endl;
}

Inventory::~Inventory()
{
    InventoryItem* current = m_head;

    while (current)
    {
        InventoryItem* next = current->GetNextItem();
        delete current;
        current = next;
    }
	std::cout << "Inventory destroyed." << std::endl;
}

void Inventory::AddItem(InventoryItem* item)
{
    if (!item)
    {
        return;
    }

    item->SetNextItem(nullptr);
    item->SetPrevItem(nullptr);

    if (!m_head)
    {
        m_head = item;
        m_tail = item;
        m_current = item;
    }
    else
    {
        item->SetPrevItem(m_tail);
        m_tail->SetNextItem(item);
        m_tail = item;
    }
}

void Inventory::RemoveCurrentItem()
{
    if (!m_current)
    {
        return;
    }

    InventoryItem* prev = m_current->GetPrevItem();
    InventoryItem* next = m_current->GetNextItem();

    if (prev)
    {
        prev->SetNextItem(next);
    }
    if (next)
    {
        next->SetPrevItem(prev);
    }

    if (m_current == m_head)
    {
        m_head = next;
    }
    if (m_current == m_tail)
    {
        m_tail = prev;
    }

    delete m_current;

    if (next)
    {
        m_current = next;
    }
    else
    {
        m_current = prev;
    }

}

void Inventory::SelectNextItem()
{
    if (m_current && m_current->GetNextItem())
    {
        m_current = m_current->GetNextItem();
    }
    else
    {
        m_current = m_head;
    }
}

void Inventory::SelectPreviousItem()
{
    if (m_current && m_current->GetPrevItem())
    {
        m_current = m_current->GetPrevItem();
    }
    else
    {
        m_current = m_tail;
    }
}

void Inventory::DisplayCurrentItem()
{
    if (m_current)
    {
        std::cout << m_current->ToString() << std::endl;
    }
    else
    {
        std::cout << "No items in inventory." << std::endl;
    }
}

void Inventory::DisplayAll()
{
    std::cout << "\n--- INVENTORY CONTENTS ---\n";

    if (!m_head)
    {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }

    InventoryItem* current = m_head;
    while (current)
    {
        if (current == m_current)
        {
            std::cout << ">> " << current->ToString() << " <<" << std::endl;
        }
        else
        {
            std::cout << current->ToString() << std::endl;
        }

        current = current->GetNextItem();
    }
}

void Inventory::EquipCurrentItem(Character& player)
{
    if (!m_current)
    {
        std::cout << "You need to select an item." << std::endl;
        return;
    }

    EquipmentItem* equipment = dynamic_cast<EquipmentItem*>(m_current);
    if (!equipment)
    {
        std::cout << "You can't equip this item" << std::endl;
        return;
    }

    InventoryItem* prevItem = m_current->GetPrevItem();
    InventoryItem* nextItem = m_current->GetNextItem();

    if (prevItem)
    {
        prevItem->SetNextItem(nextItem);
    }
    else
    {
        m_head = nextItem;
    }

    if (nextItem)
    {
        nextItem->SetPrevItem(prevItem);
    }
    else
    {
        m_tail = prevItem;
    }

    equipment->SetPrevItem(nullptr);
    equipment->SetNextItem(nullptr);

    if (nextItem)
    {
        m_current = nextItem;
    }
    else if (prevItem)
    {
        m_current = prevItem;
    }
    else
    {
        m_current = nullptr;
    }

    EquipmentItem* unequipped = player.EquipItem(equipment);

    if (unequipped)
    {
        unequipped->SetNextItem(nullptr);
        unequipped->SetPrevItem(nullptr);

        if (!m_head)
        {
            m_head = unequipped;
            m_tail = unequipped;
            m_current = unequipped;
        }
        else
        {
            m_tail->SetNextItem(unequipped);
            unequipped->SetPrevItem(m_tail);
            m_tail = unequipped;
        }
    }
}

void Inventory::InsertItemAfterCurrent(InventoryItem* item)
{
    if (!m_current)
    {
        m_head = m_tail = m_current = item;
    }
    else
    {
        InventoryItem* next = m_current->GetNextItem();
        item->SetPrevItem(m_current);
        item->SetNextItem(next);
        m_current->SetNextItem(item);
        if (next)
        {
            next->SetPrevItem(item);
        }
        else
        {
            m_tail = item;
        }
    }
}

InventoryItem* Inventory::GetCurrentItem()
{
    return m_current;
}
