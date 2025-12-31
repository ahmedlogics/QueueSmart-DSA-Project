#include "Handlers/UserHandlers.hpp"
#include "Handlers/AuthHandlers.hpp"
#include "Services/AuthService.hpp"

using namespace std;

crow::response UserHandlers::handleGetProfile(const crow::request& req) {
 
    auto userId = AuthHandlers::getAuthenticatedUserId(req);
    
    if (!userId) return crow::response(401);

    auto user = AuthService::getInstance().getUserById(*userId);
    if (user) {
        return crow::response(200, user->toJson());
    }
    
    return crow::response(404);
}