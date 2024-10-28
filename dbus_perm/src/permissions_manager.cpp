#include "permissions_manager.h"

PermissionManager::PermissionManager() {
  const char *serviceName = "com.system.permissions";
  connection = sdbus::createSessionBusConnection(serviceName);

  sdbus::ObjectPath objectPath{"/"};
  dbusObject = sdbus::createObject(*connection, std::move(objectPath));

  dbusObject->registerMethod("RequestPermission")
      .onInterface("com.system.permissions")
      .withInputParamNames("permissionEnumCode")
      .implementedAs(std::move([this](int type) { RequestPermission(type); }));

  dbusObject->registerMethod("CheckApplicationHasPermission")
      .onInterface("com.system.permissions")
      .withInputParamNames("applicationExecPath", "permissionEnumCode")
      .implementedAs(std::move([this](std::string path, int type) {
        CheckApplicationHasPermission(path, type);
      }));

  dbusObject->finishRegistration();
}

void PermissionManager::start() { connection->enterEventLoop(); }

void PermissionManager::RequestPermission(int permissionEnumCode) {
  std::string path = getPath(dbusObject, connection);
  std::cout << "Path " << path << std::endl;

  int dbRes = writeRecordToDB(permissionEnumCode, path);
}

bool PermissionManager::CheckApplicationHasPermission(
    std::string applicationExecPath, int permissionEnumCode) {
  sqlite3 *db;

  std::cout << "in check app perm" << std::endl;

  int rc = sqlite3_open("permissions.db", &db);
  if (rc != SQLITE_OK) {
    char errMsg[255];
    std::string connectionName;

    sprintf(errMsg, "Failed to open DB: %s\n", sqlite3_errmsg(db));
    connection->requestName(connectionName);
    throw sdbus::Error(connectionName, errMsg);
    return false;
  }

  const char *checkSQL =
      "SELECT 1 FROM permissions WHERE path = ? AND permission = ? LIMIT 1;";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(db, checkSQL, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    char errMsg[255];
    std::string connectionName;

    sprintf(errMsg, "Failed to prepare record: %s\n", sqlite3_errmsg(db));
    connection->requestName(connectionName);
    throw sdbus::Error(connectionName, errMsg);

    return false;
  }

  sqlite3_bind_text(stmt, 1, applicationExecPath.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, permissionEnumCode);

  rc = sqlite3_step(stmt);
  // If a row is returned, the record exists
  std::cout << "path " << applicationExecPath << " code " << permissionEnumCode
            << " rc " << rc << std::endl;
  bool exists = (rc == SQLITE_ROW);

  sqlite3_finalize(stmt);
  if (!exists)
  {
    char errMsg[255];
    std::string connectionName;
    connection->requestName(connectionName);
    throw sdbus::Error(connectionName, "Unathorized access");
  }
  return exists;
}