/*
 * CS-405 Secure Coding
 * Module Four Milestone - Unit Testing
 * Developer: Justin Carlo Florida
 *
 * This program uses the Google Test framework to test the functionality
 * and behavior of a C++ std::vector collection. The unit tests verify
 * operations including adding elements, resizing, capacity, clearing,
 * erasing, reserving memory, and exception handling. Both positive and
 * negative test cases are included to verify expected behavior and
 * proper handling of invalid operations.
 */

// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Verify the collection starts empty.
    ASSERT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);

    // Add one value to the collection.
    add_entries(1);

    // Verify the collection now contains one value.
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Verify the collection starts empty.
    ASSERT_TRUE(collection->empty());

    // Add five values to the collection.
    add_entries(5);

    // Verify five values were successfully added.
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize)
{
    // Verify max_size is valid for an empty collection.
    ASSERT_TRUE(collection->empty());
    EXPECT_GE(collection->max_size(), collection->size());

    // Verify max_size remains greater than or equal to size
    // as entries are added.
    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    // Verify capacity is valid for an empty collection.
    ASSERT_TRUE(collection->empty());
    EXPECT_GE(collection->capacity(), collection->size());

    // Verify capacity remains greater than or equal to size
    // as entries are added.
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // Add five values to establish the initial collection size.
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Increase the collection size to ten.
    collection->resize(10);

    // Verify resizing increased the collection size.
    EXPECT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // Add ten values to establish the initial collection size.
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // Decrease the collection size to five.
    collection->resize(5);

    // Verify resizing decreased the collection size.
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesCollectionToZero)
{
    // Add five values to establish the initial collection size.
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Resize the collection to zero.
    collection->resize(0);

    // Verify the collection is now empty.
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // Add five values to establish a non-empty collection.
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Clear all values from the collection.
    collection->clear();

    // Verify the collection is empty after clear().
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseRangeErasesCollection)
{
    // Add five values to establish a non-empty collection.
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Erase all elements using the begin and end iterators.
    collection->erase(collection->begin(), collection->end());

    // Verify the collection is empty after erasing the full range.
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
    // Add five values to establish the initial collection.
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    // Store the original size and capacity.
    size_t originalSize = collection->size();
    size_t originalCapacity = collection->capacity();

    // Reserve additional capacity.
    collection->reserve(originalCapacity + 10);

    // Verify capacity increased while size remained unchanged.
    EXPECT_GT(collection->capacity(), originalCapacity);
    EXPECT_EQ(collection->size(), originalSize);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRangeForInvalidIndex)
{
    // Verify the collection starts empty.
    ASSERT_TRUE(collection->empty());

    // Verify that accessing an invalid index throws std::out_of_range.
    EXPECT_THROW(collection->at(0), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// Positive custom test: verify push_back stores the expected value.
TEST_F(CollectionTest, PushBackStoresExpectedValue)
{
    // Add a known value to the collection.
    collection->push_back(42);

    // Verify one value was added.
    ASSERT_EQ(collection->size(), 1);

    // Verify the stored value is correct.
    EXPECT_EQ(collection->front(), 42);
    EXPECT_EQ(collection->back(), 42);
}
// Negative custom test: verify at() rejects an index past the last element.
TEST_F(CollectionTest, AtThrowsOutOfRangePastLastElement)
{
    // Add one known value to the collection.
    collection->push_back(42);
    ASSERT_EQ(collection->size(), 1);

    // Index 1 is out of bounds because the only valid index is 0.
    EXPECT_THROW(collection->at(1), std::out_of_range);
}