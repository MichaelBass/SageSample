//
//  PROViewController.m
//  Sample2
//
//  Created by Michael Bass on 9/25/18.
//  Copyright © 2018 mss. All rights reserved.
//

#import "PROViewController.h"

@interface PROViewController ()
@property (nonatomic, retain) id<IRTEngine> engine;
@property (nonatomic, retain) NSMutableString* auditLog;
@end

@implementation PROViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self setUp];
    //[self basicTest:2];
}

-(void)logTrace:(NSString*) trace{
    [self.auditLog appendString:trace];
    [self.auditLog appendString:@"\n"];
}

-(void)writeTrace{
    
    NSString *filePath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"IRTLog.txt"];
    NSFileHandle *myHandle = [NSFileHandle fileHandleForWritingAtPath:filePath];
    [myHandle seekToEndOfFile];
    [myHandle writeData:[self.auditLog dataUsingEncoding:NSUTF8StringEncoding]];
}

-(void)setUp{
    
 /*
    if(!_auditLog){
        NSLog(@"%@",[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"IRTLog.txt"]);
        _auditLog = [[NSMutableString alloc] init];
        
        NSFileManager *fileManager = [NSFileManager defaultManager];
        NSString *filePath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"IRTLog.txt"];
        
        if (![fileManager fileExistsAtPath:filePath]){
            NSError *error;
            [@"Start Unit Test\n" writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:&error];
        }
        
    }
 */
    NSBundle *bundle = [NSBundle mainBundle];
//    for (NSBundle *bundles in [NSBundle allBundles]) {
//        bundle = [NSBundle bundleWithPath:[bundles pathForResource:@"Content" ofType:@"bundle"]];
//        if(bundle){ break; }
//    }

    NSString *param_file2 =@"Content/Calibrations/BEBC8474-D244-4A38-87DE-00A640DE03DE.json";    //PROMIS-Ca Bank v1.0 - Depression
    NSString *paramFile2 = [bundle.resourcePath stringByAppendingPathComponent:param_file2];
    

    NSString *file2 = @"Content/Forms/BEBC8474-D244-4A38-87DE-00A640DE03DE.json";    //PROMIS-Ca Bank v1.0 - Depression
    NSString *fileDOM2 = [bundle.resourcePath stringByAppendingPathComponent:file2];
    
    
    self.engine = (id<IRTEngine>)[[IRTGradedResponseModelEngine alloc] initWithParameterFile:paramFile2];
    [self.engine setItemList:fileDOM2];

    // NSLog(@"Expires in %d days",[self.engine getExpiration]);
    NSLog(@"Expires in %d days",[self.engine getExpiration]);
}


-(void)basicTest:(int)responseValue{
    
    [self logTrace:@"Basic Test - Answer every question the same. No scores"];
    //Select the first Item ID.
    NSArray *itemIDs = [self.engine getNextItems];
    
    //Stopping rule: engine.finished is true or getNextItems is nil. (choose one)
    //then the administration is done.
    
    //while (itemIDs) {
    while (!self.engine.finished ) {
        
        // get the first Item by ItemID
        NSArray *items = [self.engine getItems :itemIDs];
        IRTItem *item = (IRTItem *)items[0];
        
        // Log out the DOM on the item to simulate the UI
        [self renderItem:item];
        
        IRTMapResponse* response = [self selectResponse: (NSInteger)responseValue item:item];
        
        // send the user response back to the engine. In this example always respond to the second option.
        NSString* ItemResponseOID = response.itemResponseOID;
        
        NSArray *formItemOIDs =[NSArray arrayWithObjects:item.formItemOID,nil];
        NSArray *itemResponseOIDs  = [NSArray arrayWithObjects:ItemResponseOID,nil];
        
        [self.engine processResponses:formItemOIDs itemResponseOIDs:itemResponseOIDs];
        
        //get the next item ID
        itemIDs = [self.engine getNextItems];
        
    }

    
    //[self displayResults:[self.engine getItemResults]];
    //[self writeTrace];
    
    //return [self.engine getTheta ];
    
    [self.delegate viewControllerDidFinish:  self.engine];
    
}

-(void) renderItem:(IRTItem *) item{
    
    //NSLog(@"Printing Item: \r%@", item.formID);
    NSString *itemHeader = [NSString stringWithFormat:@"Printing Item: %@", item.formID];
    [self logTrace:itemHeader];
    NSString *context = ((IRTElement*)item.elements[0]).elementText;
    //NSLog(@"%@", context);
    [self logTrace:context];
    
    
    if(item.elements.count > 2){
        NSString *stem = ((IRTElement*)item.elements[1]).elementText;
        // NSLog(@"%@", stem);
        [self logTrace:stem];
    }
    for (IRTMapResponse* map in ((IRTElement*)item.elements[item.elements.count-1]).mappings){
        NSString *mapOutput = [NSString stringWithFormat:@"%@ : %@ (%@)", map.itemResponseOID, map.mapText, map.value];
        [self logTrace:mapOutput];
        //NSLog(@"%@ : %@ (%@)", map.itemResponseOID, map.mapText, map.value);
    }
}

-(void) displayResults:(NSArray*) results {
    
    NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
    [formatter setMaximumFractionDigits:6];
    [formatter setMinimumFractionDigits:6];
    
    
    [self logTrace:[NSString stringWithFormat:@"\nResults:\n"]];
    [self logTrace:[NSString stringWithFormat:@"ItemDataOID\t\tDate Time Stamp\t\tItemID\t\tAnswer\t\tTheta\tSE\tPosition"]];
    
    
    for (IRTItem *myResult in results) {
        
        NSString* itemResult =    [NSString stringWithFormat:@"%@\t%@\t%@\t\t%@\t%@\t%@\t%@",myResult.itemDataOID,myResult.dateCreated,myResult.formID,myResult.answer,[formatter stringFromNumber:myResult.theta],[formatter stringFromNumber:myResult.se],myResult.position];
        NSString *resultOutput = [NSString stringWithFormat:@"%@",itemResult];
        [self logTrace:resultOutput];
        
        NSLog(@"%@",resultOutput);
        
    }
    [self logTrace:@""];
    [self logTrace:@""];
}

-(IRTMapResponse*) selectResponse:(NSInteger) position item:(IRTItem*) item {
    
    return  (IRTMapResponse*)(((IRTElement*)item.elements[item.elements.count -1]).mappings[position]);
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
- (IBAction)runTests:(id)sender {
    [self basicTest:2];
}

@end
