/*!
 *
 * @header IRTEngine.h.
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
* @brief The main class for administering IRT-based forms.
* This is an abstract class, cast concrete implemented engines to this protocol.
*/
@protocol IRTEngine <NSObject>

/*!
 * @brief internal name (ref. primary key) of the currently administered item.
 *
 * @discussion
 * internal use only.
 *
 * @return NSString
 */
@property (nonatomic, strong) NSString *itemID;


/*!
 * @brief Determine if an assessment is finished.
 *
 * @discussion
 * flag is set when administration algorithm determines as assessment is done or all items have been administered.
 *
 * @return Boolean
 */
@property (nonatomic) BOOL finished;

/*!
 * @brief Initializer method for the IRTEngine.
 *
 * @discussion
 * The formData comes from the server API Calibration/{formOID}.json endpoint.
 *
 *
 *    NSString *file ="Neuro-QOL Bank v1.0 - Ability to Part. in SRA.json";
 *    NSData *fileDOM = [bundle.resourcePath stringByAppendingPathComponent:file];
 *    self.engine = (id<IRTEngine>)[[IRTGradedResponseModelEngine alloc] initWithParameterFile:fileDOM encoding:NSUTF8StringEncoding];
 *
 * @param formData json-formatted statistics file.
 *
 * @return IRTEngine The main class for administering IRT-based forms.
 */
-(id)initWithParameterFileWithData:(NSData *)formData;
/*!
 * @brief Setter method for loading items into the Engine.
 *
 * @discussion
 * The formData comes from the server API Form/{formOID}.json endpoint.
 *
 * @param formData json-formatted item DOM (see server API for specs).
 *
 */
-(void)setItemListWithData: (NSData *) formData;

/*!
 * @brief Setter method for loading previously administered items into the Engine.
 *
 * @discussion
 * This method would be called if an asseessment is restarting.
 *
 * @param formData json-formatted file returned from getPreviousResults.
 *
 */
-(void)setPreviousResultsWithData: (NSData *) formData;



/*!
* @brief Initializer method for the IRTEngine.
*
* @discussion
* The formFile comes from the server API Calibration/{formOID}.json endpoint.
*
*
*    NSString *file ="Neuro-QOL Bank v1.0 - Ability to Part. in SRA.json";
*    NSString *fileDOM = [bundle.resourcePath stringByAppendingPathComponent:file];
*    self.engine = (id<IRTEngine>)[[IRTGradedResponseModelEngine alloc] initWithParameterFile:paramFile];
*
* @param formFile json-formatted statistics file.
*
* @return IRTEngine The main class for administering IRT-based forms.
*/
-(id)initWithParameterFile:(NSString *)formFile;

/*!
 * @brief Setter method for loading items into the Engine.
 *
 * @discussion
 * The formFile comes from the server API Form/{formOID}.json endpoint.
 *
 * @param formFile json-formatted item DOM (see server API for specs).
 *
 */
-(void)setItemList: (NSString *) formFile;

/*!
 * @brief Setter method for loading previously administered items into the Engine.
 *
 * @discussion
 * This method would be called if an asseessment is restarting.
 *
 * @param formFile json-formatted file returned from getPreviousResults.
 *
 */
-(void)setPreviousResults: (NSString *) formFile;

/*!
 * @brief Getter method for returning administered items.
 *
 * @discussion
 * This method can be called to retrieve state of the Engine and can be reloaded to continue an assessment at a later date.
 *
 * @return NSString json-formatted string representation of assessment state.
 */
-(NSString *) getPreviousResults;


/*!
 * @brief Getter method for returning the next items to render to the UI.
 *
 * @discussion
 * This method is called to navigate through the assessment. For most engines this method will return an array with 1 item
 *
 * @return NSArray Containing the item DOM to be rendered to the UI.
 */
-(NSArray *) getNextItems;

/*!
 * @brief Getter method for returning the previous items to render to the UI.
 *
 * @discussion
 * This method is called to navigate back through the assessment. For most engines this method will return an array with 1 item
 *
 * @return NSArray Containing the item DOM to be rendered to the UI.
 */
-(NSArray *) getPreviousItems;

/*!
 * @brief Getter method for returning current items to render to the UI.
 *
 * @discussion
 * This method is intended for internal use. IRTEngine is stateful and will return the same array based on the internal state of the engine.
 *
 * @param formItemOIDs item id for the item to return.
 *
 * @return NSArray Containing the item DOM to be rendered to the UI.
 */
-(NSArray *) getItems :(NSArray *) formItemOIDs;

/*!
 * @brief Getter method for returning the administered items.
 *
 * @discussion
 * This method returns a trace of the assessment.
 *
 * @return NSArray Containing the item that have been administered and scored.
 */
-(NSArray *) getItemResults;

/*!
 * @brief Method for sending user input to the Engine in order to calculate score and determine the next item(s) to present.
 *
 * @discussion
 * For most engine, the parameter arrays will contain one object each
 *
 * @param formItemOIDs item ids for the items that the user is responding to.
 * @param itemResponseOIDs response ids for the items that the user is responding to.
 *
 */
-(void)processResponses:(NSArray *)formItemOIDs itemResponseOIDs:(NSArray *)itemResponseOIDs;

/*!
 * @brief Method for sending user input to the Engine in order to calculate score and determine the next item(s) to present.
 *
 * @discussion
 * For most engine, the parameter arrays will contain one object each
 *
 * @param formItemOIDs item ids for the items that the user is responding to.
 * @param itemResponseOIDs response ids for the items that the user is responding to.
 * @param itemDataOIDs primary keys for the items that the user is responding to.
 * @param datesCreated datestamps for the items that the user is responding to.
 *
 */
//-(void)processResponses:(NSArray *)formItemOIDs itemResponseOIDs:(NSArray *)itemResponseOIDs itemDataOIDs:(NSArray *)itemDataOIDs datesCreated:(NSArray *)datesCreated;

/*! 
 @brief Getter method for retrieving the current estimate of the executing assessment.
 
 @return float The current estimate in Logit.
*/
-(double) getTheta;

/*!
 @brief Getter method for retrieving the current standard error of the executing assessment.
 
 @return float The current standard error in Logit.
 */
-(double) getSE;

/*!
 @brief Getter method for retrieving the days until expiration.
 
 @return int The current days until expiration.
 */
-(int) getExpiration;

@end
