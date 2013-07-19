#include "Timing.hpp"

#include <cstddef>
#include <sys/time.h>

scottgs::Timing::Timing() {
  init();
}

void scottgs::Timing::init() {
  _isRunning = false;
  _startingTime = 0;
  _elapsedTime = 0;
}

void scottgs::Timing::start() {
  if(false == _isRunning) {
    _isRunning = true;
    _startingTime = getCurrentTime();
  }
}

void scottgs::Timing::split() {
  stop();
  start();
}

void scottgs::Timing::stop() {
  if(true == _isRunning) { 
    _elapsedTime += getSplitElapsedTime();
    _isRunning = false;
  }
}

void scottgs::Timing::reset() {
  init();
}

double scottgs::Timing::getTotalElapsedTime() const {
  if(false == _isRunning)
    return _elapsedTime;
  else
    return _elapsedTime + getSplitElapsedTime(); 
}

double scottgs::Timing::getSplitElapsedTime() const {
  return getCurrentTime() - _startingTime;
}

double scottgs::Timing::getCurrentTime() const {
  struct timeval tp;
  int rtn;
  rtn=gettimeofday(&tp, NULL);
  return (double)tp.tv_sec+(1.e-6)*tp.tv_usec;
}
