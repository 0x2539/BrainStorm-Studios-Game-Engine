
#import "HelloOpenGLAppDelegate.h"

@interface MyViewController : UIViewController
@end

@implementation MyViewController
- (void)loadView {
    // Create your EAGL view
    //CGRect screenBounds = [[UIScreen mainScreen] bounds];
    OpenGLView *eaglView = [[OpenGLView alloc] initWithFrame:CGRectMake(0, 0, 480, 320)];
    self.view = eaglView;
    [eaglView release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}
@end

@implementation HelloOpenGLAppDelegate
@synthesize glView=_glView;

@synthesize window=_window;

/*
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    CGRect screenBounds = [[UIScreen mainScreen] bounds];    
    self.glView = [[[OpenGLView alloc] initWithFrame:screenBounds] autorelease];
    [self.window addSubview:_glView];
    [self.window makeKeyAndVisible];
    return YES;
}*/
- (void)applicationDidFinishLaunching:(UIApplication *)application {
    MyViewController *viewController = [[MyViewController alloc] init];
    [self.window setRootViewController:viewController];
    [viewController release];
    [self.window makeKeyAndVisible];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

- (void)dealloc
{
    [_glView release];
    [_window release];
    [super dealloc];
}

@end

