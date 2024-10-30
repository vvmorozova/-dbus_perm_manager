#include "main_app.h"

int main() {
  // get sys time
  auto connection = sdbus::createSessionBusConnection();
  sdbus::ObjectPath objectPath{"/"};
  auto timeProxy =
      sdbus::createProxy(*connection, "com.system.time", std::move(objectPath));
  std::cout << "0" << std::endl;
  uint64_t result = 0;
  timeProxy->callMethod("GetSystemTime")
      .onInterface("com.system.time")
      .withArguments()
      .storeResultsTo(result);

  std::cout << "1" << std::endl;
  // if no rights, ask for perm
  if (result == 0) {
    auto permProxy =
        sdbus::createProxy("com.system.permissions", std::move(objectPath));

    result = 0;
    permProxy->callMethod("RequestPermission")
        .onInterface("com.system.permissions")
        .withArguments(PermissionManager::Permissions::SystemTime)
        .storeResultsTo(result);
  }
  std::cout << "2" << std::endl;
  // get sys time again

  result = 0;
  timeProxy->callMethod("GetSystemTime")
      .onInterface("com.system.time")
      .storeResultsTo(result);

  std::cout << "main curr time " << result << std::endl;
}