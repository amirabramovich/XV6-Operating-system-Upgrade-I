#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  policy(atoi(argv[1]));
  exit(0);
}