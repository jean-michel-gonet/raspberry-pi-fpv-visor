#include "event-bus-service.hpp"
#include "catch.hpp"


/** Any class can be used as an event. */
class AnyEvent {
public:
	AnyEvent(int id) {
		identity = id;
	}
	int getIdentity() {
		return identity;
	}
private:
	int identity;
};

/** Any class can be a subscriber, as long as it
  * has a function to receive the event. */
class AnySubscriber {
public:
	AnySubscriber(int id) {
		identityOfLastReceivedEvent = id;
	};
	int getIdentityOfLastReceivedEvent() {
		return identityOfLastReceivedEvent;
	}
	void setIdentityOfLastReceivedEvent(int id) {
		identityOfLastReceivedEvent = id;
	}
	void receiveNotification(AnyEvent event) {
		identityOfLastReceivedEvent = event.getIdentity();
	}
private:
	int identityOfLastReceivedEvent;
};

using namespace std::placeholders;
using namespace std;

SCENARIO("A bus service can broadcast any event to all subscribers") {
	EventBusService<AnyEvent> eventBus;

	GIVEN( "Two classes subscribed to the same event") {
		AnySubscriber subscriber1(10), subscriber2(20);
		function<void (AnyEvent)> s1 = bind(&AnySubscriber::receiveNotification, subscriber1, _1);
		eventBus.subscribe(s1);
		eventBus.subscribe(bind(&AnySubscriber::receiveNotification, subscriber2, _1));
		subscriber1.setIdentityOfLastReceivedEvent(30);
		subscriber2.setIdentityOfLastReceivedEvent(40);
		WHEN( "When the event is fired") {
			eventBus.propagate(AnyEvent(1));
			THEN ( "All subscriptors are informed ") {
				REQUIRE( subscriber1.getIdentityOfLastReceivedEvent() == 1);
			}
		}		
	}
}
