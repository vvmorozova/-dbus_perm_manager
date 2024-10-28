#pragma once

#include <algorithm>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

uint32_t getPid(const std::string &senderName,
                std::unique_ptr<sdbus::IConnection> &connection);