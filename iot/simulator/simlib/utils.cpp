#include "def.h"
#include <signal.h>
#include <time.h>
#include <unistd.h>

WINDOW* win;
const int DOCK_X = 0;
const int DOCK_Y = 7;
void (*push1_handle)() = NULL;
void (*push2_handle)() = NULL;

void
usr1_handle(int arg)
{
  if (push1_handle != NULL)
    push1_handle();
}

void
usr2_handle(int arg)
{
  if (push2_handle != NULL)
    push2_handle();
}

void
chkkb()
{
  char c;
  while (c = wgetch(win)) {
    switch (c) {
      case 'q':
        goto _exit;
      case '1':
        pins[PUSH1]->writeStat(HIGH);
        kill(getpid(), SIGUSR1);
        delay(KEY_PUSH_INTERVAL);
        pins[PUSH1]->writeStat(LOW);
        break;
      case '2':
        pins[PUSH2]->writeStat(HIGH);
        kill(getpid(), SIGUSR2);
        delay(KEY_PUSH_INTERVAL);
        pins[PUSH2]->writeStat(LOW);
        break;
    }
  }

_exit:
  endwin();
  exit(0);
}

void
init(void)
{
  pins[RED_LED] = new LEDPin();
  pins[YELLOW_LED] = new LEDPin();
  pins[GREEN_LED] = new LEDPin();
  pins[PUSH1] = new Pin();
  pins[PUSH2] = new Pin();

  win = initscr();
  noecho();

  std::thread p(chkkb);
  p.detach();

  signal(SIGUSR1, usr1_handle);
  signal(SIGUSR2, usr2_handle);

  led_init();
}

void
dock(void)
{
  wmove(win, DOCK_Y, DOCK_X);
}

void
delay(unsigned int s)
{
  usleep(s * 1000);
}

void
delayMicroseconds(unsigned int us)
{
  usleep(us);
}

unsigned long
millis(void)
{
  return clock() * 1000;
}

unsigned long
micros(void)
{
  return clock();
}

int
isAscii(int ch)
{
  return (ch >= 0 && ch < 128);
}

void
randomSeed(long s)
{
  srand(s);
}

unsigned long long
bit(int n)
{
  return 1 << n;
}

void
bitClear(unsigned long long* x, int n)
{
  *x &= ~(1 << n);
}

int
bitRead(unsigned long long x, int n)
{
  return (x & (1 << n)) != 0;
}

void
bitSet(unsigned long long* x, int n)
{
  *x |= 1 << n;
}

void
bitWrite(unsigned long long* x, int n, int b)
{
  return (b == 0) ? bitClear(x, n) : bitSet(x, n);
}

unsigned char
highByte(unsigned long long x)
{
  unsigned char mask = -1;
  int i, bitlen = sizeof(x) * 8;
  unsigned long long p = 1ULL << (bitlen - 1);
  int off = 0;
  for (i = 0; i < bitlen; ++i) {
    if (x & (p >> i) != 0)
      break;
  }
  off = bitlen - 1 - i - 8;
  if (off <= 0)
    return x & mask;
  else
    return x & (mask << off);
}

unsigned char
lowByte(unsigned long long x)
{
  unsigned char mask = -1;
  return x & mask;
}

void
attachInterrupt(int _intpin, void (*handle)(), PinStat mode)
{
  switch (static_cast<PinName>(_intpin)) {
    case PUSH1:
      push1_handle = handle;
      break;
    case PUSH2:
      push2_handle = handle;
      break;
  }
}

void
detachInterrupt(int _intpin)
{
  switch (static_cast<PinName>(_intpin)) {
    case PUSH1:
      push1_handle = NULL;
      break;
    case PUSH2:
      push2_handle = NULL;
      break;
  }
}