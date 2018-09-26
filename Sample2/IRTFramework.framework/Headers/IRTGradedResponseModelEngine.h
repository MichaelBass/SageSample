/*!
 *
 * @header IRTGradedResponseModelEngine.h.
 * @author Michael Bass
 * @copyright Copyright (c) 2016, Michael Bass All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1.  Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3.  Neither the name of the copyright holder(s) nor the names of any contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission. No license is granted to the trademarks of
 * the copyright holders even if such marks are included in this software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER, AUTHOR AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>

#import "IRTEngine.h"
#import "IRTItem.h"
#import "IRTRatingScaleItemCalibration.h"

#import "IRTMapResponse.h"
/*!
 * @brief The main class for administering IRT-based forms.
 * This is the concrete implementation for Graded Response Model algorithm.
 */
@interface IRTGradedResponseModelEngine : NSObject <IRTEngine>

/*!
 * @brief A collection of IRTItem(s) used for an assessment.
 *
 * @discussion
 * The setter method -(void)setItemList: (NSString *) formFile should be called right after the parameters are loaded -(id)initWithParameterFile:(NSString *)formFile;.
 * formFile is the name of the json formatted file from the server API Form/{formOID}.json endpoint. 
 * @return NSArray
 */
@property (nonatomic, copy) NSArray *itemList;

/*!
 * @brief Counter of items administered.
 *
 * @discussion
 * Used for validating max and min stopping rule.
 *
 * @return int
 */
@property (nonatomic) int position;

/*!
 * @brief Collection of statistical values used for administration and scoring of IRT-based instruments.
 *
 * @discussion
 * The dictionary is loaded when initializing the engine with the following constructor: -(id)initWithParameterFile:(NSString *)parameterFile
 * parameterFile is the name of the json formatted file from the server API Calibrations/{formOID}.json endpoint.
 * @return NSDictionary
 */
@property (nonatomic, copy) NSDictionary *parameterDictionary;

/*!
 * @brief Logit-based ability estimate for an assessment.
 *
 * @discussion
 * The theta value is usually presented to end-users as T-Score (i.e. T-Score = theta*10.0 + 50.0)
 * @return float
 */
@property (nonatomic) double theta;

/*!
 * @brief Standard Error of ability estimate.
 *
 * @discussion
 * Represents the standard deviation of the ability estimate.
 * @return float
 */
@property (nonatomic) double se;

/*!
 * @brief Lower bound of quadrature grid.
 *
 * @discussion
 * Default value = -4.0.
 * @return float
 */
@property (nonatomic) float min_ability;

/*!
 * @brief Upper bound of quadrature grid.
 *
 * @discussion
 * Default value = 4.0.
 * @return float
 */
@property (nonatomic) float max_ability;

-(void)processRatingScaleItem:(IRTRatingScaleItemCalibration *)ratingScaleItem andItem:(IRTItem *)item;

-(IRTMapResponse *)mapForResponseWithID:(NSString *)ItemResponseOID forItem:(IRTItem *)item;
- (NSString *)getResponse:(NSString *)FormItemOID ItemResponseOID:(NSString *)ItemResponseOID;
@end
