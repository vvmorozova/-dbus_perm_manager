#pragma once

#include <iostream>
#include <stdbool.h>
#include <sdbus-c++/sdbus-c++.h>

#include "sql.h"
#include "utils.h"

class PermissionManager {
public:
  PermissionManager();
  void start();

  enum Permissions { SystemTime = 0 };

private:
  void RequestPermission(int permissionEnumCode);
  bool CheckApplicationHasPermission(std::string applicationExecPath,
                                     int permissionEnumCode);

  std::unique_ptr<sdbus::IObject> dbusObject;
  std::unique_ptr<sdbus::IConnection> connection;

};