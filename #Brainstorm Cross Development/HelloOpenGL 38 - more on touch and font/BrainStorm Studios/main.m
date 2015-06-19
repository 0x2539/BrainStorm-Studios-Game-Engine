
#import <UIKit/UIKit.h>
#import "HelloOpenGLAppDelegate.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"HelloOpenGLAppDelegate");
    [pool release];
    return retVal;
}
