### **The Purpose of the Program**

The objective of the program is to verify if the user-provided prime factorization of a given integer is correct. The user inputs a number and its factorization, and the program checks whether the factorization is mathematically correct. The program also ensures that the input format strictly adheres to the specification, rejecting inputs with incorrect formatting.

### **Overview of the Main Functions**

The program has several key components:

1. **`main()`**: The central function that drives the program. It reads input, calls other functions, and generates the final output.
2. **`parseInput()`**: This function is responsible for parsing and validating the input string, extracting the integer, sign, prime factors, and exponents.
3. **`factorize()`**: This function computes the correct prime factorization of the input integer.
4. **`isPrime()`**: This function checks whether a number is prime.
5. **`sortPrimesAndExponents()`**: This function sorts the prime factors and their corresponding exponents in ascending order.

---

### **Main Method (`main()`)**

```cpp
int main() {
    char input[256];
    cin.getline(input, 256); // Read the entire input as a C-style string
```

1. **Variable `input[256]`**: We define a character array `input[256]` to store the user’s input string, because we are not allowed to use the `string` library.
2. **`cin.getline(input, 256)`**: This command reads the entire input line (up to 256 characters) and stores it in `input[]`. It’s important to use `getline` because we want to capture the entire input, which may contain spaces.

---

```cpp
int number, sign, userPrimes[10], userExponents[10], count = 0;
if (!parseInput(input, number, sign, userPrimes, userExponents, count)) {
    cout << "Invalid input format." << endl;
    return 0;
}
```

3. **Variables Defined**:

   - `number`: This will store the integer part of the input (the number being factorized).
   - `sign`: This will store either `1` or `-1`, representing whether the number is positive or negative.
   - `userPrimes[10]`: This array will hold the prime factors provided by the user. We assume there will be no more than 10 prime factors.
   - `userExponents[10]`: This array will hold the exponents corresponding to each prime factor.
   - `count`: This variable will store the number of prime-exponent pairs parsed from the input.

4. **Calling `parseInput()`**: The `parseInput` function takes the user’s input and parses it. If the input is valid, the function extracts the number, the sign, the primes, and the exponents. If the input is invalid, it returns `false`, and the program outputs "Invalid input format." and exits.

---

```cpp
int correctPrimes[10], correctExponents[10], correctCount = 0;
factorize(number, correctPrimes, correctExponents, correctCount);
```

5. **Variables for the Correct Factorization**:

   - `correctPrimes[10]`: This array will hold the correct prime factors after factorizing `number`.
   - `correctExponents[10]`: This array will hold the correct exponents for the prime factors.
   - `correctCount`: This will store the number of prime-exponent pairs in the correct factorization.

6. **Calling `factorize()`**: This function performs the prime factorization of `number` and fills the `correctPrimes[]` and `correctExponents[]` arrays with the prime factors and their exponents, respectively.

---

```cpp
sortPrimesAndExponents(userPrimes, userExponents, count);
sortPrimesAndExponents(correctPrimes, correctExponents, correctCount);
```

7. **Sorting Prime Factors**: Both the user’s primes and the correct primes must be sorted in ascending order before comparison. This is because the user can input the primes in any order, but the comparison must be done in a consistent manner.

---

```cpp
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
```

8. **Comparison Logic**: The program checks whether the user’s prime factors and exponents match the correct prime factors and exponents:
   - First, it checks whether the number of prime-exponent pairs (`count`) matches the correct count (`correctCount`).
   - If the counts match, the program compares each prime and its corresponding exponent. If any prime or exponent doesn’t match, the input is considered incorrect.

---

```cpp
if (correct) {
    cout << "Correct!" << endl;
} else {
    cout << "Incorrect. " << number << " = " << (number < 0 ? "-1" : "1");
    for (int i = 0; i < correctCount; i++) {
        cout << " * " << correctPrimes[i] << "^" << correctExponents[i];
    }
    cout << endl;
}
```

9. **Generating Output**:
   - If the input factorization is correct, the program outputs `"Correct!"`.
   - If the factorization is incorrect, the program outputs `"Incorrect."` followed by the correct factorization in the required format, including the sign (`-1` or `1`), and the prime-exponent pairs.

---

### **Deep Dive into `parseInput()`**

This is the most critical function in the program. It parses the user’s input, checks if the format is valid, and extracts the relevant information (integer, sign, prime factors, and exponents).

```cpp
bool parseInput(const char input[], int &integer, int &sign, int primes[], int exponents[], int &count) {
    int pos = 0;
    bool valid = true;
```

- **Parameters**:
  - `input[]`: The user’s input string.
  - `integer`: This will store the integer being factorized.
  - `sign`: This will store the sign (`1` or `-1`).
  - `primes[]`: This array will hold the prime factors.
  - `exponents[]`: This array will hold the exponents.
  - `count`: This will store the number of prime-exponent pairs.
