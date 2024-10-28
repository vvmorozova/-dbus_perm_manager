
#include <algorithm>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <sqlite3.h>
#include <fstream>
// void RequestPermission(permissionEnumCode : int);
// bool CheckApplicationHasPermission(applicationExecPath: String,
// permissionEnumCode: int);

// uint32_t getPid(const std::string &dbus_id) {
//   const char *serviceName = "org.freedesktop.DBus";
//   sdbus::ObjectPath objectPath{"/org/freedesktop/DBus"};
//   auto connection = sdbus::createProxy(serviceName, objectPath);

//   uint32_t pid;

//   connection->callMethod("GetConnectionUnixProcessID")
//       .onInterface("org.freedesktop.DBus")
//       .withArguments(dbus_id)
//       .storeResultsTo(pid);
//   return pid;
// }

class PermissionManager {

public:
  PermissionManager() {
    const char *serviceName = "com.system.permissions";
    connection = sdbus::createSessionBusConnection(serviceName);

    sdbus::ObjectPath objectPath{"/"};
    dbusObject = sdbus::createObject(*connection, std::move(objectPath));

    dbusObject->registerMethod("RequestPermission")
        .onInterface("com.system.permissions")
        .withInputParamNames("permissionEnumCode")
        .implementedAs(
            std::move([this](int type) { RequestPermission(type); }));

    dbusObject->finishRegistration();
  }

  void start() { connection->enterEventLoop(); }

private:
  void RequestPermission(int permissionEnumCode) {
    std::cout << "in requested permision" << std::endl;

    auto senderDBusName =
        dbusObject->getCurrentlyProcessedMessage()->getSender();

    auto dbus_pid = 0;
    char pidPath[254];
    std::cout << "dbus pid " << getPid(senderDBusName) << std::endl;

    sprintf(pidPath, "/proc/%d/cmdline", getPid(senderDBusName));

    if (access(pidPath, F_OK) == -1) {
      throw std::runtime_error("No process with this pid");
    }

    std::ifstream infile(pidPath);
    std::string path;
    infile >> path;
    std::cout << "Path " << path << std::endl;

  }

  uint32_t getPid(const std::string &dbus_id) {
    const char *serviceName = "org.freedesktop.DBus";
    sdbus::ObjectPath objectPath{"/org/freedesktop/DBus"};
    auto conn = sdbus::createProxy(*connection, serviceName, objectPath);
    

    uint32_t pid;

    conn->callMethod("GetConnectionUnixProcessID")
        .onInterface("org.freedesktop.DBus")
        .withArguments(dbus_id)
        .storeResultsTo(pid);
    return pid;
  }

  std::unique_ptr<sdbus::IObject> dbusObject;
  std::unique_ptr<sdbus::IConnection> connection;
};

int main(int argc, char *argv[]) {
  PermissionManager permManager;
  permManager.start();
}
