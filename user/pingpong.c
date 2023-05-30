#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int fds1[2]; // parent write to child
  int fds2[2]; // child write to parent

  pipe(fds1);
  pipe(fds2);

  if (fork() == 0) {
    int pid = getpid();
    char ch = 'A';
    read(fds1[0], &ch, 1);
    printf("%d: received ping\n", pid);
    write(fds2[1], &ch, 1);
  } else {
    int pid = getpid();
    char ch = 'A';
    write(fds1[1], &ch, 1);
    read(fds2[0], &ch, 1);
    printf("%d: received pong\n", pid);
  }
  return 0;
}
