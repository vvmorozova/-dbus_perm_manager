#include "main_app.h"

int main() {
  // get sys time
  auto connection = sdbus::createSessionBusConnection();
  sdbus::ObjectPath objectPath{"/"};
  auto timeProxy =
      sdbus::createProxy(*connection, "com.system.time", std::move(objectPath));
  uint64_t result = 0;
  try {
    timeProxy->callMethod("GetSystemTime")
        .onInterface("com.system.time")
        .withArguments()
        .storeResultsTo(result);
  } catch (sdbus::Error &e) {
    std::cout << "Permissions not granted, trying to receive them" << std::endl;
  }

  // if no rights, ask for perm
  if (result == 0) {
    auto permProxy =
        sdbus::createProxy(*connection, "com.system.permissions", "/");

    permProxy->callMethod("RequestPermission")
        .onInterface("com.system.permissions")
        .withArguments(PermissionManager::Permissions::SystemTime);
  }
 std::cout << "Permissions are granted" << std::endl;
  // get sys time again

  result = 0;
  timeProxy->callMethod("GetSystemTime")
      .onInterface("com.system.time")
      .storeResultsTo(result);

  std::chrono::system_clock::time_point tp =
      std::chrono::system_clock::time_point(std::chrono::seconds(result));

  std::time_t time = std::chrono::system_clock::to_time_t(tp);

  std::cout << "Date: "
            << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
            << std::endl;
}