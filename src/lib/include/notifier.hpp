#ifndef notifier_hpp
#define notifier_hpp

#include <functional>

/** Interface describing a service that calls back when event occurs. */
class Notifier {
public:
	virtual ~Notifier() = default;
	
	/** Specifies the method to call back. */
	virtual void setNotificationCallback(std::function<void ()> n) = 0;
};

#endif
