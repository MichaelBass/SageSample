//
//  ViewController.swift
//  Sample2
//
//  Created by Michael Bass on 9/22/18.
//  Copyright © 2018 mss. All rights reserved.
//

import UIKit
import IRTFramework
import BridgeApp

class MainViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    let scheduleManager = SBAScheduleManager()
    
    @IBOutlet weak var tableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        NotificationCenter.default.addObserver(forName: .SBAUpdatedScheduledActivities,
                                               object: self.scheduleManager,
                                               queue: OperationQueue.main) {(_) in
                                                
                                                self.tableView.reloadData()
        }
        
        
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.scheduleManager.scheduledActivities.count
        
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "ScheduleCell", for: indexPath)
        let schedule = self.scheduleManager.scheduledActivities[indexPath.row]
        cell.textLabel?.text = schedule.activity.label
        cell.detailTextLabel?.text = schedule.activity.detail
        
        return cell
    }

    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let schedule = self.scheduleManager.scheduledActivities[indexPath.row]
        guard let taskIdentifier = schedule.activityIdentifier else {
            return
        }
        
        if (taskIdentifier == "Example_List") {
            let taskViewModel = self.scheduleManager.instantiateTaskViewModel(for: schedule)
            let viewController = RSDTaskViewController(taskViewModel: taskViewModel)
            viewController.delegate = self
            self.present(viewController, animated: true, completion: nil)
        }
        else {
            //bring up PRO
        }
        
        print("\(taskIdentifier)")
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard  let viewController = segue.destination as? PROViewController else {
            return
        }
        viewController.delegate = self
    }

}


extension MainViewController: PROViewControllerDelegate {
    func viewControllerDidFinish(_ engine: IRTEngine) {
        print("We have a result with \(engine.getItemResults()?.count ?? 0) items.\n\(String(describing: engine.getItemResults()))")
        
        guard let indexPath = self.tableView.indexPathForSelectedRow,
            indexPath.item < self.scheduleManager.scheduledActivities.count,
            let taskIdentifier = self.scheduleManager.scheduledActivities[indexPath.row].activityIdentifier
            else {
                return
        }
        
        let irtResult = IRTResult(identifier: taskIdentifier, engine: engine)
//        let navigator = RSDConditionalStepNavigatorObject(with: [])
//        let task = RSDTaskObject(identifier: taskIdentifier, stepNavigator: navigator)
        var taskResult = RSDTaskResultObject(identifier: taskIdentifier)
        taskResult.appendAsyncResult(with: irtResult)
        let taskResultContainer = RSDTaskState(taskResult: taskResult)
        taskResultContainer.scheduleIdentifier = self.scheduleManager.scheduledActivities[indexPath.row].guid
        
        self.scheduleManager.archiveAndUpload(taskResultContainer)
    }
    
}

extension MainViewController: RSDTaskViewControllerDelegate {
    func taskController(_ taskController: RSDTaskController, didFinishWith reason: RSDTaskFinishReason, error: Error?) {
        self.presentedViewController?.dismiss(animated: true, completion: {
            self.scheduleManager.taskController(taskController, didFinishWith: reason, error: error)
        })
        
    }
    
    func taskController(_ taskController: RSDTaskController, readyToSave taskViewModel: RSDTaskViewModel) {
        self.scheduleManager.taskController(taskController, readyToSave: taskViewModel)
    }
    
    func taskViewController(_ taskViewController: UIViewController, viewControllerForStep stepModel: RSDStepViewModel) -> UIViewController? {
        guard stepModel.step.stepType == .exampleButton  else {
            return nil
        }
        
        let viewController = self.storyboard?.instantiateViewController(withIdentifier: "ExampleButtonStepViewController") as? RSDStepViewController
        viewController?.stepViewModel = stepModel
        
        return viewController
    }
    
    
}

// NSString* itemResult =    [NSString stringWithFormat:@"%@\t%@\t%@\t\t%@\t%@\t%@\t%@",myResult.itemDataOID,myResult.dateCreated,myResult.formID,myResult.answer,[formatter stringFromNumber:myResult.theta],[formatter stringFromNumber:myResult.se],myResult.position];
// NSString *resultOutput = [NSString stringWithFormat:@"%@",itemResult];
// [self logTrace:resultOutput];
//
// NSLog(@"%@",resultOutput);
//

struct IRTResult : RSDResult, RSDArchivable {

    let identifier: String
    
    let type: RSDResultType = "IRT"
    
    var startDate: Date = Date()
    
    var endDate: Date = Date()
    
    var items: [IRTItem]
    
    var score: Double
    
    var se: Double
    
    init(identifier: String, engine: IRTEngine) {
        self.identifier = identifier
        let items = engine.getItemResults()?.compactMap { $0 as? IRTItem } ?? []
        self.items = items
        self.score = items.last?.theta.doubleValue ?? 0
        self.se = items.last?.se.doubleValue ?? 0
    }
    
    func buildArchiveData(at stepPath: String?) throws -> (manifest: RSDFileManifest, data: Data)? {
        let data = try self.rsd_jsonEncodedData()
        let manifest = RSDFileManifest(filename: "irt", timestamp: Date(), contentType: "application/json", identifier: self.identifier, stepPath: stepPath)
        return (manifest, data)
    }
}


fileprivate enum IRTItemCodingKeys : String, CodingKey {
    case dateCreated, formID, answer, theta, se, position
}

extension IRTItem: Encodable {
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: IRTItemCodingKeys.self)
        try container.encodeIfPresent(self.formID, forKey: .formID)
        try container.encodeIfPresent(self.dateCreated, forKey: .dateCreated)
        try container.encodeIfPresent(self.answer, forKey: .answer)
        try container.encodeIfPresent(self.theta, forKey: .theta)
        try container.encodeIfPresent(self.se, forKey: .se)
        try container.encodeIfPresent(self.position, forKey: .position)
    }
}
