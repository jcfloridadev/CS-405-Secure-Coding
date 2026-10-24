/*
 * File: BufferOverflow.cpp
 * Developer: Justin Carlo Florida
 * Course: CS-405 Secure Coding
 * Purpose: Demonstrates how a buffer overflow vulnerability can occur
 * when user input exceeds the size of a fixed-length character array.
 * This program implements defensive coding techniques by validating
 * input length, preventing buffer overflow, and notifying the user
 * when the maximum allowed input length is exceeded.
 */

// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <string>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  variable, and its position in the declaration. It must always be directly before the variable used for input.
  //  You must notify the user if they entered too much data.

  const std::string account_number = "CharlieBrown42";
  char user_input[20];

  std::cout << "Enter a value: ";

  // Read at most 19 characters plus the null terminator into the fixed-size buffer.
  // This prevents writing past the end of the array.
  std::cin.getline(user_input, sizeof(user_input));

  // If the input exceeds the buffer size, getline() sets the fail state.
  if (std::cin.fail())
  {
      // Inform the user that the supplied input exceeded the buffer size
      // and was rejected before it could be processed.
      std::cout << "You entered: " << user_input << "... " << "[Input exceeded maximum length]" << std::endl;
      std::cout << "Error: Input exceeds the maximum allowed length (19 characters)." << std::endl;

      // Clear the fail state so the input stream can continue to be used.
      std::cin.clear();

      // Remove any remaining characters from the input buffer so they
      // do not affect future input operations.
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Exit the program because the oversized input was rejected.
      return 1;
  }

  // Display the validated user input.
  std::cout << "You entered: " << user_input << std::endl;

  // Display the account number to verify it was not modified by oversized input.
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
