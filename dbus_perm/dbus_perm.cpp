
#include <sdbus-c++/sdbus-c++.h>
#include <sqlite3.h>
#include <iostream>
// void RequestPermission(permissionEnumCode : int);
// bool CheckApplicationHasPermission(applicationExecPath: String, permissionEnumCode: int);



void RequestPermission(int permissionEnumCode)
{
    // Return error if there are no numbers in the collection
    std::cout << "in rewuested permision" << std::endl;
    // Emit 'concatenated' signal
    std::string result = "AAAA";
    
}

int main(int argc, char *argv[])
{
    const char* serviceName = "com.system.permissions";
    auto connection = sdbus::createSessionBusConnection(serviceName);

  // Создаем DBus объект
  sdbus::ObjectPath objectPath{"/"};
  auto object = sdbus::createObject(*connection, std::move(objectPath));
// auto object = sdbus::createObject(*connection, "/");

    object->registerMethod("RequestPermission").onInterface("com.system.permissions").withInputParamNames("permissionEnumCode").implementedAs(RequestPermission);
    object->finishRegistration();
    std::cout << "init object " << object->getObjectPath() << std::endl;
    connection->enterEventLoop();

}
