/// @file tests.cpp
/// @author 
/// @date October 20, 2023

/// 
/// TODO Update the file header with the appropriate information.
///

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This is a basic test case example with sections.
// Requires: <no oter functions>
TEST_CASE("Test 0: The Null Test") 
{
    // In this section we test Scenario 1.
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    // In this section we test Scenario 2.
    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}


TEST_CASE("Test 1: The Constructor") 
{
    // In this section we test Scenario 1.
    SECTION("Test 1.1:  Default Constuctor should be an empty priority queue")
    {
        prqueue<int> pq; 

        REQUIRE(pq.size() == 0);
    }
}

TEST_CASE("Test 2: The Size and Enqueue") 
{
    // In this section we test Scenario 1.
    SECTION("Test 2.1:  Should return an empty list")
    {
        prqueue<int> pq; 


        REQUIRE(pq.size() == 0);
    }

    SECTION("Test 2.2:  Should return a list of size 3")
    {
        prqueue<int> pq; 
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);


        REQUIRE(pq.size() == 3);
    }

    SECTION("Test 2.3:  Should return a list of size 4")
    {
        prqueue<int> pq; 
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 2);
        pq.enqueue(40, 3);


        REQUIRE(pq.size() == 4);
    }

    SECTION("Test 2.4:  Should return a list of size 6")
    {
        prqueue<int> pq; 
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 2);
        pq.enqueue(40, 3);
        pq.enqueue(50, 3);
        pq.enqueue(60, 3);


        REQUIRE(pq.size() == 6);
    }


    prqueue<int> pq;
    for(int i = 0; i <= 30; i++){
        pq.enqueue(i * 10, i);
    }

    SECTION("Test 2.5: Size should be 30")
    {
        REQUIRE(pq.size() == 31);
    }

    SECTION("Test 2.6: Size should be 30")
    {
        int priority, value; 
        pq.begin();

        for(int i = 0; i < 30; i++){
            REQUIRE(pq.next(value, priority));
            REQUIRE(priority == i);
            REQUIRE(value == i * 10);          
        }

        REQUIRE_FALSE(pq.next(value, priority));
    }

}


TEST_CASE("Test 3: Printing a string of the entire priority queue, in order") 
{
    // In this section we test Scenario 1.
    SECTION("Test 3.1:  Should return nothing")
    {
        prqueue<int> pq; 
        REQUIRE(pq.toString() == "");
    }

    SECTION("Test 3.2:  Should print everything in order")
    {
        prqueue<string> pq; 

        pq.enqueue("Ben", 1);
        pq.enqueue("Jen", 2);
        pq.enqueue("Sven", 2);
        pq.enqueue("Gwen", 3);


        REQUIRE(pq.toString() == "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n");

    }

}

//Test Case provided by Zaheer Safi, netID: zsafi2@uic.edu
TEST_CASE("prqueue toString - Character Values") 
{
    prqueue<char> pq;

    SECTION("Empty queue should produce an empty string") {
        REQUIRE(pq.toString() == "");
    }

    SECTION("Enqueue elements and check the string representation") {
        pq.enqueue('A', 2);
        pq.enqueue('B', 1);
        pq.enqueue('C', 5);
        REQUIRE(pq.toString() == "1 value: B\n2 value: A\n5 value: C\n");
    }

    SECTION("Enqueue elements with duplicate priorities") {
        pq.clear();
        pq.enqueue('A', 2);
        pq.enqueue('B', 2);
        pq.enqueue('C', 2);
        REQUIRE(pq.toString() == "2 value: A\n2 value: B\n2 value: C\n");
    }
}

TEST_CASE("Test 4: Clearing the list") 
{
    // In this section we test Scenario 1.
    SECTION("Test 4.1:  Should return 0")
    {
        prqueue<int> pq; 
        pq.clear();

        REQUIRE(pq.size() == 0);
    }

    SECTION("Test 4.2:  Should clear everything")
    {
        prqueue<string> pq; 

        pq.enqueue("Ben", 1);
        pq.enqueue("Jen", 2);
        pq.enqueue("Swen", 2);
        pq.enqueue("Gwen", 3);

        pq.clear();


        REQUIRE(pq.size() == 0);
    }

    SECTION("Test 4.3:  Should clear everything")
    {
        prqueue<string> pq; 

        pq.enqueue("Ben", 1);
        pq.enqueue("Jen", 2);
        pq.enqueue("Swen", 2);
        pq.enqueue("Gwen", 4);
        pq.enqueue("Peter", 5);
        pq.enqueue("MJ", 6);
        pq.enqueue("Harry", 7);
        pq.enqueue("May", 8);
        pq.enqueue("Norman", 9);

        pq.clear();


        REQUIRE(pq.size() == 0);
    }

}

