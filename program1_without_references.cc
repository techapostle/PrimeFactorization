#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Struct to store the parsed input
struct FactorizationResult {
  int primes[10];
  int exponents[10];
  int count;
};

// Protype for helper functions
bool isPrime(int n);
int skipSpaces(const char input[], int pos);
ParsedInput parseInput(const char input[]);
struct FactorizationResult;
FactorizationResult factorize(int number);
void sortPrimesAndExponents(int primes[], int exponents[], int count);

// Main function
int main() {
  char input[256];
  cin.getline(input, 256); // Read the entire input as a C-style string

  ParsedInput parsed = parseInput(input);
  if (!parsed.valid) {
    cout << "Invalid input format." << endl;
    return 0;
  }

  // Sort the user primes and exponents for correct comparison
  sortPrimesAndExponents(parsed.primes, parsed.exponents, parsed.count);

  // Calculate the correct prime factorization of the number
  FactorizationResult correctFactorization = factorize(parsed.integer);

  // Sort the correct primes and exponents for correct comparison
  sortPrimesAndExponents(correctFactorization.primes, correctFactorization.exponents, correctFactorization.count);

  // Compare the input prime factorization with the correct one
  bool correct = true;
  if (parsed.count != correctFactorization.count) {
    correct = false;
  } else {
    for (int i = 0; i < parsed.count; i++) {
      if (parsed.primes[i] != correctFactorization.primes[i] || parsed.exponents[i] != correctFactorization.exponents[i]) {
        correct = false;
        break;
      }
    }
  }

  // Output the result
  if (correct) {
    cout << "Correct!" << endl;
  } else {
    cout << "Incorrect. " << parsed.integer << " = ";

    // Adjust the output to correctly show -1 or 1 depending on the sign
    cout << (parsed.integer < 0 ? "-1" : "1");

    // Output the prime factorization
    for (int i = 0; i < correctFactorization.count; i++) {
      cout << " * " << correctFactorization.primes[i] << "^" << correctFactorization.exponents[i];
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
int skipSpaces(const char input[], int pos) {
  while (input[pos] == ' ') {
    pos++;
  }
  return pos;
}

// Function to parse the user input manually using a C-style string
struct ParsedInput {
  int integer;
  int sign;
  int primes[10];
  int exponents[10];
  int count;
  bool valid;
};

ParsedInput parseInput(const char input[]) {
  ParsedInput result;
  result.count = 0;
  result.valid = true;
  int pos = 0;

  // Parse the integer on the left-hand side of the equation
  pos = skipSpaces(input, pos);  // Skip any spaces
  bool negativeInteger = false;
  if (input[pos] == '-') {
    negativeInteger = true;
    pos++;
  }

  result.integer = 0;
  while (input[pos] >= '0' && input[pos] <= '9') {
    result.integer = result.integer * 10 + (input[pos] - '0');
    pos++;
  }

  if (negativeInteger) {
    result.integer = -result.integer;
  }

  pos = skipSpaces(input, pos);  // Skip any spaces

  // Skip the '=' sign
  if (input[pos] != '=') {
    result.valid = false;
    return result;
  }
  pos++;
  pos = skipSpaces(input, pos);  // Skip spaces after '='

  // Parse the sign (must be either 1 or -1)
  bool negativeSign = false;
  if (input[pos] == '-') {
    negativeSign = true;
    pos++;
  }

  if (input[pos] != '1') {
    result.valid = false;  // Invalid sign (should be either 1 or -1)
    return result;
  }

  result.sign = negativeSign ? -1 : 1;
  pos++;

  pos = skipSpaces(input, pos);  // Skip spaces after '1' or '-1'

  // Start parsing the prime factors and exponents
  result.count = 0;
  while (input[pos] != '?' && input[pos] != '\0' && input[pos] != '\n') {
    if (input[pos] == '\n' || input[pos] == '\r') {
      break;
    }

    if (input[pos] != '*') {
      result.valid = false;  // Expected multiplication symbol
      return result;
    }
    pos++;
    pos = skipSpaces(input, pos);  // Skip spaces after '*'

    // Parse the prime number
    int prime = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
      prime = prime * 10 + (input[pos] - '0');
      pos++;
    }

    if (!isPrime(prime)) {
      result.valid = false;  // Not a prime number
      return result;
    }

    result.primes[result.count] = prime;

    pos = skipSpaces(input, pos);  // Skip spaces after prime number

    // Parse the exponent, expect '^'
    if (input[pos] != '^') {
      result.valid = false;  // Expected '^'
      return result;
    }
    pos++;
    pos = skipSpaces(input, pos);  // Skip spaces after '^'

    int exponent = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
      exponent = exponent * 10 + (input[pos] - '0');
      pos++;
    }

    result.exponents[result.count] = exponent;
    result.count++;

    pos = skipSpaces(input, pos);  // Skip spaces after exponent
  }

  // Ensure the input ends with '?' and nothing else (except for possible newline)
  if (input[pos] != '?' || (input[pos + 1] != '\0' && input[pos + 1] != '\n' && input[pos + 1] != '\r')) {
    result.valid = false;  // Input doesn't end with '?'
  }

  return result;
}

// Function to calculate the prime factorization of a number
FactorizationResult factorize(int number) {
  FactorizationResult result;
  result.count = 0;
  int absNumber = (number < 0) ? -number : number;

  for (int i = 2; i * i <= absNumber; ++i) {
    if (isPrime(i)) {
      int exponent = 0;
      while (absNumber % i == 0) {
        absNumber /= i;
        exponent++;
      }
      if (exponent > 0) {
        result.primes[result.count] = i;
        result.exponents[result.count] = exponent;
        result.count++;
      }
    }
  }

  if (absNumber > 1) {
    result.primes[result.count] = absNumber;
    result.exponents[result.count] = 1;
    result.count++;
  }

  return result;
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