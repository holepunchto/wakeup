#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#import <appling.h>

#import "../../include/wakeup.h"
#import "../platform.h"

int
wakeup_launch (const appling_app_t *app, const char *url, void *data) {
  @autoreleasepool {
    NSAppleEventDescriptor *event = CFBridgingRelease(data);

    NSURL *path = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%s", app->path]];

    NSMutableArray<NSString *> *components = [NSMutableArray arrayWithArray:path.pathComponents];

    while (components.count > 0) {
      NSString *component = [components lastObject];

      if ([component.pathExtension isEqualToString:@"app"]) break;

      [components removeLastObject];
    }

    if (components.count == 0) return -1;

    path = [NSURL fileURLWithPathComponents:components];

    NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];

    configuration.arguments = @[ [NSString stringWithFormat:@"%s", url] ];

    if (event) configuration.appleEvent = event;

    __block NSError *error = Nil;

    dispatch_semaphore_t sem = dispatch_semaphore_create(0);

    [[NSWorkspace sharedWorkspace]
      openApplicationAtURL:path
             configuration:configuration
         completionHandler:^(NSRunningApplication *app, NSError *err) {
           error = err;

           dispatch_semaphore_signal(sem);
         }];

    dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);

    dispatch_release(sem);

    if (error) return -1;
  }

  return 0;
}
