//
//  ViewController.swift
//  SmartPiggyBank
//
//  Created by M. Ayberk Kale on 6.11.2018.
//  Copyright © 2018 MAKMA. All rights reserved.
//

import UIKit
import Firebase
import FirebaseDatabase

class ViewController: UIViewController {

    @IBOutlet weak var UserDesiredValue: UITextField!
    
   
    
    
    @IBOutlet weak var twentyfivekurusvalue: UITextField!
    
    
    @IBOutlet weak var fiftykurusvalue: UITextField!
    
    
    @IBOutlet weak var onetlvalue: UITextField!
    
     var ref:FIRDatabaseReference?
    
 
   
    @IBAction func OKBUTTON_5(_ sender: UIButton) {
        ref=FIRDatabase.database().reference()
        
        let UserDesiredValue_string = NSString(string: UserDesiredValue!.text! )
        
        if(UserDesiredValue_string != ""){
            
            let five_one="1"
            
            
            let UserDesiredValue_string_5: NSString = NSString(format: "%@%@", five_one, UserDesiredValue_string)
            ref?.child("UserDesired").setValue( UserDesiredValue_string_5.doubleValue)
            
        }
        
        UserDesiredValue.resignFirstResponder()
    }

    
    
    @IBAction func OKUBUTTON_25(_ sender: UIButton) {
        
        ref=FIRDatabase.database().reference()
        
        let UserDesiredValue_string = NSString(string: twentyfivekurusvalue!.text! )
        
        if(UserDesiredValue_string != ""){
            
            let twentyfive_one="2"
            
            
            let UserDesiredValue_string_25: NSString = NSString(format: "%@%@", twentyfive_one, UserDesiredValue_string)
            ref?.child("UserDesired").setValue( UserDesiredValue_string_25.doubleValue)
            
        }
        
         twentyfivekurusvalue.resignFirstResponder()
    }
    
    
  
    
    @IBAction func OKBU_50(_ sender: UIButton) {
        
        ref=FIRDatabase.database().reference()
        
        let UserDesiredValue_string = NSString(string: fiftykurusvalue!.text! )
        
        if(UserDesiredValue_string != ""){
            
            let fifty_one="3"
            
            
            let UserDesiredValue_string_50: NSString = NSString(format: "%@%@", fifty_one, UserDesiredValue_string)
            ref?.child("UserDesired").setValue( UserDesiredValue_string_50.doubleValue)
            
        }
        
        fiftykurusvalue.resignFirstResponder()
    }
    
   
    @IBAction func UIBUT_1(_ sender: UIButton) {
        
        ref=FIRDatabase.database().reference()
        
        let UserDesiredValue_string = NSString(string: onetlvalue!.text! )
        
        if(UserDesiredValue_string != ""){
            
            let onetl_one="4"
            
            
            let UserDesiredValue_string_1: NSString = NSString(format: "%@%@", onetl_one, UserDesiredValue_string)
            ref?.child("UserDesired").setValue( UserDesiredValue_string_1.doubleValue)
            
        }
        
        onetlvalue.resignFirstResponder()
    }
    
    @IBAction func Servo1Switch(_ sender: UISwitch) {
        
        var ref: FIRDatabaseReference?
        
        ref = FIRDatabase.database().reference()
        if sender.isOn {
            
            ref?.child("ServoOne").setValue(Bool(true))
            
            
            
        }else{
            ref?.child("ServoOne").setValue(Bool(false))
            
            
        }
    }
     @IBOutlet weak var dataView: UITextView?
    
    
    
    @IBOutlet weak var dataView2: UITextView?
    
   
    @IBOutlet weak var  dataView3: UITextView?
    
    
    @IBOutlet weak var dataView4: UITextView?
    
    
    @IBAction func getDataPressed(){
        APIManager.sharedInstance.getPostWithId(postId: 1, onSuccess: { json in
            DispatchQueue.main.async {
                
                
              //  let json_answer = (json)["feeds"]
                
                 let json_answer_5kurus = (json)["feeds"][0]["field1"]
                
                 let json_answer_25kurus = (json)["feeds"][0]["field2"]
                
                 let json_answer_50kurus = (json)["feeds"][0]["field3"]
                
                 let json_answer_1tl = (json)["feeds"][0]["field4"]
               // let id = name["feeds"].string
                
               // self.dataView?.text = String(describing: json)
                
              
              
                
                self.dataView?.text = String(describing: json_answer_5kurus)
                    self.dataView2?.text = String(describing: json_answer_25kurus)
                    self.dataView3?.text = String(describing: json_answer_50kurus)
                    self.dataView4?.text = String(describing: json_answer_1tl)
               
            }
        }, onFailure: { error in
            let alert = UIAlertController(title: "Error", message: error.localizedDescription, preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "Dismiss", style: .default, handler: nil))
            self.show(alert, sender: nil)
        })
    }

    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }


}

