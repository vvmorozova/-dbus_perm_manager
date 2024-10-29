#include "system_time.h"

SystemTime::SystemTime() {
  const char *serviceName = "com.system.time";
  connection = sdbus::createSessionBusConnection(serviceName);

  sdbus::ObjectPath objectPath{"/"};
  dbusObject = sdbus::createObject(*connection, std::move(objectPath));

  dbusObject->registerMethod("GetSystemTime")
      .onInterface("com.system.time")
      .withInputParamNames()
      .implementedAs(std::move([this]() { GetSystemTime(); }));

  dbusObject->finishRegistration();
}

void SystemTime::start() { connection->enterEventLoop(); }

uint64_t SystemTime::GetSystemTime() {

  std::string path = getPath(dbusObject, connection);
  std::cout << "Path " << path << std::endl;

  // ask permission

  // get sys time
  auto currTime =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::cout << "curr time " << std::ctime(&currTime) << std::endl;
  return currTime;
}