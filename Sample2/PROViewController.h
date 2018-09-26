//
//  PROViewController.h
//  Sample2
//
//  Created by Michael Bass on 9/25/18.
//  Copyright © 2018 mss. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <IRTFramework/IRTFramework.h>

NS_ASSUME_NONNULL_BEGIN
@protocol PROViewControllerDelegate <NSObject>

- (void) viewControllerDidFinish: (id <IRTEngine>) engine;

@end
@interface PROViewController : UIViewController

@property (weak, nonatomic) id<PROViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
