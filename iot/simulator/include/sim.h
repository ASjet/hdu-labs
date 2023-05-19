#ifndef SIM_H
#define SIM_H

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using byte = unsigned char;

// pin
enum PinName
{
  RED_LED = 0,
  GREEN_LED,
  YELLOW_LED,
  PUSH1,
  PUSH2,
};

enum PinDir
{
  INVALID = 0,
  INPUT,
  OUTPUT,
  INPUT_PULLUP,
};

enum PinStat
{
  UNKNOWN = 0,
  LOW,
  HIGH,
  RISING,
  CHANGE,
};

// Digital I/O
PinStat
digitalRead(int _inPin);

void
digitalWrite(int _ledPin, PinStat _ledStat);

void
pinMode(int _pin, PinDir _mode);

// Time
void
delay(unsigned int _ms);

void
delayMicroseconds(unsigned int _us);

unsigned long
micros(void);

unsigned long
millis(void);

// Characters
int
isAscii(int ch);

inline bool
isAplha(int ch)
{
  return std::isalpha(static_cast<unsigned char>(ch));
}

inline bool
isAlphaNumeric(int ch)
{
  return std::isalnum(static_cast<unsigned char>(ch));
}

inline bool
isControl(char ch)
{
  return std::iscntrl(static_cast<unsigned char>(ch));
}

inline bool
isDigit(char ch)
{
  return std::isdigit(static_cast<unsigned char>(ch));
}

inline bool
isGraph(char ch)
{
  return std::isgraph(static_cast<unsigned char>(ch));
}

inline bool
isHexadecimalDigit(char ch)
{
  return std::isxdigit(static_cast<unsigned char>(ch));
}

inline bool
isLowerCase(char ch)
{
  return std::islower(static_cast<unsigned char>(ch));
}

inline bool
isPrintable(char ch)
{
  return std::isprint(static_cast<unsigned char>(ch));
}

inline bool
isPunct(char ch)
{
  return std::ispunct(static_cast<unsigned char>(ch));
}

inline bool
isSpace(char ch)
{
  return std::isspace(static_cast<unsigned char>(ch));
}

inline bool
isUpperCase(char ch)
{
  return std::isupper(static_cast<unsigned char>(ch));
}

inline bool
isWhitespace(char ch)
{
  return std::isblank(static_cast<unsigned char>(ch));
}

// Random
void
randomSeed(long seed);

// Bit and Byte
unsigned long long
bit(int n);

void
bitClear(unsigned long long* x, int n);

int
bitRead(unsigned long long x, int n);

void
bitSet(unsigned long long* x, int n);

void
bitWrite(unsigned long long* x, int n, int b);

unsigned char
highByte(unsigned long long x);

unsigned char
lowByte(unsigned long long x);

// Interrupt
void
attachInterrupt(int _pin, void (*ISR)(), PinStat mode);

void
detachInterrupt(int _pin);

#endif