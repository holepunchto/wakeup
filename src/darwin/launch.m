#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

int
wakeup_launch (const char *app, size_t argc, const char *argv[]) {
  NSMutableArray<NSString *> *arguments = [[NSMutableArray alloc] initWithCapacity:argc];

  for (size_t i = 0; i < argc; i++) {
    arguments[i] = [NSString stringWithFormat:@"%s", argv[i]];
  }

  NSURL *url = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%s", app]];

  NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];

  configuration.arguments = arguments;

  [[NSWorkspace sharedWorkspace]
    openApplicationAtURL:url
           configuration:configuration
       completionHandler:nil];

  return 0;
}
