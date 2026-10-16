//
// Created by csobe on 2026-10-13.
//

#include "NotificationManager.h"
#include "GameObject.h"
namespace CMPUT350 {
void NotificationManager::Register(std::weak_ptr<GameObject> object, const std::string& key) {
    mListeners[key].push_back(object);
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object, const std::string& key) {
    if (auto it = mListeners.find(key); it != mListeners.end()) {
        for (auto i = it->second.begin(); i != it->second.end(); ) {
            //CITE: https://stackoverflow.com/questions/21834131/stdshared-ptrowner-before-and-stdowner-less-what-exactly-is-meant-by-own
            //Accessed at 6:03pm, 2026-10-13, Mike Seymores answer
            if (!i->owner_before(object) && !object.owner_before(*i)) {
                i = it->second.erase(i);
                continue;
            }
            ++i;
        }


    }
}

void NotificationManager::Notify(const std::string& message) {
    /*
     *In the initial engine, all key notifications were passed to all objects, which is inefficient.
     *We will now update the engine to allow key events to be registered with the engine.
     *When a particular key scancode is pressed down or released, if that key has been registered to
     *the engine, then the engine will send an event to the notification manager with the string that
     *was passed in. So, both Key::A and Key::Left (etc) can be registered to the “MoveLeft” notification,
     *and the game will respond identically whether the player uses arrow keys or WASD.
    */
    //Sooooo I feel like we check if the message matches a "notification" like MoveLeft, and then we notify
    //The appropriate object

    /*
     *Current List:
     *  left
     *  right
     *  shoot
     *  enemy_shoot
     *  stop
     *
     *Potential:
     *  enter left: For enemies entering
     *  enter right: For enemies entering
     *  fly down: Might have multiple depending on enemy type if we need to
     *  points: For scoring points, may need multiple values. i.e. points 200, points 550
     */

    // Get iterator to objects listening for the message
    auto targets = mListeners[message];

    // Send event to each object
    for( auto it = targets.begin(); it != targets.end(); it++ ) {
        if( auto obj = it->lock() ) { // get object from the weak_ptr
            obj->ReceiveNotification(message);
        }
    }
    
}
}