#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double uniform_distribution(double a, double b) {
  double random_num =
      ((double)rand() / RAND_MAX); // Generate a random number between 0 and 1

  double scaled_num =
      random_num * (b - a); // Scale the random number to the desired range
  double shifted_num =
      scaled_num + a; // Shift the scaled number to the desired lower bound
  return shifted_num;
}

int main() {
  srand(time(NULL)); // Seed the random number generator with the current time

  double lower_bound = 1.0;
  double upper_bound = 10.0;

  int num_samples = 10;
  int i;

  printf("Generating %d samples from a uniform distribution between %.2f and "
         "%.2f:\n",
         num_samples, lower_bound, upper_bound);

  for (i = 0; i < num_samples; i++) {
    double sample = uniform_distribution(lower_bound, upper_bound);
    printf("%.2f\n", sample);
  }

  return 0;
}
