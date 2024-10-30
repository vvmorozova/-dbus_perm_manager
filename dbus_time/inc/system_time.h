#pragma once
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdbool.h>
#include <sdbus-c++/sdbus-c++.h>

#include "utils.h"
#include "permissions_manager.h"

class SystemTime {
public:
  SystemTime();
  void start();

private:
  uint64_t GetSystemTime();
  std::unique_ptr<sdbus::IObject> dbusObject;
  std::unique_ptr<sdbus::IConnection> connection;
};