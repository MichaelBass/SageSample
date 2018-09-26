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
    

}

extension RSDStepNavigatorType {
    static let example: RSDStepNavigatorType = "example"
}
