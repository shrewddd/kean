#include <Carbon/Carbon.h> 
#include <ApplicationServices/ApplicationServices.h>
#include <cstddef>
#include <iostream>
#include <ostream>

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
  if(type != kCGEventKeyDown && type != kCGEventFlagsChanged) {
    return event;
  }

  CGEventFlags flags = CGEventGetFlags(event);
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

  std::cout << keyCode << std::endl;
  return event;
};


int main() {

  CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged);

  CFMachPortRef eventTap = CGEventTapCreate(
    kCGSessionEventTap, 
    kCGHeadInsertEventTap, 
    kCGEventTapOptionDefault,
    eventMask, 
    CGEventCallback, 
    NULL
  );

  if(!eventTap) {
    std::cout << "ERROR: Unable to initialize event tap handler" << std::endl;
    return -1;
  }

  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  CFRunLoopRun();

  return 0;
}
