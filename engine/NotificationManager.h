//
// Created by csobe on 2026-10-13.
//

#ifndef PROJECT1_NOTIFICATIONMANAGER_H
#define PROJECT1_NOTIFICATIONMANAGER_H
#include <memory>
#include <unordered_map>
#include <vector>

namespace CMPUT350 {
class GameObject;

class NotificationManager {
public:
    void Register(std::weak_ptr<GameObject> object, const std::string& key);
    void Unregister(std::weak_ptr<GameObject> object, const std::string& key);
    void Notify(const std::string& message);
private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<GameObject>>> mListeners;
};
}

#endif  // PROJECT1_NOTIFICATIONMANAGER_H
