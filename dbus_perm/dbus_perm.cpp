
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
    const char *serviceName = "com.system.permissions";
    // auto connection = sdbus::createSessionBusConnection(serviceName);
    auto connection = sdbus::createSessionBusConnection();

    sdbus::ServiceName destination{"com.system.permissions"};
    sdbus::ObjectPath objectPath{"/com/system/permissions"};
    // auto dbusProxy = sdbus::createProxy(*connection, "org.freedesktop.DBus", "/org/freedesktop/DBus");
    auto dbusProxy = sdbus::createProxy(std::move(destination), std::move(objectPath));

    pid_t pid;
    dbusProxy->callMethod("GetConnectionUnixProcessID")
        .onInterface("org.freedesktop.DBus")
        .withArguments(serviceName)
        .storeResultsTo(pid);

    // g_permissionManager = permissionManager.get();

    const char *interfaceName = "com.system.permissions.permissionManager";
    // permissionManager->registerMethod("RequestPermission").onInterface(interfaceName).implementedAs(&RequestPermission);
    // permissionManager->registerSignal("RequestedPermission").onInterface(interfaceName).withParameters(0);
    // permissionManager->finishRegistration();

    connection->enterEventLoop();
}