TEST_CASE("Test 5: The Equality Operator.") 
{
    prqueue<int> pq1; 
    prqueue<int> pq2; 
    SECTION("Test 5.1:  Empty prqueues")
    {

        REQUIRE(pq1 == pq2);
    }

    SECTION("Test 5.2:  Checking two equal queues")
    {

        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);

        pq2.enqueue(10, 1);
        pq2.enqueue(20, 2);
        pq2.enqueue(30, 3);
        pq2.enqueue(40, 4);
        

        REQUIRE(pq1 == pq2);
    }

    SECTION("Test 5.3:  Checking two difference queues")
    {

        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);

        pq2.enqueue(50, 1);
        pq2.enqueue(70, 2);
        pq2.enqueue(80, 3);
        pq2.enqueue(90, 4);

        REQUIRE_FALSE(pq1 == pq2);

    }

    SECTION("Test 5.4:  Different Queues with different sizes")
    {

        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
 
        pq2.enqueue(10, 1);
        pq2.enqueue(20, 2);
        pq2.enqueue(30, 3);

        REQUIRE_FALSE(pq1 == pq2);
    }


}


TEST_CASE("Test 6: Overloading the Equals Operator"){

    SECTION("Test 6.1:  Equals Operator test 1")
    {
        prqueue<int> pq1; 
        prqueue<int> pq2; 

        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);

        pq2.enqueue(40, 4);
        pq2.enqueue(50, 5);
        
        pq1 = pq2;

        REQUIRE(pq1 == pq2);
    }

    SECTION("Test 6.1:  Equals Operator test 2")
    {
        prqueue<int> pq1;
        pq1.enqueue(15, 1);
        pq1.enqueue(16, 2);
        pq1.enqueue(17, 3);
        
        prqueue<int> pq2;
        pq2.enqueue(6, 2);
        pq2.enqueue(7, 2);
        pq2.enqueue(8, 2);
        pq2.enqueue(9, 2);
        pq2.enqueue(17, 3);
        pq2.enqueue(2, 3);
        pq2.enqueue(1, 3);

        pq2 = pq1;    

        REQUIRE(pq2.toString() == pq1.toString());
    }


    prqueue<int> pq1;
    for(int i = 0; i <= 30; i++){
        pq1.enqueue(i * 10, i);
    }

    prqueue<int> pq2;
    for(int i = 0; i <= 30; i++){
        pq2.enqueue(i * 10, i);
    }

    SECTION("Test 6.2: queues should be equal")
    {
        REQUIRE(pq2.toString() == pq1.toString());
    }

    SECTION("Test 6.3: Should not be equal")
    {
        prqueue<int> pq1;
        for(int i = 0; i <= 30; i++){
            pq1.enqueue(i * 10, i);
        }

        prqueue<int> pq2;
        for(int i = 0; i <= 29; i++){
            pq2.enqueue(i * 10, i);
        }

        REQUIRE_FALSE(pq1 == pq2);
    }

}

//Test Case provided by Zaheer Safi, netID: zsafi2@uic.edu
TEST_CASE("prqueue peek and operator==") 
{
    SECTION("Peek at a priority queue with one element") 
    {
        prqueue<int> pq;
        pq.enqueue(42, 2);
        int value = pq.peek();
        REQUIRE(value == 42);
        REQUIRE(pq.size() == 1);
    }

    SECTION("Equality operator between equal priority queues") 
    {
        prqueue<int> pq1;
        pq1.enqueue(42, 2);
        pq1.enqueue(17, 1);
        pq1.enqueue(99, 3);

        prqueue<int> pq2;
        pq2.enqueue(42, 2);
        pq2.enqueue(17, 1);
        pq2.enqueue(99, 3);

        REQUIRE(pq1 == pq2);
    }

    SECTION("Equality operator between unequal priority queues") 
    {
        prqueue<int> pq1;
        pq1.enqueue(42, 2);
        pq1.enqueue(17, 1);

        prqueue<int> pq2;
        pq2.enqueue(42, 2);
        pq2.enqueue(99, 3);

        REQUIRE(!(pq1 == pq2));
    }
}


