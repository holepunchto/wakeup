#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#import "../../include/wakeup.h"

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize timer;

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
  [[NSAppleEventManager sharedAppleEventManager]
    setEventHandler:self
        andSelector:@selector(handleURLEvent:withReplyEvent:)
      forEventClass:kInternetEventClass
         andEventID:kAEGetURL];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  [self resetTimer];
}

- (void)handleURLEvent:(NSAppleEventDescriptor *)event
        withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
  NSString *url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];

  wakeup([url UTF8String], (void *) CFBridgingRetain(event));

  [self resetTimer];
}

- (void)resetTimer {
  if (timer) [timer invalidate];

  timer = [NSTimer
    scheduledTimerWithTimeInterval:5
                            target:self
                          selector:@selector(handleTimerFire:)
                          userInfo:nil
                           repeats:NO];
}

- (void)handleTimerFire:(NSTimer *)timer {
  [[NSApplication sharedApplication] terminate:self];
}

@end
