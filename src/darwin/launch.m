#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#import "../../include/wakeup.h"

int
wakeup_launch (const wakeup_app_t *app, size_t argc, const char *argv[]) {
  @autoreleasepool {
    NSMutableArray<NSString *> *arguments = [NSMutableArray arrayWithCapacity:argc];

    for (size_t i = 0; i < argc; i++) {
      arguments[i] = [NSString stringWithFormat:@"%s", argv[i]];
    }

    NSURL *url = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%s", app->path]];

    NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];

    configuration.arguments = arguments;

    [[NSWorkspace sharedWorkspace]
      openApplicationAtURL:url
             configuration:configuration
         completionHandler:nil];
  }

  return 0;
}
