# zeromath
a tool of windows for math{simple}


## 1. Project Overview

**Super Math Calculator v1.0** is a versatile, terminal-based computational suite designed to handle a wide array of mathematical, statistical, and conversion tasks. Developed in standard C, this application provides a unified interface for basic arithmetic, scientific functions, statistical analysis, unit conversions, and number base transformations.

The program features a modular architecture, robust input validation, and a persistent calculation history feature. It is designed to be lightweight, portable, and easy to extend, making it an excellent tool for students, engineers, and developers who need quick, reliable calculations without the overhead of a graphical user interface.

### 1.1 Core Objectives
*   **Comprehensive Utility:** Consolidate multiple calculator types (Basic, Scientific, Statistical, etc.) into a single executable.
*   **Data Persistence:** Implement a rolling history buffer to allow users to review previous calculations.
*   **User-Friendly Interface:** Provide clear menus, error handling, and cross-platform compatibility (Windows/Linux/macOS).
*   **Extensibility:** Use a modular function structure that allows for easy addition of new features (e.g., Matrix operations, Financial tools).

### 1.2 Key Features
*   **Basic & Scientific Modes:** Supports standard arithmetic (`+`, `-`, `*`, `/`, `%`, `^`) and advanced functions (`sin`, `cos`, `tan`, `log`, `ln`, `sqrt`, `fabs`, `factorial`).
*   **Statistical Analysis:** Calculates Mean, Median, and Population Standard Deviation for dynamic datasets.
*   **Unit Converter:** Handles conversions for Length (m, cm, inch, feet), Temperature (C, F, K), and Weight (kg, pounds, grams).
*   **Number Base Converter:** Supports bidirectional conversion between Decimal, Binary, and Hexadecimal.
*   **Calculation History:** Stores the last 10 results in a circular buffer for quick reference.

---

## 2. System Architecture

### 2.1 Data Structures

The application uses a global array to manage calculation history:

```c
#define MAX_HISTORY 10
char history[MAX_HISTORY][100];
int historyCount = 0;
```

*   **`history`**: A 2D character array storing string representations of past calculations.
*   **`historyCount`**: Tracks the number of stored entries. When the limit is reached, the array shifts to act as a FIFO (First-In-First-Out) queue.

### 2.2 Module Structure

| Module | Function Name | Key Capabilities |
| :--- | :--- | :--- |
| **Core Loop** | `main()` | Menu dispatch, input validation, history management. |
| **Basic Math** | `basicCalculator()` | Arithmetic operations, modulo, power. |
| **Scientific** | `scientificCalculator()` | Trigonometry, logarithms, roots, factorial. |
| **Statistics** | `statisticsCalculator()` | Mean, Median (via sorting), Standard Deviation. |
| **Units** | `unitConverter()` | Length, Temperature, Weight conversions. |
| **Bases** | `numberBaseConverter()` | Dec <-> Bin, Dec <-> Hex. |
| **Utilities** | `addToHistory()`, `showHistory()` | History buffer management and display. |

---

## 3. Detailed Module Analysis

### 3.1 Input Validation Engine

A critical component of the system is its resilience against user error. The `main` loop and individual calculators use `scanf` return value checks:

```c
if (scanf("%d", &choice) != 1) {
    printf("Invalid input. Please enter a number.\n");
    while (getchar() != '\n'); // Clear buffer
    continue;
}
```
This prevents infinite loops when users enter characters instead of integers. Similarly, `basicCalculator` uses `scanf("%lf %c %lf", ...)` to parse expressions like `5 + 3`, ensuring robust parsing of space-separated inputs.

### 3.2 Statistics Calculator (`statisticsCalculator`)

This module implements a dynamic data ingestion process:
1.  **Input:** Users enter numbers separated by spaces. Input terminates upon entering a non-numeric character (e.g., 'q').
2.  **Mean Calculation:** Sum of all elements divided by count.
3.  **Median Calculation:**
    *   Implements a **Bubble Sort** algorithm to order the `numbers` array.
    *   Selects the middle element (or average of two middle elements) based on parity of the count.
4.  **Standard Deviation:** Calculates population variance ($\sigma^2$) and then the square root for $\sigma$.

> **Note:** The current implementation uses Population Standard Deviation. For sample data, dividing by `count - 1` would be more appropriate.

### 3.3 Unit Converter (`unitConverter`)

The converter uses a **Two-Step Normalization Strategy**:
1.  **To Base Unit:** Convert the input value to a standard base unit (e.g., meters for length, Celsius for temperature, kilograms for weight).
2.  **From Base Unit:** Convert the base unit value to the desired target unit.

