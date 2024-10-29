#include "utils.h"
uint32_t getPid(const std::string &senderName,
                std::unique_ptr<sdbus::IConnection> &connection) {
  const char *serviceName = "org.freedesktop.DBus";
  sdbus::ObjectPath objectPath{"/org/freedesktop/DBus"};
  auto conn = sdbus::createProxy(*connection, serviceName, objectPath);

  uint32_t pid;

  conn->callMethod("GetConnectionUnixProcessID")
      .onInterface("org.freedesktop.DBus")
      .withArguments(senderName)
      .storeResultsTo(pid);
  return pid;
}

std::string getPath(std::unique_ptr<sdbus::IObject> &dbusObject,
                    std::unique_ptr<sdbus::IConnection> &connection) {
  auto senderDBusName = dbusObject->getCurrentlyProcessedMessage()->getSender();

  char pidPath[254];

  sprintf(pidPath, "/proc/%d/cmdline", getPid(senderDBusName, connection));

  if (access(pidPath, F_OK) == -1) {
    std::string connectionName;
    connection->requestName(connectionName);
    throw sdbus::Error(connectionName, "No process with this pid");
  }

  std::ifstream infile(pidPath);
  std::string path;
  infile >> path;

  return path;
}