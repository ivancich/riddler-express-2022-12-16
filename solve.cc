#include <iostream>
#include <stdlib.h>

void explain(int a, int b, int c, const int end) {
    std::cout << a << ", " << b;
    do {
        std::cout << ", " << c;
        int new_c = a + b + c;
        a = b;
        b = c;
        c = new_c;
    } while (c <= end);
    std::cout << std::endl;
}

int solve (int a, int b, int c, const int best, const int end) {
    int new_a = c - b - a;
    while (new_a <= a && new_a >= 1) {
        c = b;
        b = a;
        a = new_a;
        new_a = c - b - a;
    }
    int sum = a + b + c;
    if (sum < best) {
        explain(a, b, c, end);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    int goal = 2023;
    if (argc > 1) {
        long l = strtol(argv[1], nullptr, 10);
        if (errno != 0) {
            std::cerr << "Error: \"" << argv[1] << "\" could not be interpreted as a number." << std::endl;
            exit(1);
        }
        goal = int(l);
    }

    int best = INT_MAX;

    for (int c = goal; c >= 1; c--) {
        for (int b = c; b >= 1; b--) {
            const int a = goal - b - c;
            if (a > b) {
                break;
            }

            int len = solve(a, b, c, best, goal);
            if (len < best) {
                best = len;
            }
        }
    }
}
