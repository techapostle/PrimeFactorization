#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Protype for helper functions
bool isPrime(int n);
void skipSpaces(const char input[], int &pos);
bool parseInput(const char input[], int &integer, int &sign, int primes[], int exponents[], int &count);
void factorize(int number, int primes[], int exponents[], int &count);
void sortPrimesAndExponents(int primes[], int exponents[], int count);

// Main function
int main() {
  char input[256];
  cin.getline(input, 256); // Read the entire input as a C-style string

  int number, sign, userPrimes[10], userExponents[10], count = 0;

  if (!parseInput(input, number, sign, userPrimes, userExponents, count)) {
    cout << "Invalid input format." << endl;
    return 0;
  }

  // Sort the user primes and exponents for correct comparison
  sortPrimesAndExponents(userPrimes, userExponents, count);

  // Calculate the correct prime factorization of the number
  int correctPrimes[10], correctExponents[10], correctCount = 0;
  factorize(number, correctPrimes, correctExponents, correctCount);

  // Sort the correct primes and exponents for correct comparison
  sortPrimesAndExponents(correctPrimes, correctExponents, correctCount);

  // Compare the input prime factorization with the correct one
  bool correct = true;
  if (count != correctCount) {
    correct = false;
  } else {
    for (int i = 0; i < count; i++) {
      if (userPrimes[i] != correctPrimes[i] || userExponents[i] != correctExponents[i]) {
        correct = false;
        break;
      }
    }
  }

  // Output the result
  if (correct) {
    cout << "Correct!" << endl;
  } else {
    cout << "Incorrect. " << number << " = ";

    // Adjust the output to correctly show -1 or 1 depending on the sign
    cout << (number < 0 ? "-1" : "1");

    // Output the prime factorization
    for (int i = 0; i < correctCount; i++) {
      cout << " * " << correctPrimes[i] << "^" << correctExponents[i];
    }
    cout << endl;
  }

  return 0;
}

// Helper function to check if a number is prime
bool isPrime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

// Function to skip spaces
void skipSpaces(const char input[], int &pos) {
  while (input[pos] == ' ') {
    pos++;
  }
}

// Function to parse the user input manually using a C-style string
bool parseInput(const char input[], int &integer, int &sign, int primes[], int exponents[], int &count) {
  int pos = 0;
  bool valid = true;

  // Parse the integer on the left-hand side of the equation
  skipSpaces(input, pos);  // Skip any spaces
  bool negativeInteger = false;
  if (input[pos] == '-') {
    negativeInteger = true;
    pos++;
  }

  integer = 0;
  while (input[pos] >= '0' && input[pos] <= '9') {
    integer = integer * 10 + (input[pos] - '0');
    pos++;
  }

  if (negativeInteger) {
    integer = -integer;
  }

  skipSpaces(input, pos);  // Skip any spaces

  // Skip the '=' sign
  if (input[pos] != '=') {
    return false;
  }
  pos++;
  skipSpaces(input, pos);  // Skip spaces after '='

  // Parse the sign (must be either 1 or -1)
  bool negativeSign = false;
  if (input[pos] == '-') {
    negativeSign = true;
    pos++;
  }

  if (input[pos] != '1') {
    return false;  // Invalid sign (should be either 1 or -1)
  }

  sign = negativeSign ? -1 : 1;
  pos++;

  skipSpaces(input, pos);  // Skip spaces after '1' or '-1'

  // Start parsing the prime factors and exponents
  count = 0;
  while (input[pos] != '?' && input[pos] != '\0' && input[pos] != '\n') {
    if (input[pos] == '\n' || input[pos] == '\r') {
      break;
    }

    if (input[pos] != '*') {
      return false;  // Expected multiplication symbol
    }
    pos++;
    skipSpaces(input, pos);  // Skip spaces after '*'

    // Parse the prime number
    int prime = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
      prime = prime * 10 + (input[pos] - '0');
      pos++;
    }

    if (!isPrime(prime)) {
      return false;  // Not a prime number
    }

    primes[count] = prime;

    skipSpaces(input, pos);  // Skip spaces after prime number

    // Parse the exponent, expect '^'
    if (input[pos] != '^') {
      return false;  // Expected '^'
    }
    pos++;
    skipSpaces(input, pos);  // Skip spaces after '^'

    int exponent = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
      exponent = exponent * 10 + (input[pos] - '0');
      pos++;
    }

    exponents[count] = exponent;
    count++;

    skipSpaces(input, pos);  // Skip spaces after exponent
  }

  // Ensure the input ends with '?' and nothing else (except for possible newline)
  if (input[pos] != '?' || (input[pos + 1] != '\0' && input[pos + 1] != '\n' && input[pos + 1] != '\r')) {
    return false;  // Input doesn't end with '?'
  }

  return valid;
}

// Function to calculate the prime factorization of a number
void factorize(int number, int primes[], int exponents[], int &count) {
  count = 0;
  int absNumber = (number < 0) ? -number : number;

  for (int i = 2; i * i <= absNumber; ++i) {
    if (isPrime(i)) {
      int exponent = 0;
      while (absNumber % i == 0) {
        absNumber /= i;
        exponent++;
      }
      if (exponent > 0) {
        primes[count] = i;
        exponents[count] = exponent;
        count++;
      }
    }
  }

  if (absNumber > 1) {
    primes[count] = absNumber;
    exponents[count] = 1;
    count++;
  }
}

// Helper function to manually sort primes and exponents based on the primes
void sortPrimesAndExponents(int primes[], int exponents[], int count) {
  for (int i = 0; i < count - 1; ++i) {
    for (int j = i + 1; j < count; ++j) {
      if (primes[i] > primes[j]) {
        // Swap primes
        int tempPrime = primes[i];
        primes[i] = primes[j];
        primes[j] = tempPrime;

        // Swap corresponding exponents
        int tempExponent = exponents[i];
        exponents[i] = exponents[j];
        exponents[j] = tempExponent;
      }
    }
  }
}