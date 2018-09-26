/*!
 *
 * @header IRTItemCalibration.h.
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

/*!
 * @brief The main meta data structure for item parameters.
 * IRTItemCalibration represents a single item for statistical purposes.
 */
@interface IRTItemCalibration : NSObject

/*!
 * @brief User-defined id for an item.
 *
 * @discussion
 * Used for statistical item representation.
 * @return NSString
 */
@property (nonatomic, strong) NSString *formItemOID;

/*!
 * @brief User-friendly id for an item.
 *
 * @discussion
 * Used for reporting.
 * @return NSString
 */
@property (nonatomic, strong) NSString *itemID;

/*!
 * @brief Discrimination parameter.
 *
 * @return double
 */
@property (nonatomic) double a_GRM;

/*!
 * @brief variance parameter.
 * @discussion
 * Used for item selection.
 * @return double
 */
@property (nonatomic) double variance;

/*!
 * @brief internal flag for administered items.
 * @discussion
 * Used internally for determining if an item has already been administered.
 * @return bool
 */
@property (nonatomic) bool administered;


/*!
 * @brief Constructor method for loading complete set of.
 *
 * @discussion
 * For most engine, the parameter arrays will contain one object each
 *
 * @param formitemoid item ids for the items that the user is responding to.
 * @param itemid user-friendly reference for item.
 * @param a_grm aka slope.
 *
 */
-(id)initWithName:(NSString *)formitemoid itemid:(NSString *)itemid a_grm:(double ) a_grm;

@end
