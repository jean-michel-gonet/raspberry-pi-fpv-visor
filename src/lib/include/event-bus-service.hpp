#ifndef event_bus_service_hpp
#define event_bus_service_hpp

#include <vector>

using namespace std;

/**
 * A class to receive events and redistribute them to
 * all subscribers.
 * This piece of code involves all kind of difficult stuff I had to learn:
 * - Using static variables in template classes:
 *   - https://www.fayewilliams.com/2014/12/23/static-variables-in-template-classes-and-methods/
 * - Why do we need to have a header-only class:
 *   - https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
 * - Use erase-remove idiom to remove elements by value from a vector:
     - https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
 * - How to deal with static members in header-only classes:
 *   - https://stackoverflow.com/questions/11709859/how-to-have-static-data-members-in-a-header-only-library
 */

/** @brief Describes the interface that a subscriber must implement.
 * The subscriber has to implement the ability to receive events.
 */
template <class T>
class Subscriptor {
public:
	/** @brief Calls the subscriptor providing the event.
	 * @param event The event.
	 */
	virtual void receive(T event) = 0;
};

/** @brief A static vector of Subscriptor.
 * This is a work around to use a static variables in header-only
 * classes.
 */
template <class T>
struct SubscriptorsHolder {
	static vector<Subscriptor<T> *> subscriptors;
};

/** @brief Declare the static variable, so it can be linked.
 */
template <class T>
vector<Subscriptor<T> *> SubscriptorsHolder<T>::subscriptors;

/** @brief Propagates the events to all subscriptors in the list.
 */
template <class T>
class EventBusService {
public:
	EventBusService() {
		vector<Subscriptor<T> *> subscriptors = SubscriptorsHolder<T>::subscriptors;
	};
	virtual ~EventBusService() = default;
	
	/** @brief Propagates the event to all subscriptors.
	 * @param event The event.
	 */
	virtual void propagate(T event) {
		for (int i = 0; i < subscriptors.size(); i++) {
			Subscriptor<T> *subscriptor = subscriptors[i];
			subscriptor->receive(event);
		}
	};

	/** @brief Any class able to receive the event can subscribe.
	 * @param subscriptor A pointer to an instance able to receive events.
	 */
	virtual void subscribe(Subscriptor<T> *subscriptor) {
		subscriptors.push_back(subscriptor);
	};

	/** @brief Unsubscribes the specified subscriptor.
	 * @param subscriptor A pointer to the subscriptor.
	 */
	virtual void unsubscribe(Subscriptor<T> *subscriptor) {
		subscriptors.erase(remove(subscriptors.begin(), subscriptors.end(), subscriptor), subscriptors.end());
	}
private:
	vector<Subscriptor<T> *> subscriptors;
};

#endif
