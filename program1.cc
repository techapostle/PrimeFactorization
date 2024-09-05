#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// Helper function to check if a number is prime
bool isPrime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

// Function to parse an integer from the input and return it
int parseInteger() {
  int num;
  cin >> num;
  return num;
}

// Function to parse a prime-exponent pair and return the prime and exponent
bool parsePrimeExponent(int& prime, int& exponent) {
  char mult, caret;

  cin >> mult;  // Read the multiplication symbol '*'
  if (mult != '*') return false;  // Check for '*'

  cin >> prime;  // Read the prime number
  if (!isPrime(prime)) return false;  // Check if it's a prime number

  cin >> caret;  // Read the caret '^'
  if (caret != '^') return false;  // Check for '^'

  cin >> exponent;  // Read the exponent

  return true;
}

// Function to factorize a number one prime at a time and compare it against the input
bool factorizeAndCompare(int number, int sign) {
  int calculatedProduct = sign;
  int prime, exponent;

  while (cin.peek() != '?') {  // Continue until we encounter the '?' character
    if (!parsePrimeExponent(prime, exponent)) {
      return false;  // Invalid prime-exponent pair
    }

    // Multiply the calculated product by prime^exponent
    int primePower = 1;
    for (int i = 0; i < exponent; i++) {
      primePower *= prime;
    }
    calculatedProduct *= primePower;
  }

  return calculatedProduct == number;  // Return true if the factorized product matches the original number
}

// Main function
int main() {
  int number = parseInteger();  // Read the integer on the left side of the equation
  char equalSign;
  cin >> equalSign;  // Read the '=' sign

  if (equalSign != '=') {
    cout << "Invalid input format." << endl;
    return 0;
  }

  int sign = parseInteger();  // Read the sign (1 or -1)
  if (sign != 1 && sign != -1) {
    cout << "Invalid input format." << endl;
    return 0;
  }

  // No need for an early check of '*' or '?', as the prime-exponent pairs will be validated while parsing.

  // Factorize and compare with the given number
  bool correct = factorizeAndCompare(number, sign);
  char questionMark;
  cin >> questionMark;  // Read the '?' character

  // Output the result with appropriate formatting
  if (correct && questionMark == '?') {
    cout << "Correct!" << endl;  // Print "Correct!" if the factorization matches
  } else if (questionMark == '?') {
    cout << "Incorrect. " << number << " = " << (sign < 0 ? "-1" : "1");

    // Re-read and output the prime factorization
    int prime, exponent;
    bool firstFactor = true;

    while (cin.peek() != '?') {  // Continue until we encounter the '?' character again
      if (!parsePrimeExponent(prime, exponent)) {
        break;
      }

      if (!firstFactor) {
        cout << " * ";  // Print " * " between factors
      } else {
        cout << " * ";  // Print the first " * " after the sign
        firstFactor = false;
      }

      cout << prime << "^" << exponent;  // Print the prime-exponent pair
    }

    cout << endl;
  } else {
    cout << "Invalid input format." << endl;
  }

  return 0;
}
