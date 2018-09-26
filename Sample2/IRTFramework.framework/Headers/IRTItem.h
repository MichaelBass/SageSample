/*!
 *
 * @header IRTItem.h.
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
 * @brief The main meta data structure for UI.
 * IRTItem represents a single observation for statistical purposes.
 */
@interface IRTItem : NSObject

/*!
 * @brief User-defined id for an item.
 *
 * @discussion
 * Used for item representation in reporting and returned array elements for getNext/Previous Items.
 * @return NSString
 */
@property (strong, nonatomic) NSString *formID;

/*!
 * @brief internal name (ref. primary key) of an item.
 *
 * @discussion
 * internal use only as key for Dictionaries
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *formItemOID;

/*!
 * @brief position of item within form.
 *
 * @discussion
 * for sequential administration the order will dictate item administration position.
 *
 * @return NSInteger
 */
@property (nonatomic) NSInteger order;

/*!
 * @brief collection of UI units for an item.
 *
 * @discussion
 * Items are composed of a collection of metadata pieces called 'elements'.
 * An individual piece is called an element and can represent the following:
 * A recall period -  "In the past 7 days"
 * A focal point - "I have pain"
 * A collection of response options. "Never, Sometimes, Always".
 *
 * This collection can have 1 to many elements.
 * User responses/results will only exist if this collection contains a collection of responses.
 * Otherwise, the item is presented to the user for informational purposes only.
 *
 * @return NSMutableArray
 */
@property (strong, nonatomic) NSMutableArray *elements;

/*!
 * @brief internal name (ref. primary key) of an item response.
 *
 * @discussion
 * Uniquely represents a response option for an item.
 * The same response on two different items will have different itemResponseOIDs.
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *itemResponseOID;

/*!
 * @brief represents a numerical value for a response option.
 *
 * @discussion
 * This value is sometime refered to as raw score.
 * This value does not have to be unique within a collection of response options.
 * (i.e. two response options could have the same underlying score.)
 * If an item is skipped (i.e. not answered, then the score is nil.
 * @return NSNumber
 */
@property (strong, nonatomic) NSNumber *score;

/*!
 * @brief represents a string value for a response option.
 *
 * @discussion
 * This is not to be confused with the text a user sees for a response.
 * In most cases, this repesents the String value of a score.
 * If an item is skipped, then this value = @"00000000-0000-0000-0000-000000000000"
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *response;

/*!
 * @brief String representation of the sequence of item administration.
 *
 * @discussion
 * For adaptive administration, the position property represents the order of administration.
 * This will differ from the order property, which represents the placement of the item on the form in relation to the other items.
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *position;

/*!
 * @brief system generated unique identifier for an item that has been administered and responded to.
 *
 * @discussion
 * This property will uniquely identify an item that has response data associated with it.
 * Skipped items will also have an itemDataOID assigned.
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *itemDataOID;

/*!
 * @brief interm Standard Error of the assessment at the time the item had been administered.
 *
 * @discussion
 * The Standard Error is recalcuated after each item is adminstered and the calculated value is stored in this property.
 *
 * @return NSNumber
 */
@property (strong, nonatomic) NSNumber *se;

/*!
 * @brief interm Logit-based ability estimate for an assessment at the time the item had been administered.
 *
 * @discussion
 * The Theta estimate is recalcuated after each item is adminstered and the calculated value is stored in this property.
 *
 * @return NSNumber
 */
@property (strong, nonatomic) NSNumber *theta;

/*!
 * @brief Time stamp of when the item had been answered.
 *
 * @discussion
 * The format for this property is: @"yyyy-MM-dd HH:mm:ss"
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *dateCreated;

/*!
 * @brief Text associated with the response option presented to the user.
 *
 * @discussion
 * This property uniquely represents the options an user sees during the administration of an assessment.
 * Since the score of a response is not necessarily unique, this property is an unique user-friendly representation of a user response.
 *
 * @return NSString
 */
@property (strong, nonatomic) NSString *answer;
@end
