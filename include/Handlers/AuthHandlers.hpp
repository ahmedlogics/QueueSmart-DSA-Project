#pragma once
#include "crow.h"
#include <optional>

class AuthHandlers {
public:
    static crow::response handleRegister(const crow::request& req);
    static crow::response handleLogin(const crow::request& req);
    
    // This must be static to be used by other handlers
    static std::optional<int> getAuthenticatedUserId(const crow::request& req);
}; 