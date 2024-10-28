#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

uint32_t getPid(const std::string &senderName,
                std::unique_ptr<sdbus::IConnection> &connection);
std::string getPath(std::unique_ptr<sdbus::IObject> &dbusObject,
                    std::unique_ptr<sdbus::IConnection> &connection);