#import <AppKit/AppKit.h>

#import "AppDelegate.h"

int
main () {
  NSApplication *app = [NSApplication sharedApplication];
  app.delegate = [AppDelegate new];
  [app run];
}
