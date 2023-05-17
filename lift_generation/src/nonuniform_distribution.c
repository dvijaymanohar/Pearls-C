#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VALUES 5

double empiricalProbabilities[NUM_VALUES] = {0.2, 0.3, 0.1, 0.15, 0.25};
double parameterValues[NUM_VALUES] = {1.0, 2.0, 3.0, 4.0, 5.0};

double generateNonUniformRandom() {
  double rand_num = ((double)rand() / RAND_MAX);
  double cumulative_prob = 0.0;

  for (int i = 0; i < NUM_VALUES; i++) {
    cumulative_prob += empiricalProbabilities[i];
    if (rand_num < cumulative_prob) {
      return parameterValues[i];
    }
  }

  return parameterValues[NUM_VALUES -
                         1]; // Fallback to the last parameter value
}

int main() {
  srand(time(NULL));

  // Generate and print 10 random numbers following the non-uniform empirical
  // distribution
  for (int i = 0; i < 10; i++) {
    double rand_num = generateNonUniformRandom();
    printf("Random Number %d: %.2f\n", i + 1, rand_num);
  }

  return 0;
}
