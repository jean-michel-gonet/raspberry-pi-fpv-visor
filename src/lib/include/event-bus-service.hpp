#ifndef event_bus_service_hpp
#define event_bus_service_hpp

#include <functional>
#include <vector>

using namespace std;

/**
 * A class to receive events and redistribute them to
 * all subscribers.
 * This piece of code involves all kind of difficult stuff I had to learn:
 * - About using pointers to functions:
 *   - http://en.cppreference.com/w/cpp/utility/functional/bind
 * - Using static variables in template classes:
 *   - https://www.fayewilliams.com/2014/12/23/static-variables-in-template-classes-and-methods/
 * - Why do we need to have a header-only class:
 *   - https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c
 * - Use erase-remove idiom to remove elements by value from a vector:
     - https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
 * - why can't we use erase-remove idiom: 
 *   - https://stackoverflow.com/questions/41677041/c-vectorerase-complains-about-overload-resolution-deleted-operator
 *   - https://stackoverflow.com/questions/3629835/why-is-stdfunction-not-equality-comparable
 * - How to deal with static members in header-only classes:
 *   - https://stackoverflow.com/questions/11709859/how-to-have-static-data-members-in-a-header-only-library
 * - std::vector::push_back makes copies of objects, so you can't just
 *   store your subscriptors in it: you need to store pointers to your
 *   subscriptors:
 *   - https://stackoverflow.com/questions/2275076/is-stdvector-copying-the-objects-with-a-push-back
 */

/** @brief A wrapper around a function pointer
 * The wrapper serves two purposes:
 * - It can be duplicated (as std::vector::push_back will do) without
 *   changing the pointed function.
 * - It implements the == operator, needed to perform the
 *   remove-erase idiom.
 */
template <class T>
class SubscriptorHolder {
public:
	/** @brief Class constructor.
	 * @param s A pointer to a function.
	 */
	SubscriptorHolder(function<void (T)> s) {
		subscriptor = &s;
	}
	/** @brief Calls the subscriptor providing the event.
	 * @param event The event.
	 */
	void callSubscriptor(T event) {
		subscriptor[0](event);
	}
private:
	function<void (T)> *subscriptor;
};

/** @brief A static vector of SubscriptorHolder.
 * This is a work around to use a static variables in header-only
 * classes.
 */
template <class T>
struct SubscriptorsHolder {
	static vector<SubscriptorHolder<T>> subscriptors;
};

/** @brief Declare the static variable, so it can be linked.
 */
template <class T>
vector<SubscriptorHolder<T>> SubscriptorsHolder<T>::subscriptors;

/** @brief Propagates event to all subscriptors.
 */
template <class T>
class EventBusService {
public:
	EventBusService() {
		vector<SubscriptorHolder<T>> subscriptors = SubscriptorsHolder<T>::subscriptors;
	};
	virtual ~EventBusService() = default;
	virtual void propagate(T event) {
		for (int i = 0; i < subscriptors.size(); i++) {
			SubscriptorHolder<T> subscriptorHolder = subscriptors[i];
			subscriptorHolder.callSubscriptor(event);
		}
	};

	virtual void subscribe(function<void (T)> subscriptor) {
		SubscriptorHolder<T> subscriptorHolder(subscriptor);
		subscriptors.push_back(subscriptorHolder);
	};

	virtual void unsubscribe(function<void (T)> subscriptor) {
		// The erase-remove idiom does not work because
		// std::function explicitly removes the == operator.
		//subscriptors.erase(remove(subscriptors.begin(), subscriptors.end(), subscriptor), subscriptors.end());
	}
private:
	vector<SubscriptorHolder<T>> subscriptors;
};

#endif
