#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void pipeline(int fds1[2]) {
  int p;
  if (read(fds1[0], &p, sizeof(int)) != 0) {
    int fds2[2];
    pipe(fds2);

    if (fork() == 0) {
      pipeline(fds2);
    } else {
      int n;
      printf("prime %d\n",   p);
      while (read(fds1[0], &n, sizeof(n)) != 0) {
        if (n % p != 0) {
          write(fds2[1], &n, sizeof(n));
        }
      }
      close(fds1[0]);
      close(fds2[1]);
      int stat;
      wait(&stat);
    }
  }
}
int main(int argc, char *argv[]) {
  int fds[2];
  pipe(fds);

  if (fork() != 0) {
    for (int i = 2; i <= 35; i++) {
      write(fds[1], &i, sizeof(i));
    }
    close(fds[1]);
    int stat;
    wait(&stat);
  } else {
    pipeline(fds);
  }
  return 0;
}
