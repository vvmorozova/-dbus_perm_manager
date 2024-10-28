#pragma once

#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

#include "sql.h"
#include "utils.h"

class PermissionManager {
public:
  PermissionManager();

  void start();

private:
  void RequestPermission(int permissionEnumCode);

  std::unique_ptr<sdbus::IObject> dbusObject;
  std::unique_ptr<sdbus::IConnection> connection;
};