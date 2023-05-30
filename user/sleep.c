#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("sleep: missing operand\n");
    return 0;
  }
  int time = atoi(argv[1]);
  sleep(time);
  return 0;
}
