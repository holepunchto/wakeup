#import <AppKit/AppKit.h>

#import "../../include/wakeup.h"

#import "AppDelegate.h"

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
  [[NSAppleEventManager sharedAppleEventManager]
    setEventHandler:self
        andSelector:@selector(handleURLEvent:withReplyEvent:)
      forEventClass:kInternetEventClass
         andEventID:kAEGetURL];
}

- (void)handleURLEvent:(NSAppleEventDescriptor *)event
        withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
  wakeup([[[event paramDescriptorForKeyword:keyDirectObject] stringValue] UTF8String]);
}

@end
