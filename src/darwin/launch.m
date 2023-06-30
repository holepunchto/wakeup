#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#import "../../include/wakeup.h"

int
wakeup_launch (const wakeup_app_t *app, const char *url) {
  @autoreleasepool {
    NSURL *path = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%s", app->path]];

    NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];

    configuration.arguments = @[ [NSString stringWithFormat:@"%s", url] ];

    [[NSWorkspace sharedWorkspace]
      openApplicationAtURL:path
             configuration:configuration
         completionHandler:nil];
  }

  return 0;
}
