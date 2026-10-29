#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList list;

    int listLength = list.length();

    TEST_ASSERT_EQUAL(0, listLength);
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList list;

    list.pushFrontValue(10);
    list.pushBackValue(20);

    int listLength = list.length();
    TEST_ASSERT_EQUAL(2, listLength);

}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList list;

    list.popFrontValue();
    list.popBackValue();

    TEST_ASSERT_FALSE(list.containsValue(10));
}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList list;

    list.pushBackValue(1);
    list.pushBackValue(3);
    list.pushBackValue(3);

    std::optional<NodeValue> backValue = list.popBackValue();
    std::optional<NodeValue> frontValue = list.popFrontValue();

    TEST_ASSERT_TRUE(backValue.has_value() && std::holds_alternative<int>(backValue.value()));
    TEST_ASSERT_TRUE(frontValue.has_value() && std::holds_alternative<int>(frontValue.value()));

    TEST_ASSERT_EQUAL(3, std::get<int>(backValue.value()));
    TEST_ASSERT_EQUAL(1, std::get<int>(frontValue.value()));


    int listLength = list.length();
    TEST_ASSERT_EQUAL(1, listLength);
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList list;

    list.pushFrontValue(1);
    bool a = list.deleteValue(2);

    TEST_ASSERT_FALSE(a);

    int listLength = list.length();
    TEST_ASSERT_EQUAL(1, listLength);
}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList list;

    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);

    list.deleteValue(2);
    
    std::optional<NodeValue> backValue1 = list.popBackValue();
    std::optional<NodeValue> backValue2 = list.popBackValue();

    TEST_ASSERT_TRUE(backValue1.has_value() && std::holds_alternative<int>(backValue1.value()));
    TEST_ASSERT_TRUE(backValue2.has_value() && std::holds_alternative<int>(backValue2.value()));

    TEST_ASSERT_EQUAL(3, std::get<int>(backValue1.value()));
    TEST_ASSERT_EQUAL(1, std::get<int>(backValue2.value()));
}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    StdDoublyLinkedList newList;
    newList.pushBackValue(1);
    newList.pushBackValue(2);
    newList.pushBackValue(1);

    newList.deleteValue(NodeValue{1});

    int listLength = newList.length();
    TEST_ASSERT_EQUAL(2, listLength);

    std::optional<NodeValue> frontValue = newList.popFrontValue();

    TEST_ASSERT_TRUE(frontValue.has_value() && std::holds_alternative<int>(frontValue.value()));
    TEST_ASSERT_EQUAL(2, std::get<int>(frontValue.value()));
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    StdDoublyLinkedList newList;

    std::optional<NodeValue> frontValue = newList.popFrontValue();
    std::optional<NodeValue> backValue = newList.popBackValue();

    TEST_ASSERT_FALSE(frontValue.has_value() && std::holds_alternative<int>(frontValue.value()));
    TEST_ASSERT_FALSE(backValue.has_value() && std::holds_alternative<int>(backValue.value()));
}