**Example (Length):**
*   Input: `10 feet` -> Convert to `3.048 meters`.
*   Target: `inch` -> Convert `3.048 meters` to `120 inches`.

This approach reduces the complexity of $N^2$ conversion factors to $2N$ factors.

### 3.4 Number Base Converter (`numberBaseConverter`)

*   **Decimal to Binary:** Uses a modulo-2 algorithm to extract bits, stores them in a char array, and then reverses the string.
*   **Decimal to Hex:** Utilizes `sprintf` with `%llX` format specifier for efficient conversion.
*   **Binary/Hex to Decimal:** Uses `strtoll` (String to Long Long) with base parameters (2 for binary, 16 for hex) for robust parsing.

### 3.5 History Management (`addToHistory`)

The history system implements a **Sliding Window**:
*   If `historyCount < MAX_HISTORY`, the new entry is appended.
*   If full, the array shifts all elements up by one index (`history[i] = history[i+1]`), dropping the oldest entry, and appends the new one at the end.
*   This ensures the most recent 10 calculations are always available.

---

## 4. User Interface & Experience

### 4.1 Menu System
The interface is text-based, using a `do-while` loop in `main()` to keep the program running until the user selects '0'.

**Sample Menu:**
```text
===== Main Menu =====
1. Basic Calculator
2. Scientific Calculator
3. Statistics Calculator
4. Matrix Calculator (Coming Soon)
...
0. Exit
```

### 4.2 Output Formatting
*   **Basic/Scientific:** Results are printed to 2 decimal places (`%.2lf`).
*   **Statistics:** Results are printed to 4 decimal places (`%.4f`) for higher precision.
*   **Units:** Results vary based on type (e.g., `%.4lf` for length, `%.2lf` for temperature).

---

## 5. Compilation and Deployment

### 5.1 Prerequisites
*   **Compiler:** GCC, Clang, or MSVC.
*   **Standard Library:** Requires `<stdio.h>`, `<stdlib.h>`, `<math.h>`, `<string.h>`, `<ctype.h>`.
*   **Linking:** On Linux/macOS, link the math library using `-lm`.

### 5.2 Build Instructions

**On Linux/macOS:**
```bash
gcc main.c -o super_calc -lm -std=c99
./super_calc
```

**On Windows (MinGW):**
```cmd
gcc main.c -o super_calc.exe -lm
super_calc.exe
```

**On Windows (MSVC):**
```cmd
cl main.c
super_calc.exe
```

---

## 6. Code Quality & Best Practices

### 6.1 Strengths
1.  **Modularity:** Each calculator is a separate function, making the code easy to read and debug.
2.  **Input Safety:** Extensive use of buffer clearing (`while (getchar() != '\n')`) prevents input stream corruption.
3.  **Cross-Platform:** Uses standard C libraries, ensuring it runs on any OS with a C compiler.
4.  **History Feature:** Adds significant utility by allowing users to track their work.

### 6.2 Areas for Improvement
1.  **Trigonometric Units:** The `scientificCalculator` assumes inputs are in **Radians**. Most casual users expect **Degrees**. Adding a degree-to-radian conversion step would improve usability.
2.  **Factorial Limit:** The factorial function uses `long long`, which overflows at $21!$. For larger numbers, a arbitrary-precision library or double-approximation would be needed.
3.  **Statistics Sorting:** Bubble Sort is $O(N^2)$. For large datasets, `qsort` from `<stdlib.h>` would be more efficient.
4.  **Placeholder Functions:** Several functions (Matrix, Financial, Geometry) are currently placeholders. Implementing these would complete the "Super" aspect of the calculator.

---

## 7. Future Roadmap

### 7.1 Short-Term Enhancements
*   **Degree/Radian Toggle:** Add a global state or menu option to switch trigonometric input modes.
*   **Matrix Implementation:** Implement basic matrix operations (Addition, Multiplication, Determinant) using 2D arrays.
*   **File Output:** Allow users to save calculation history to a `.txt` file.

### 7.2 Long-Term Vision
*   **Graphing Capability:** Integrate with a lightweight plotting library to visualize functions.
*   **Symbolic Math:** Integrate a library like GiNaC for algebraic manipulation.
*   **GUI Frontend:** Port the logic to a graphical interface using Qt or GTK for a modern user experience.

---

## 8. Conclusion

**Super Math Calculator v1.0** is a robust, well-structured educational and practical tool that effectively bridges the gap between simple arithmetic and complex scientific computation. Its emphasis on input validation, modular design, and user-friendly features like history tracking makes it a reliable resource for students and professionals alike. By combining everything from basic addition to statistical analysis and unit conversion, it offers a comprehensive "Swiss Army Knife" for mathematical tasks in a lightweight, portable C package.
