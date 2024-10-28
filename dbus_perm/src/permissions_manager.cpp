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

  dbusObject->finishRegistration();
}

void PermissionManager::start() { connection->enterEventLoop(); }

void PermissionManager::RequestPermission(int permissionEnumCode) {
  std::string path = getPath(dbusObject, connection);
  std::cout << "Path " << path << std::endl;
  
  int dbRes = writeRecordToDB(permissionEnumCode, path);
}
