#include <Carbon/Carbon.h> 
#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
  if(type != kCGEventKeyDown && type != kCGEventFlagsChanged) {
    return event;
  }

  CGEventFlags flags = CGEventGetFlags(event);
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

  std::cout << keyCode << std::endl;
  return event;
};

void initialize_listener() {
  CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged);

  CFMachPortRef eventTap = CGEventTapCreate(
    kCGSessionEventTap, 
    kCGHeadInsertEventTap, 
    kCGEventTapOptionDefault,
    eventMask, 
    CGEventCallback, 
    nullptr  
  );

  if(!eventTap) {
    std::cout << "ERROR: Unable to initialize event tap handler" << std::endl;
    return;
  }

  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  CFRunLoopRun();
}
