
#include <sdbus-c++/sdbus-c++.h>
#include <sqlite3.h>
#include <iostream>
// void RequestPermission(permissionEnumCode : int);
// bool CheckApplicationHasPermission(applicationExecPath: String, permissionEnumCode: int);

sdbus::IObject* g_permissionManager{};

void RequestPermission(int permissionEnumCode)
{
    // Return error if there are no numbers in the collection
    std::cout << "in rewuested permision" << std::endl;
    // Emit 'concatenated' signal
    std::string result = "AAAA";
    const char* interfaceName = "com.system.permissions.permissionManager";
    g_permissionManager->emitSignal("concatenated").onInterface(interfaceName).withArguments(result);
    
}

int main(int argc, char *argv[])
{
    const char* serviceName = "com.system.permissions";
    auto connection = sdbus::createSystemBusConnection(serviceName);


    // Register D-Bus property on the object, and export the object.
    sdbus::ObjectPath objectPath{"/com/system/permissions"};
    // auto dbusProxy = sdbus::createProxy(*connection, "org.freedesktop.DBus", "/org/freedesktop/DBus");
    auto dbusProxy = sdbus::createProxy(serviceName, std::move(objectPath));

    const char* interfaceName = "com.system.permissions";
    pid_t pid;
    dbusProxy->callMethod("RequestPermission")
        .onInterface(interfaceName)
        .withArguments(serviceName)
        .storeResultsTo(pid);

    std::cout << "in dbus main" << std::endl;
    connection->enterEventLoop();

}
