#pragma once
#include "crow.h"

class UserHandlers {
public:
    static crow::response handleGetProfile(const crow::request& req);
}; 