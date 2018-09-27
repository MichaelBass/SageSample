//
//  ExampleFactory.swift
//  Sample2
//
//  Created by Michael Bass on 9/26/18.
//  Copyright © 2018 mss. All rights reserved.
//

import UIKit
import Research
import BridgeApp

class ExampleFactory: SBAFactory {
    
    override func decodeStepNavigator(from decoder: Decoder, with type: RSDStepNavigatorType) throws -> RSDStepNavigator {
        switch type {
        case .example:
            return try ExampleNavigator(from: decoder)
        default:
            return try super.decodeStepNavigator(from: decoder, with: type)
        }
    }
    
    override func decodeStep(from decoder: Decoder, with type: RSDStepType) throws -> RSDStep? {
        switch type {
        case .exampleButton:
            return try ExampleButtonStep(from: decoder)
        default:
            return try super.decodeStep(from: decoder, with: type)
        }
    }
    

}

extension RSDStepNavigatorType {
    static let example: RSDStepNavigatorType = "example"
}

extension RSDStepType {
    static let exampleButton: RSDStepType = "exampleButton"
}
