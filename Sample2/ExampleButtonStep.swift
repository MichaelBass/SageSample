//
//  ExampleButtonStep.swift
//  Sample2
//
//  Created by Michael Bass on 9/26/18.
//  Copyright © 2018 mss. All rights reserved.
//

import UIKit
import Research
import ResearchUI
//class ExternalIDRegistrationStep : RSDUIStepObject, RSDFormUIStep, RSDStepViewControllerVendor

struct ExampleButtonStep: RSDUIStep,  Decodable {
//    private enum CodingKeys: String, CodingKey, CaseIterable {
//        case identifier
//        case stepType = "type"
//        case title
//        case text
//        case detail
//        case footnote
//    }
    
    
    
    let title: String?
    
    let text: String?
    
    let detail: String?
    
    let footnote: String?
    
    let identifier: String
 
    let buttonCaption: String
        
    let type: RSDStepType
    
    var stepType: RSDStepType {
        return self.type
    }
    
    func instantiateStepResult() -> RSDResult {
        return RSDAnswerResultObject(identifier: self.identifier, answerType: .integer)
    }
    
    func validate() throws {
        //do nothing
    }
    
    func action(for actionType: RSDUIActionType, on step: RSDStep) -> RSDUIAction? {
        return nil
    }
    
    func shouldHideAction(for actionType: RSDUIActionType, on step: RSDStep) -> Bool? {
        return nil
    }
    


}
