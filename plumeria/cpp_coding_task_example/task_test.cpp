//
// You don't have to look at the code in this file, it will test the correctness
// of the functions in `task.h`
//

#include <iostream>

#include "task.h"

void test_example1() {
  std::cout << "\nTEST example1\n";

  const int input = 15;
  const int expected_result = 17;
  const int actual_result = example1(input);

  if (expected_result == actual_result) {
    std::cout << "PASS\n";
  } else {
    std::cout << "FAIL expected " << expected_result << " but received "
              << actual_result << "\n";
  }
}

void test_example2() {
  std::cout << "\nTEST example2\n";

  const int input = 15;
  const int expected_result = 30;
  const int actual_result = example2(input);

  if (expected_result == actual_result) {
    std::cout << "PASS\n";
  } else {
    std::cout << "FAIL expected " << expected_result << " but received "
              << actual_result << "\n";
  }
}

int main(int argc, char *argv[]) {
  test_example1();
  test_example2();
  return 0;
}
