#include "crow.h"
#include "crow/middlewares/cors.h"
#include "Handlers/AuthHandlers.hpp"
#include "Handlers/QueueHandlers.hpp"
#include "Handlers/UserHandlers.hpp"
#include <iostream>

using namespace std;

int main() {
    // App with CORS
    crow::App<crow::CORSHandler> app;

    // Configure CORS
    auto& cors = app.get_middleware<crow::CORSHandler>();
    

    cors.global()
        .origin("*")  
        .methods("POST"_method, "GET"_method, "OPTIONS"_method) 
        .headers("Content-Type", "Authorization"); 

 
    // Auth
    CROW_ROUTE(app, "/api/register").methods("POST"_method)(AuthHandlers::handleRegister);
    CROW_ROUTE(app, "/api/login").methods("POST"_method)(AuthHandlers::handleLogin);
    CROW_ROUTE(app, "/api/profile").methods("GET"_method)(UserHandlers::handleGetProfile);

    // Queue Logic
    CROW_ROUTE(app, "/api/book").methods("POST"_method)(QueueHandlers::handleBookToken);
    CROW_ROUTE(app, "/api/queue/<string>").methods("GET"_method)(QueueHandlers::handleGetQueueStatus);

    // Admin Logic
    CROW_ROUTE(app, "/api/admin/serve/<string>").methods("POST"_method)(QueueHandlers::handleServeNextToken);
    CROW_ROUTE(app, "/api/admin/undo/<string>").methods("POST"_method)(QueueHandlers::handleUndoToken);

    // Start
    cout << "\n--- QueueSmart Backend Starting on Port 18080 ---" << endl;
    app.port(18080).multithreaded().run();

    return 0;
}