TEST_CASE("Test 7: The Peek Function") 
{

    SECTION("Test 7.1:  Should return the second element")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);

        REQUIRE(pq1.peek() == 10);
    }

    SECTION("Test 7.2:  Should return the third element")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);

        REQUIRE(pq1.peek() == 10);
    }

    SECTION("Test 7.3:  Should return the sixth element")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);
        pq1.enqueue(50, 5);
        pq1.enqueue(60, 6);

        REQUIRE(pq1.peek() == 10);
    }

    SECTION("Test 7.4:  Should return the fourth element")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);

        REQUIRE(pq1.peek() == 10);
    }
}

TEST_CASE("Test 8: The Dequeue Function") 
{

    SECTION("Test 7.1:  Should return size of 1")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);

        pq1.dequeue();

        REQUIRE(pq1.size() == 1);
    }

    SECTION("Test 7.2: Should return size of 2")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);

        pq1.dequeue();

        REQUIRE(pq1.size() == 2);
    }

    SECTION("Test 7.3:  Should return size of 5")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);
        pq1.enqueue(50, 5);
        pq1.enqueue(60, 5);

        pq1.dequeue();

        REQUIRE(pq1.size() == 5);
    }

    SECTION("Test 7.4:  Should return size of 3")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 4);

        pq1.dequeue();

        REQUIRE(pq1.size() == 3);
    }

    SECTION("Test 7.4:  Should return size of 5")
    {
        prqueue<int> pq1; 
        pq1.enqueue(10, 1);
        pq1.enqueue(20, 2);
        pq1.enqueue(30, 3);
        pq1.enqueue(40, 3);
        pq1.enqueue(40, 4);
        pq1.enqueue(50, 5);

        pq1.dequeue();


        REQUIRE(pq1.size() == 5);
    }

}

