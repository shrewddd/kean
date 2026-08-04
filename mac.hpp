#include <Carbon/Carbon.h> 
#include <ApplicationServices/ApplicationServices.h>

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

void initialize_listener();
