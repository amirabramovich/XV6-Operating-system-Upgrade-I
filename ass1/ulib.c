#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

int
indexof(const char *s, char c)
{
  for(int i=0; *s; s++){
    if(*s == c)
      return i;
    ++i;
  }
  return 0;
}

int
indexof2(const char *s, char c, int start)
{
  int i=0;
  for(; i<start; s++)
    ++i;
  for(; *s; s++){
    if(*s == c)
      return i;
    ++i;
  }
  return 0;
}

char*
strcpy2(char *s, char *t, int start, int end)
{
  char *os;
  int i=0;
  for(; i<start; t++)
    ++i;
  os = s;
  for(int i=start;i<end;i++)
    *s++ = *t++;
  return os;
}

char*
append(char *str1, char *str2, char *buff)
{
  char *output;
  output = buff;
  int i=0;
  int firstlen = strlen(str1);
  int secondlen = strlen(str2);
  // printf(2, "firstlen is %d secondlen is %d\n", firstlen,secondlen);
  // printf(2, "buff is %s\n", output);
  for(; i<firstlen;++i){
    *buff++ = *str1++;
    // printf(2, "i is %d\n", i);
  }
  // printf(2, "buff is %s\n", output);
  for(; i<firstlen+secondlen;++i){
    *buff++ = *str2++;
  }
  // printf(2, "buff is %s\n", output);
  return output;
}