//Traveral test cases provided by Zaheer Safi, netID: zsafi2@uic.edu
TEST_CASE("prqueue begin and next") 
{
    prqueue<int> pq;

    SECTION("Inorder traversal of an empty priority queue") 
    {
        int value;
        int priority;

        pq.begin();
        REQUIRE_FALSE(pq.next(value, priority));
    }

    SECTION("Inorder traversal after enqueuing elements") 
    {
        pq.enqueue(42, 2);
        pq.enqueue(17, 1);
        pq.enqueue(20, 5);
        pq.enqueue(100, 3);
        pq.enqueue(1000, 4);

        int value;
        int priority;
        int expectedPriorities[] = {1, 2, 3, 4, 5}; 

        pq.begin();
        for (int i = 0; i < 4; ++i) 
        {
            REQUIRE(pq.next(value, priority));
            REQUIRE(priority == expectedPriorities[i]);
        }
        REQUIRE_FALSE(pq.next(value, priority));
    }

    SECTION("Inorder traversal after enqueuing elements") 
    {
        pq.enqueue(42, 2);
        pq.enqueue(17, 1);
        pq.enqueue(17, 2);
        pq.enqueue(20, 5);
        pq.enqueue(100, 3);
        pq.enqueue(1000, 4);

        int value;
        int priority;
    
        pq.begin();
        pq.next(value, priority);
        
        REQUIRE(value == 17);
        REQUIRE(priority == 1);

        pq.next(value, priority);

        REQUIRE(value == 42);
        REQUIRE(priority == 2);

        pq.next(value, priority);

        REQUIRE(value == 17);
        REQUIRE(priority == 2);
        
        REQUIRE(pq.next(value, priority) == true);
        
        REQUIRE(value == 100);
        REQUIRE(priority == 3);

        pq.next(value, priority);
        REQUIRE(value == 1000);
        REQUIRE(priority == 4);
        
        pq.next(value, priority);
        REQUIRE(value == 20);
        REQUIRE(priority == 5);

        REQUIRE_FALSE(pq.next(value, priority));
    }
    
    SECTION("Inorder traversal after enqueuing elements") 
    {
        pq.enqueue(42, 1);
        pq.enqueue(17, 3);
        pq.enqueue(17, 5);
        pq.enqueue(20, 5);
        pq.enqueue(100, 4);
        pq.enqueue(1000, 7);
        pq.enqueue(199, 7);
        pq.enqueue(220, 3);
        pq.enqueue(120, 5);

        int value;
        int priority;
        int expectedPriorities[] = {1, 3, 3, 4, 5, 5, 5, 7, 7}; // Expected priorities in ascending order.
        int expectedValues[] = {42, 17, 220, 100, 17, 20, 120, 1000, 199};
        pq.begin();
        
        for (int i = 0; i < 8; i++)
        {
            REQUIRE(pq.next(value, priority) == true);
            REQUIRE(value == expectedValues[i]);
            REQUIRE(priority == expectedPriorities[i]);
        }
        REQUIRE(pq.next(value, priority) == false);
    }

    SECTION("Inorder traversal after enqueuing elements") 
    {
        pq.enqueue(42, 2);
        pq.enqueue(17, 3);
        pq.enqueue(17, 2);
        int data = pq.dequeue();
        REQUIRE(data == 42);
        int value;
        int priority;
    
        pq.begin();
        pq.next(value, priority);
        
        REQUIRE(value == 17);
        REQUIRE(priority == 2);

        pq.next(value, priority);
        REQUIRE(value == 17);
        REQUIRE(priority == 3);

        REQUIRE_FALSE(pq.next(value, priority));       
    }

    SECTION("Inorder traversal after enqueuing elements") 
    {
        pq.enqueue(1, 5);
        pq.enqueue(2, 5);
        pq.enqueue(3, 5);
        pq.enqueue(4, 2);
        pq.enqueue(5, 4);
        pq.enqueue(6, 10);
        pq.enqueue(7, 20);
        pq.enqueue(8, 2);
        pq.enqueue(9, 2);

        
        int value;
        int priority;
        int expectedPriorities[] = {2, 2, 2, 4, 5, 5, 5, 10, 20}; // Expected priorities in ascending order.
        int expectedValues[] = {4,8,9,5,1,2,3,6,7};
        pq.begin();
        for (int i = 0; i < 8; i++)
        {
            REQUIRE(pq.next(value, priority) == true);
            REQUIRE(value == expectedValues[i]);
            REQUIRE(priority == expectedPriorities[i]);
        }
        REQUIRE(pq.next(value, priority) == false);   
    }
}

TEST_CASE("more test preque begin nand next") 
{
    SECTION("Inorder traversal of an empty priority queue") 
    {
        prqueue<int> pq;
        pq.begin();
        int value, priority;
        REQUIRE(pq.next(value, priority) == false);
    }

    SECTION("Inorder traversal of a priority queue with one element") 
    {
        prqueue<int> pq;
        pq.enqueue(42, 2);
        pq.begin();
        int value, priority;
        REQUIRE(pq.next(value, priority) == false);
        REQUIRE(value == 42);
        REQUIRE(priority == 2);
        REQUIRE(pq.next(value, priority) == false);
    }

    SECTION("Inorder traversal of a priority queue with unique priorities") 
    {
        prqueue<int> pq;
        pq.enqueue(42, 2);
        pq.enqueue(17, 1);
        pq.enqueue(99, 3);
        pq.begin();
        int value, priority;
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(value == 17);
        REQUIRE(priority == 1);
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(value == 42);
        REQUIRE(priority == 2);
        REQUIRE(pq.next(value, priority) == false);
        REQUIRE(value == 99);
        REQUIRE(priority == 3);
    }

    SECTION("Inorder traversal of a priority queue with duplicate priorities") 
    {
        prqueue<int> pq;
        pq.enqueue(42, 1);
        pq.enqueue(17, 2);
        pq.enqueue(99, 3);
        pq.begin();
        int value, priority;
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(value == 42);
        REQUIRE(priority == 1);
        REQUIRE(pq.next(value, priority) == true);
        REQUIRE(value == 17);
        REQUIRE(priority == 2);
        REQUIRE(pq.next(value, priority) == false);
        REQUIRE(value == 99);
        REQUIRE(priority == 3);
    }

}
