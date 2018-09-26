//
//  ExampleButtonStepViewController.swift
//  Sample2
//
//  Created by Michael Bass on 9/26/18.
//  Copyright © 2018 mss. All rights reserved.
//

import UIKit
import Research
import ResearchUI

class ExampleButtonStepViewController: RSDStepViewController {

    @IBOutlet weak var button: UIButton!

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        if let buttonStep = self.step as? ExampleButtonStep {
            self.button.setTitle(buttonStep.buttonCaption, for: .normal)
        }
    }
    
    @IBAction func pressed(_ sender: Any) {
        if let buttonStep = self.step as? ExampleButtonStep {
            //get the result and add a number
            
        }
        self.goForward()

    }
    
}
