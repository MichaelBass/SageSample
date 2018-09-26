/*!
 *
 * @header IRTElement.h.
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
 * @brief The smallest representation of the building blocks of an item.
 * IRTElement represents an unit of metadata that can be rendered in an UI.
 */
@interface IRTElement : NSObject

/*!
 * @brief internal name (ref. primary key) of an element.
 *
 * @discussion
 * Internal use only.
 * @return NSString
 */
@property (strong, nonatomic) NSString *elementOID;

/*!
 * @brief Text representation of the element.
 *
 * @discussion
 * Usually the information that is rendered to the UI.
 * @return NSString
 */
@property (strong, nonatomic) NSString *elementText;

/*!
 * @brief Ordering of the element within the parent collection (i.e. item.elements).
 *
 * @discussion
 * When rendering UI, this property should dictate the relative placement of the elements on the interface.
 * @return NSString
 */
@property (strong, nonatomic) NSString *elementOrder;

/*!
 * @brief Collection of response elements (i.e. Maps).
 *
 * @discussion
 * Represents the response options of an item.
 * @return NSMutableArray
 */
@property (strong, nonatomic) NSMutableArray *mappings;

@end
