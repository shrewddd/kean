#include "mac.hpp"
#include "core_collector.hpp"
#include "keyboard_event.hpp"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <iostream>

namespace {
CGEventRef CGEventCallback(CGEventTapProxy proxy, 
                           CGEventType type, 
                           CGEventRef event, 
                           void *refcon) {
  auto *collector = static_cast<CoreCollector *>(refcon);

  if (type != kCGEventKeyDown && type != kCGEventFlagsChanged) {
    return event;
  }

  CGEventFlags flags = CGEventGetFlags(event);
  CGKeyCode keyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

  std::cout << keyCode << std::endl;

  KeyboardEvent ke = {keyCode, flags};

  collector->push(ke);
  return event;
};
} 

void MacEventSource::run(CoreCollector &collector) {
  CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged);

  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,eventMask, CGEventCallback, &collector);

  if (!eventTap) {
    std::cout << "ERROR: Unable to initialize event tap handler" << std::endl;
    return;
  }

  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  CFRunLoopRun();
}
