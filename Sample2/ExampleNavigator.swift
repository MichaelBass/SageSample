//
//  ExampleNavigator.swift
//  Sample2
//
//  Created by Michael Bass on 9/26/18.
//  Copyright © 2018 mss. All rights reserved.
//

import UIKit
import Research

struct ExampleNavigator: RSDStepNavigator, Decodable {
    private enum CodingKeys : String, CodingKey, CaseIterable {
        case steps
    }

    let steps: [RSDStep]
    
    init(with steps:[RSDStep]) {
        self.steps = steps
    }
   
    public init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        let factory = decoder.factory
        
        // Decode the steps
        let stepsContainer = try container.nestedUnkeyedContainer(forKey: .steps)
        self.steps = try factory.decodeSteps(from: stepsContainer)
        
    }

    
    
    
    func step(with identifier: String) -> RSDStep? {
        return self.steps.first {
            $0.identifier == identifier
        }
    }
    
    func shouldExit(after step: RSDStep?, with result: RSDTaskResult) -> Bool {
        return false
    }
    
    func hasStep(after step: RSDStep?, with result: RSDTaskResult) -> Bool {
        guard let step = step else {
            return true
        }
        return self.steps.last?.identifier != step.identifier
    }
    
    func hasStep(before step: RSDStep, with result: RSDTaskResult) -> Bool {
        return false
    }
    
    func step(after step: RSDStep?, with result: inout RSDTaskResult) -> (step: RSDStep?, direction: RSDStepDirection) {
        let isLastStep = self.steps.last?.identifier == step?.identifier
        guard let step = step,
            let answerResult = result.findAnswerResult(with: step.identifier),
            let answer = answerResult.value as? Int,
            answer < self.steps.count
        else {
            let nextStep = isLastStep ? nil : self.steps.first
            return (nextStep, .forward)
        }
        let nextStep = isLastStep ? nil : self.steps[answer]
        return (nextStep,.forward)

    }
    
    func step(before step: RSDStep, with result: inout RSDTaskResult) -> RSDStep? {
        return nil
    }
    
    func progress(for step: RSDStep, with result: RSDTaskResult?) -> (current: Int, total: Int, isEstimated: Bool)? {
        return nil
    }
    

}
