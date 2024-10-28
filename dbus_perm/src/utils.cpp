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