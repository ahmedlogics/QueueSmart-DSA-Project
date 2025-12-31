#include "Handlers/QueueHandlers.hpp"
#include "Handlers/AuthHandlers.hpp"
#include "Services/QueueManager.hpp"

using namespace std;

crow::response QueueHandlers::handleBookToken(const crow::request& req) {
    auto userId = AuthHandlers::getAuthenticatedUserId(req);
    if (!userId) return crow::response(401);

    auto body = crow::json::load(req.body);
    if (!body) return crow::response(400);

    // Create token
    Token t = QueueManager::getInstance().createToken(
        *userId,
        body["branch"].s(),
        body["category"].s(),
        body["date"].s()
    );

    QueueManager::getInstance().enqueueToken(t);

    crow::json::wvalue res;
    res["token"] = t.toJson();
    return crow::response(200, res);
}

crow::response QueueHandlers::handleGetQueueStatus(const crow::request& req, string branch) {
    // Get the list
    vector<Token> list = QueueManager::getInstance().getQueueList(branch);

    crow::json::wvalue::list jsonList;
    for (const auto& t : list) {
        jsonList.push_back(t.toJson());
    }

    return crow::response(200, crow::json::wvalue(jsonList));
}

crow::response QueueHandlers::handleServeNextToken(const crow::request& req, string branch) {
    try {
        Token t = QueueManager::getInstance().serveNext(branch);
        return crow::response(200, t.toJson());
    } catch (...) {
        return crow::response(400, "Queue Empty");
    }
}

crow::response QueueHandlers::handleUndoToken(const crow::request& req, string branch) {
    try {
        Token t = QueueManager::getInstance().undoServe(branch);
        return crow::response(200, t.toJson());
    } catch (...) {
        return crow::response(400, "Nothing to Undo");
    }
}