#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// Removed windows.h as it's not needed for English output
#include <time.h> // Needed for random number generator (placeholder for now)

#define MAX_HISTORY 10
#define MAX_STATS_COUNT 100 // Max numbers for statistics
#define MAX_UNIT_STR_LEN 20 // Max length for unit strings

// Global variables for history
char history[MAX_HISTORY][100];
int historyCount = 0;

// Function declarations
void displayMenu();
void addToHistory(const char* entry);
void showHistory();
void basicCalculator();
void scientificCalculator();
void statisticsCalculator(); // Implemented
void matrixCalculator();
void equationSolver();
void unitConverter(); // Implemented
void financialCalculator();
void geometryCalculator();
void numberBaseConverter(); // Implemented
void randomNumberGenerator();
void help();

int main() {
    // No need for Windows-specific console settings for English output
    int choice;

    printf("=== Super Math Calculator ===\n");

    do {
        displayMenu();
        printf("Enter your choice (0-12): ");
        // Check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            choice = -1; // Set to an invalid choice to loop again
            continue;
        }

        switch(choice) {
            case 1: basicCalculator(); break;
            case 2: scientificCalculator(); break;
            case 3: statisticsCalculator(); break; // Call implemented function
            case 4: matrixCalculator(); break;
            case 5: equationSolver(); break;
            case 6: unitConverter(); break; // Call implemented function
            case 7: financialCalculator(); break;
            case 8: geometryCalculator(); break;
            case 9: numberBaseConverter(); break; // Call implemented function
            case 10: randomNumberGenerator(); break;
            case 11: showHistory(); break;
            case 12: help(); break;
            case 0: printf("Thank you for using the calculator. Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}

// Displays the main menu
void displayMenu() {
    printf("\n===== Main Menu =====\n");
    printf("1. Basic Calculator\n");
    printf("2. Scientific Calculator\n");
    printf("3. Statistics Calculator\n");
    printf("4. Matrix Calculator (Coming Soon)\n");
    printf("5. Equation Solver (Coming Soon)\n");
    printf("6. Unit Converter\n");
    printf("7. Financial Calculator (Coming Soon)\n");
    printf("8. Geometry Calculator (Coming Soon)\n");
    printf("9. Number Base Converter\n");
    printf("10. Random Number Generator (Coming Soon)\n");
    printf("11. View History\n");
    printf("12. Help\n");
    printf("0. Exit\n");
}

// Adds an entry to the history
void addToHistory(const char* entry) {
    if(historyCount < MAX_HISTORY) {
        strncpy(history[historyCount], entry, 99);
        history[historyCount][99] = '\0'; // Ensure null termination
        historyCount++;
    } else {
        // Shift history entries up
        for(int i = 0; i < MAX_HISTORY-1; i++) {
            strcpy(history[i], history[i+1]);
        }
        // Add new entry to the end
        strncpy(history[MAX_HISTORY-1], entry, 99);
        history[MAX_HISTORY-1][99] = '\0'; // Ensure null termination
    }
}

// Shows the calculation history
void showHistory() {
    printf("\n=== Calculation History ===\n");
    if(historyCount == 0) {
        printf("No history yet.\n");
        return;
    }

    for(int i = 0; i < historyCount; i++) {
        printf("%d. %s\n", i+1, history[i]);
    }
}

// Basic arithmetic operations
void basicCalculator() {
    double num1, num2, result;
    char op;

    printf("\n=== Basic Calculator ===\n");
    printf("Enter expression (e.g., 5 + 3): ");
    // Use a space before %c to consume any leftover whitespace, including newline
    if (scanf("%lf %c %lf", &num1, &op, &num2) != 3) {
        printf("Invalid input format.\n");
        // Clear the input buffer
        while (getchar() != '\n');
        return;
    }

    char entry[100];
    int valid_op = 1;

    switch(op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
            if(num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: Division by zero!\n");
                return;
            }
            break;
        case '%': // Modulo for floating point numbers
            result = fmod(num1, num2);
            break;
        case '^': // Power
            result = pow(num1, num2);
            break;
        default:
            printf("Error: Invalid operator!\n");
            valid_op = 0;
            // Clear the input buffer
            while (getchar() != '\n');
            return;
    }

    if (valid_op) {
        sprintf(entry, "%.2lf %c %.2lf = %.2lf", num1, op, num2, result);
        addToHistory(entry);
        printf("Result: %.2lf\n", result);
    }
}

// Scientific calculations
void scientificCalculator() {
    int choice;
    double num, result;

    printf("\n=== Scientific Calculator ===\n");
    printf("1. Sine (sin)\n");
    printf("2. Cosine (cos)\n");
    printf("3. Tangent (tan)\n");
    printf("4. Logarithm (log10)\n");
    printf("5. Natural Logarithm (ln)\n");
    printf("6. Square Root\n");
    printf("7. Absolute Value\n");
    printf("8. Factorial\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter number: ");
     if (scanf("%lf", &num) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    char entry[100];
    int valid_calc = 1;

    switch(choice) {
        case 1:
            result = sin(num);
            sprintf(entry, "sin(%.2lf) = %.2lf", num, result);
            printf("sin(%.2lf) = %.2lf\n", num, result);
            break;
        case 2:
            result = cos(num);
            sprintf(entry, "cos(%.2lf) = %.2lf", num, result);
            printf("cos(%.2lf) = %.2lf\n", num, result);
            break;
        case 3:
            // Check for angles where tan is undefined (e.g., 90, 270 degrees)
            // Note: tan(x) in C uses radians. Need to convert degrees if user inputs degrees.
            // Assuming input is in radians for now.
            if (cos(num) == 0) { // Check if cosine is zero
                 printf("Error: Tangent is undefined for this angle.\n");
                 valid_calc = 0;
            } else {
                result = tan(num);
                sprintf(entry, "tan(%.2lf) = %.2lf", num, result);
                printf("tan(%.2lf) = %.2lf\n", num, result);
            }
            break;
        case 4:
            if(num > 0) {
                result = log10(num);
                sprintf(entry, "log10(%.2lf) = %.2lf", num, result);
                printf("log10(%.2lf) = %.2lf\n", num, result);
            } else {
                printf("Error: Logarithm argument must be greater than zero!\n");
                valid_calc = 0;
            }
            break;
        case 5:
            if(num > 0) {
                result = log(num); // Natural logarithm
                sprintf(entry, "ln(%.2lf) = %.2lf", num, result);
                printf("ln(%.2lf) = %.2lf\n", num, result);
            } else {
                printf("Error: Natural logarithm argument must be greater than zero!\n");
                valid_calc = 0;
            }
            break;
        case 6:
            if(num >= 0) {
                result = sqrt(num);
                sprintf(entry, "sqrt(%.2lf) = %.2lf", num, result);
                printf("sqrt(%.2lf) = %.2lf\n", num, result);
            } else {
                printf("Error: Square root argument must be non-negative!\n");
                valid_calc = 0;
            }
            break;
        case 7:
            result = fabs(num);
            sprintf(entry, "|%.2lf| = %.2lf", num, result);
            printf("|%.2lf| = %.2lf\n", num, result);
            break;
        case 8:
            if(num >= 0 && num == (int)num) {
                long long fact = 1; // Use long long for larger factorials
                for(int i = 1; i <= (int)num; i++) {
                    fact *= i;
                }
                result = (double)fact; // Convert back to double for printing consistency
                sprintf(entry, "%d! = %.0lf", (int)num, result);
                printf("%d! = %.0lf\n", (int)num, result);
            } else {
                printf("Error: Factorial argument must be a non-negative integer!\n");
                valid_calc = 0;
            }
            break;
        default:
            printf("Error: Invalid choice!\n");
            valid_calc = 0;
    }

    if (valid_calc) {
        addToHistory(entry);
    }
}

// Statistics calculations (Implemented: Mean, Median, Standard Deviation)
void statisticsCalculator() {
    printf("\n=== Statistics Calculator ===\n");
    printf("Enter up to %d numbers, separated by spaces.\n", MAX_STATS_COUNT);
    printf("Enter a non-numeric character (e.g., 'q') to finish input.\n");

    double numbers[MAX_STATS_COUNT];
    int count = 0;
    double sum = 0.0;

    // Read numbers from input
    while (count < MAX_STATS_COUNT && scanf("%lf", &numbers[count]) == 1) {
        sum += numbers[count];
        count++;
    }

    // Clear the rest of the input buffer
    while (getchar() != '\n');

    if (count == 0) {
        printf("No numbers entered.\n");
        return;
    }

    // Calculate Mean
    double mean = sum / count;
    printf("Mean: %.4f\n", mean);

    // Calculate Median (requires sorting)
    // Simple bubble sort for demonstration
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                double temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    double median;
    if (count % 2 == 0) {
        median = (numbers[count / 2 - 1] + numbers[count / 2]) / 2.0;
    } else {
        median = numbers[count / 2];
    }
    printf("Median: %.4f\n", median);

    // Calculate Standard Deviation
    double sum_sq_diff = 0.0;
    for (int i = 0; i < count; i++) {
        sum_sq_diff += pow(numbers[i] - mean, 2);
    }
    double variance = sum_sq_diff / count; // Population variance
    double std_dev = sqrt(variance); // Population standard deviation
    printf("Population Standard Deviation: %.4f\n", std_dev);

    // Add a summary to history
    char entry[100];
    sprintf(entry, "Statistics: Count=%d, Mean=%.2f, Median=%.2f, StdDev=%.2f", count, mean, median, std_dev);
    addToHistory(entry);
}

// Matrix Calculator (Placeholder)
void matrixCalculator() {
    printf("\nMatrix Calculator functionality coming soon.\n");
}

// Equation Solver (Placeholder)
void equationSolver() {
    printf("\nEquation Solver functionality coming soon.\n");
}

// Unit Converter (Implemented: Length, Temperature, Weight)
void unitConverter() {
    printf("\n=== Unit Converter ===\n");
    printf("Select conversion type:\n");
    printf("1. Length (m, cm, inch, feet)\n");
    printf("2. Temperature (°C, °F, K)\n");
    printf("3. Weight (kg, pounds, grams)\n");
    printf("Enter your choice: ");
    int type_choice;
     if (scanf("%d", &type_choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    double value, result;
    char from_unit[MAX_UNIT_STR_LEN], to_unit[MAX_UNIT_STR_LEN];

    printf("Enter value to convert: ");
     if (scanf("%lf", &value) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    printf("Enter unit to convert from (e.g., m, C, kg): ");
    scanf("%s", from_unit);
    printf("Enter unit to convert to (e.g., inch, F, pounds): ");
    scanf("%s", to_unit);

    // Convert units to lowercase for easier comparison
    for(int i = 0; from_unit[i]; i++){ from_unit[i] = tolower(from_unit[i]); }
    for(int i = 0; to_unit[i]; i++){ to_unit[i] = tolower(to_unit[i]); }

    char entry[100];
    int converted = 0;

    switch (type_choice) {
        case 1: // Length
            // Convert 'from_unit' to meters first
            double value_in_meters;
            if (strcmp(from_unit, "m") == 0) value_in_meters = value;
            else if (strcmp(from_unit, "cm") == 0) value_in_meters = value / 100.0;
            else if (strcmp(from_unit, "inch") == 0) value_in_meters = value * 0.0254;
            else if (strcmp(from_unit, "feet") == 0) value_in_meters = value * 0.3048;
            else { printf("Invalid 'from' unit for length.\n"); return; }

            // Convert from meters to 'to_unit'
            if (strcmp(to_unit, "m") == 0) result = value_in_meters;
            else if (strcmp(to_unit, "cm") == 0) result = value_in_meters * 100.0;
            else if (strcmp(to_unit, "inch") == 0) result = value_in_meters / 0.0254;
            else if (strcmp(to_unit, "feet") == 0) result = value_in_meters / 0.3048;
            else { printf("Invalid 'to' unit for length.\n"); return; }

            converted = 1;
            sprintf(entry, "%.2lf %s to %s = %.4lf %s", value, from_unit, to_unit, result, to_unit);
            break;

        case 2: // Temperature
            // Convert 'from_unit' to Celsius first
            double value_in_celsius;
            if (strcmp(from_unit, "c") == 0) value_in_celsius = value;
            else if (strcmp(from_unit, "f") == 0) value_in_celsius = (value - 32.0) * 5.0/9.0;
            else if (strcmp(from_unit, "k") == 0) value_in_celsius = value - 273.15;
            else { printf("Invalid 'from' unit for temperature.\n"); return; }

            // Convert from Celsius to 'to_unit'
            if (strcmp(to_unit, "c") == 0) result = value_in_celsius;
            else if (strcmp(to_unit, "f") == 0) result = (value_in_celsius * 9.0/5.0) + 32.0;
            else if (strcmp(to_unit, "k") == 0) result = value_in_celsius + 273.15;
            else { printf("Invalid 'to' unit for temperature.\n"); return; }

            converted = 1;
            sprintf(entry, "%.2lf %s to %s = %.2lf %s", value, from_unit, to_unit, result, to_unit);
            break;

        case 3: // Weight
            // Convert 'from_unit' to kilograms first
            double value_in_kg;
            if (strcmp(from_unit, "kg") == 0) value_in_kg = value;
            else if (strcmp(from_unit, "pounds") == 0) value_in_kg = value * 0.453592;
            else if (strcmp(from_unit, "grams") == 0) value_in_kg = value / 1000.0;
            else { printf("Invalid 'from' unit for weight.\n"); return; }

            // Convert from kilograms to 'to_unit'
            if (strcmp(to_unit, "kg") == 0) result = value_in_kg;
            else if (strcmp(to_unit, "pounds") == 0) result = value_in_kg / 0.453592;
            else if (strcmp(to_unit, "grams") == 0) result = value_in_kg * 1000.0;
            else { printf("Invalid 'to' unit for weight.\n"); return; }

            converted = 1;
            sprintf(entry, "%.2lf %s to %s = %.4lf %s", value, from_unit, to_unit, result, to_unit);
            break;

        default:
            printf("Invalid conversion type choice.\n");
            return;
    }

    if (converted) {
        printf("Result: %s\n", entry);
        addToHistory(entry);
    }
}

// Financial Calculator (Placeholder)
void financialCalculator() {
    printf("\nFinancial Calculator functionality coming soon.\n");
}

// Geometry Calculator (Placeholder)
void geometryCalculator() {
    printf("\nGeometry Calculator functionality coming soon.\n");
}

// Number Base Converter (Implemented: Decimal, Binary, Hexadecimal)
void numberBaseConverter() {
    printf("\n=== Number Base Converter ===\n");
    printf("Select conversion type:\n");
    printf("1. Decimal to Binary\n");
    printf("2. Decimal to Hexadecimal\n");
    printf("3. Binary to Decimal\n");
    printf("4. Hexadecimal to Decimal\n");
    printf("Enter your choice: ");
    int type_choice;
     if (scanf("%d", &type_choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    long long decimal_num;
    char binary_num[64]; // Sufficient for 64-bit binary
    char hex_num[16];    // Sufficient for 64-bit hex

    char entry[100];

    switch (type_choice) {
        case 1: // Decimal to Binary
            printf("Enter a decimal integer: ");
             if (scanf("%lld", &decimal_num) != 1) {
                printf("Invalid input.\n");
                while (getchar() != '\n');
                return;
            }
            if (decimal_num < 0) {
                printf("Error: Cannot convert negative numbers to binary with this function.\n");
                return;
            }
            if (decimal_num == 0) {
                strcpy(binary_num, "0");
            } else {
                int i = 0;
                while (decimal_num > 0) {
                    binary_num[i] = (decimal_num % 2) + '0';
                    decimal_num /= 2;
                    i++;
                }
                binary_num[i] = '\0';
                // Reverse the string
                int len = strlen(binary_num);
                for (int j = 0; j < len / 2; j++) {
                    char temp = binary_num[j];
                    binary_num[j] = binary_num[len - j - 1];
                    binary_num[len - j - 1] = temp;
                }
            }
            sprintf(entry, "Decimal to Binary: %lld -> %s", decimal_num, binary_num); // Note: decimal_num is modified
            printf("Binary equivalent: %s\n", binary_num);
            break;

        case 2: // Decimal to Hexadecimal
            printf("Enter a decimal integer: ");
             if (scanf("%lld", &decimal_num) != 1) {
                printf("Invalid input.\n");
                while (getchar() != '\n');
                return;
            }
             if (decimal_num < 0) {
                printf("Error: Cannot convert negative numbers to hexadecimal with this function.\n");
                return;
            }
            sprintf(hex_num, "%llX", decimal_num); // Use %llX for long long hexadecimal
            sprintf(entry, "Decimal to Hex: %lld -> %s", decimal_num, hex_num);
            printf("Hexadecimal equivalent: %s\n", hex_num);
            break;

        case 3: // Binary to Decimal
            printf("Enter a binary number: ");
            scanf("%s", binary_num);
            decimal_num = 0;
            int power = 0;
            int invalid_binary = 0;
            for (int i = strlen(binary_num) - 1; i >= 0; i--) {
                if (binary_num[i] == '0' || binary_num[i] == '1') {
                    decimal_num += (binary_num[i] - '0') * pow(2, power);
                    power++;
                } else {
                    printf("Error: Invalid binary digit '%c'.\n", binary_num[i]);
                    invalid_binary = 1;
                    break;
                }
            }
            if (!invalid_binary) {
                sprintf(entry, "Binary to Decimal: %s -> %lld", binary_num, decimal_num);
                printf("Decimal equivalent: %lld\n", decimal_num);
            } else {
                 return; // Exit if invalid binary input
            }
            break;

        case 4: // Hexadecimal to Decimal
            printf("Enter a hexadecimal number: ");
            scanf("%s", hex_num);
            decimal_num = strtoll(hex_num, NULL, 16); // Convert hex string to long long decimal
            sprintf(entry, "Hex to Decimal: %s -> %lld", hex_num, decimal_num);
            printf("Decimal equivalent: %lld\n", decimal_num);
            break;

        default:
            printf("Invalid conversion type choice.\n");
            return;
    }
     addToHistory(entry);
}


// Random Number Generator (Placeholder)
void randomNumberGenerator() {
    printf("\nRandom Number Generator functionality coming soon.\n");
    // Example of how to use rand() and srand() if implementing
    // srand(time(NULL)); // Seed the random number generator
    // int random_num = rand() % 100; // Generate a random number between 0 and 99
    // printf("Random number: %d\n", random_num);
}

// Displays help information
void help() {
    printf("\n=== Help ===\n");
    printf("This is a multi-functional mathematics calculator supporting the following features:\n");
    printf("1. Basic Calculator - Supports addition, subtraction, multiplication, division, modulo, and power.\n");
    printf("2. Scientific Calculator - Supports trigonometric functions, logarithms, square root, absolute value, and factorial.\n");
    printf("3. Statistics Calculator - Calculates mean, median, and population standard deviation for a set of numbers.\n");
    printf("4. Matrix Calculator - (Coming Soon)\n");
    printf("5. Equation Solver - (Coming Soon)\n");
    printf("6. Unit Converter - Supports length, temperature, and weight conversions.\n");
    printf("7. Financial Calculator - (Coming Soon)\n");
    printf("8. Geometry Calculator - (Coming Soon)\n");
    printf("9. Number Base Converter - Supports conversions between Decimal, Binary, and Hexadecimal.\n");
    printf("10. Random Number Generator - (Coming Soon)\n");
    printf("11. History - View previous calculation results.\n");
    printf("12. Help - Display this help information.\n");
    printf("0. Exit - Exit the calculator program.\n");
}
