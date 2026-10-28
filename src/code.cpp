// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Kade Heggem";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
    : prevPtr(nullptr), nextPtr(nullptr), value(newValue)
{
} 

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    return this->value;
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    return this->prevPtr;
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    return this->nextPtr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    this->prevPtr = newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    this->nextPtr = newNextPtr;
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
    : headPtr(nullptr), tailPtr(nullptr), count(0)
{
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    if (headPtr == nullptr)
    {
        return;
    }

    DoubleNode *tempPtr = headPtr;
    while (tempPtr != nullptr)
    {
        DoubleNode* nextPtr = tempPtr->getNext();
        delete tempPtr;
        tempPtr = nextPtr;
        count--;
    }

    headPtr = nullptr;
    tailPtr = nullptr;
    count = 0;
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    if (headPtr == nullptr)
    {
        return nullptr;
    }

    DoubleNode *detachedPtr = headPtr;
    headPtr = headPtr->getNext();

    if (headPtr != nullptr)
        headPtr->setPrev(nullptr);

    else
        tailPtr = nullptr;

    detachedPtr->setNext(nullptr);
    count--;

    return detachedPtr;
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    if (headPtr == nullptr)
    {
        return nullptr;
    }

    DoubleNode *detachedPtr = tailPtr;
    tailPtr = tailPtr->getPrev();

    if (tailPtr != nullptr)
        tailPtr->setNext(nullptr);

    else
        headPtr = nullptr;

    detachedPtr->setPrev(nullptr);
    count--;

    return detachedPtr;
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    DoubleNode *detachedPtr = headPtr;

    while (detachedPtr != nullptr)
    {
        if(detachedPtr->getValue() == value){
            if (detachedPtr == headPtr)
            {
                return detachFirst();
            }
            if (detachedPtr == tailPtr)
            {
                return detachLast();
            }

            detachedPtr->getPrev()->setNext(detachedPtr->getNext());
            detachedPtr->getNext()->setPrev(detachedPtr->getPrev());

            detachedPtr->setNext(nullptr);
            detachedPtr->setPrev(nullptr);

            count--;
            return detachedPtr;
        }

        detachedPtr = detachedPtr->getNext();
    }

    if (detachedPtr == nullptr)
    {
        return nullptr;
    }
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    DoubleNode *newNodePtr = new DoubleNode(value);

    if (headPtr == nullptr)
    {
        newNodePtr->setNext(headPtr);
        newNodePtr->setPrev(nullptr);
        headPtr = newNodePtr;
        tailPtr = newNodePtr;
    }

    else
    {
        newNodePtr->setNext(headPtr);
        newNodePtr->setPrev(nullptr);
        headPtr->setPrev(newNodePtr);
        headPtr = newNodePtr;
    }

    count++;
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    DoubleNode *newNodePtr = new DoubleNode(value);

    if (tailPtr == nullptr)
    {
        newNodePtr->setPrev(tailPtr);
        newNodePtr->setNext(nullptr);
        tailPtr = newNodePtr;
        headPtr = newNodePtr;
    }

    else
    {
        newNodePtr->setPrev(tailPtr);
        newNodePtr->setNext(nullptr);
        tailPtr->setNext(newNodePtr);
        tailPtr = newNodePtr;
    }

    count++;
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{

    if (headPtr == nullptr)
    {
        return std::nullopt;
    }

    DoubleNode *detachedPtr = detachFirst();

    NodeValue value = detachedPtr->getValue();

    delete detachedPtr;

    return value;
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    if (tailPtr == nullptr)
    {
        return std::nullopt;
    }

    DoubleNode *detachedPtr = detachLast();

    NodeValue value = detachedPtr->getValue();

    delete detachedPtr;

    return value;
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    DoubleNode *detachedPtr = detachValue(value);

    if (detachedPtr == nullptr)
    {
        return false;
    }

    delete detachedPtr;

    return true;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    DoubleNode *currentPtr = headPtr;

    while (currentPtr != nullptr)
    {
        if(currentPtr->getValue() == value)
        {
            return true;
        }

        currentPtr = currentPtr->getNext();
    }

    return false;
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    return 0;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    // TODO: implement
    return 0;
}

/// Return count.
int DoublyLinkedList::length() const
{
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    // TODO: implement
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    // TODO: implement
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    // TODO: implement
    return std::nullopt;
}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    // TODO: implement
    return std::nullopt;
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    // TODO: implement
    return false;
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    return false;
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    // TODO: implement
    return 0;
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    // TODO: implement
    return 0;
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    // TODO: implement
    return 0;
}
// ===== END PART 3 (do not remove this marker) =====
