#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define PRIME 101
#define MODULO 4294967296

uint64_t calculate_hash(const char *str, int length) {
    uint64_t hash = 0;
    uint64_t q_power = 1;
    for (int i = length - 1; i >= 0; i--) {
        hash = (hash + str[i] * q_power) % MODULO;
        q_power = (q_power * PRIME) % MODULO;
    }
    return hash;
}

uint64_t update_hash(uint64_t hash, char old_char, char new_char, uint64_t q_power_m) {
    hash = (hash - old_char * q_power_m + MODULO) % MODULO;
    hash = (hash * PRIME + new_char) % MODULO;
    return hash;
}

void rabin_karp_search(const char *pattern, const char *text) {
    int m = strlen(pattern);
    int n = strlen(text);
    if (m > n) {
        return;
    }
    uint64_t pattern_hash = calculate_hash(pattern, m);
    uint64_t text_hash = calculate_hash(text, m);
    uint64_t q_power_m = 1;
    for (int i = 0; i < m - 1; i++) {
        q_power_m = (q_power_m * PRIME) % MODULO;
    }
    for (int i = 0; i <= n - m; i++) {
        if (pattern_hash == text_hash) {
            if (strncmp(&text[i], pattern, m) == 0) {
                printf("%d\n", i);
            }
        }
        if (i < n - m) {
            text_hash = update_hash(text_hash, text[i], text[i + m], q_power_m);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <text>\n", argv[0]);
        return 1;
    }
    const char *pattern = argv[1];
    const char *text = argv[2];
    rabin_karp_search(pattern, text);
    return 0;
}