- **Variables**:
  - `pos`: This variable tracks the current position in the input string as we parse it.
  - `valid`: This is a flag to indicate whether the input is valid.

---

#### **Step 1: Parse the Integer**

```cpp
skipSpaces(input, pos);
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
```

1. **Skip Spaces**: The function skips over any spaces at the beginning of the input.
2. **Check for Negative Sign**: If the integer is negative, we store this information by setting `negativeInteger = true` and moving past the `-` sign.
3. **Extract the Integer**: The function reads each digit of the integer, constructing the full number.
4. **Apply Negative Sign**: If the integer was marked as negative, we apply the negative sign.

**Issue Encountered:**

- In earlier tests, we had issues with input format when handling negative numbers and spaces around the sign. This was fixed by introducing the `skipSpaces()` function to handle flexible spacing and properly managing the negative sign.

---

#### **Step 2: Check for Equals Sign (`=`)**

```cpp
skipSpaces(input, pos);
if (input[pos] != '=') {
    return false;
}
pos++;
```

After extracting the integer, the function expects an equals sign (`=`). If the `=` is missing, the input is invalid.

---

#### **Step 3: Parse the Sign (`1` or `-1`)**

```cpp
skipSpaces(input, pos);
bool negativeSign = false;
if (input[pos] == '-') {
    negativeSign = true;
    pos++;
}
if (input[pos] != '1') {
    return false;  // Sign must be 1 or -1
}
sign = negativeSign ? -1 : 1;
pos++;
```

Next, the function expects either `1` or `-1`. If the sign is negative, it will be indicated by a `-` symbol before the `1`.

---

#### **Step 4: Parse Prime Factors and Exponents**

```cpp
count = 0;
while (input[pos] != '?' && input[pos] != '\0' && input[pos] != '\n') {
    if (input[pos] != '*') {
        return false;  // Expected multiplication symbol
    }
    pos++;
    skipSpaces(input, pos);

    // Parse prime

 number
    int prime = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
        prime = prime * 10 + (input[pos] - '0');
        pos++;
    }
    if (!isPrime(prime)) {
        return false;  // Ensure the number is a prime
    }
    primes[count] = prime;

    skipSpaces(input, pos);

    // Parse exponent after '^'
    if (input[pos] != '^') {
        return false;  // Expected ^ symbol
    }
    pos++;
    skipSpaces(input, pos);

    int exponent = 0;
    while (input[pos] >= '0' && input[pos] <= '9') {
        exponent = exponent * 10 + (input[pos] - '0');
        pos++;
    }
    exponents[count] = exponent;
    count++;  // Count the number of prime-exponent pairs
}
```

1. **Loop to Parse Each Prime-Exponent Pair**: This loop extracts prime numbers and their exponents from the input. It expects the prime-exponent pairs to be separated by the multiplication symbol (`*`).
2. **Extract Prime**: The program reads the prime number, checks if it’s actually prime using the `isPrime()` function, and stores it in the `primes[]` array.
3. **Extract Exponent**: The exponent is parsed after the `^` symbol and stored in the `exponents[]` array.

**Issue Encountered:**

- We initially had issues handling inputs where users entered primes in different orders, which caused the program to incorrectly reject correct factorizations. We fixed this by introducing sorting later on.

---

#### **Step 5: Check for Question Mark (`?`)**

```cpp
skipSpaces(input, pos);
if (input[pos] != '?' || (input[pos + 1] != '\0' && input[pos + 1] != '\n' && input[pos + 1] != '\r')) {
    return false;
}
```

The input must end with a `?`. If there’s anything else after the question mark, the input is considered invalid.

---

### **Sorting Primes and Exponents (`sortPrimesAndExponents`)**

Since the prime factors can be entered in any order, we must sort them in ascending order to ensure the user’s input matches the correct factorization. Here’s how the manual bubble sort works:

```cpp
void sortPrimesAndExponents(int primes[], int exponents[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (primes[i] > primes[j]) {
                int tempPrime = primes[i];
                primes[i] = primes[j];
                primes[j] = tempPrime;
                int tempExponent = exponents[i];
                exponents[i] = exponents[j];
                exponents[j] = tempExponent;
            }
        }
    }
}
```

1. **Nested Loops**: The outer loop picks each prime in the array, and the inner loop compares it with every other prime.
2. **Swapping Primes and Exponents**: If the current prime is greater than the next, we swap the primes. We also swap the corresponding exponents to maintain the prime-exponent pair.

**Issue Encountered:**

- Without sorting, the program incorrectly rejected inputs where the prime factors were in the wrong order. This sorting function fixed the issue.

---

### **Conclusion**

This program validates the prime factorization of an integer by parsing the input, factorizing the number, and comparing the input against the correct factorization. We encountered several challenges, especially related to input parsing, handling of signs, and output formatting. We resolved these by refining the parsing logic, implementing a custom sorting function, and ensuring the output followed strict formatting rules.
