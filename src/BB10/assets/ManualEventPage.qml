import bb.cascades 1.0
import bb.system 1.0

Page {
    id: manualEventScreen
    objectName: "manualEventScreen"

    signal save()
    signal deleteEvent()

    property alias eventTypeIndex: eventField.selectedIndex
    property alias startDate: startDateField.value 
    property alias endDate: endDateField.value    
    property alias startTime: startTimeField.value    
    property alias duration: durationField.text
    property alias generalNotes: genericNotesEdit.text
    property alias medicineName: medicineNameField.text
    property alias medicineNotes: medicineNotesEdit.text
    property alias mWeight: weightEdit.text
    property alias mHeight: heightEdit.text
    property alias mCephalic: cephalicEdit.text
    property alias interval: intervalField.text
    property alias startDateEnabled: startDateField.enabled
    property alias startTimeEnabled: startTimeField.enabled
    property alias eventTypeBtnRowEnabled: eventField.enabled
    property alias recurrenceVisible: recurrenceContainer.visible

    onCreationCompleted: {
        console.debug("qml:ManualEventPageLoaded");
    }

    function setTitle(title) {
        pageTitle.title=title;
        console.debug("setTitle:"+title);
    }

    function validateForm() {
        if (eventField.selectedIndex==5) {
            if  ( !(weightEdit.text>0) || !(heightEdit.text>0) || !(cephalicEdit.text>0) )
                return false;
        }
        
        if (eventField.selectedIndex==4) {
            if  ( medicineNameField.text=="")
                return false;
        }

        if ( ((!(durationField.text>0)) && (durationField.text!="0")) || (durationField.text.indexOf(".")>=0) )
            return false;
            
        if ( (!(intervalField.text>0)) || (intervalField.text.indexOf(".")>=0) )
            return false;
        
        return true;
    }
    
    titleBar: TitleBar {
        id: pageTitle
    }

    content: ScrollView {
        scrollViewProperties {
            scrollMode: ScrollMode.Vertical
        }

        Container {
	        layout: StackLayout {
	            orientation: LayoutOrientation.TopToBottom            
	        }

            Container {
		        layout: StackLayout {
		            orientation: LayoutOrientation.TopToBottom            
		        }
		        
		        leftPadding: 10
		        topPadding: 10
		        rightPadding: 10
		        bottomPadding: 10

		        DropDown {
		            id: eventField
		            title: "Event type"
		            horizontalAlignment: HorizontalAlignment.Fill
		            verticalAlignment: VerticalAlignment.Top
		                            
		            Option {
		                imageSource: "images/breastfeeding-left.png"
		                text: "Left breast"
		                selected: true
		            }
		            
		            Option {
		                imageSource: "images/baby_bottle.png"
		                text: "Bottle"
		            }
		            
		            Option {
		                imageSource: "images/breastfeeding-right.png"
		                text: "Right breast"
		            }
		
		            Option {
		                imageSource: "images/nappy.png"
		                text: "Nappy"
		            }

		            Option {
		                imageSource: "images/Pills.png"
		                text: "Medicine"
		            }

		            Option {
		                imageSource: "images/weight.png"
		                text: "Measurements"
		            }
		        }
            }
            
	        Divider {
	        }

            Container {
		        layout: StackLayout {
		            orientation: LayoutOrientation.TopToBottom            
		        }
		        
		        leftPadding: 10
		        topPadding: 10
		        rightPadding: 10
		        bottomPadding: 10

		        Label {
		            text: "When"
		            textStyle {
		                fontSize: FontSize.Large
		            }
		        }
		        	
		        DateTimePicker {
		            title: "Start date" 
		            id: startDateField

		            onValueChanged: {
		                endDateField.value=startDateField.value;
		            }
		        }
		        
		        DateTimePicker {
		            title: "Start time" 
		            id: startTimeField
		            mode: DateTimePickerMode.Time
		            minuteInterval: 1
		        }
		
		        Label {
		            text: "Duration"
		        }
		
		        TextField {
					id: durationField
					text: "0"
					hintText: "minutes"
					inputMode: TextFieldInputMode.NumbersAndPunctuation
		        }

				Label {
				    visible: ( ((!(durationField.text>0)) && (durationField.text!="0")) || (durationField.text.indexOf(".")>=0) )
				    textStyle {
				        color: Color.Red
				        fontSize: FontSize.Small
				    }
				    text: "Please enter the event's duration (minutes)" 
				}
            }
	
	        Divider {
	        }

	
	        Container {
		        layout: StackLayout {
		            orientation: LayoutOrientation.TopToBottom            
		        }
		        
		        leftPadding: 10
		        topPadding: 10
		        rightPadding: 10
		        bottomPadding: 10

		        Label {
		            text: "Notes"
		            textStyle {
		                fontSize: FontSize.Large
		            }
		        }
		        
		
		        Container {
		            id: genericContainer
		            visible: (eventField.selectedIndex<=3)
		            
		            layout: StackLayout {
		                orientation: LayoutOrientation.TopToBottom            
		            }
		
			        TextArea {
			            id: genericNotesEdit
			        }
		        }
		        
		        Container {
		            id: medicineContainer
		            visible: (eventField.selectedIndex==4)


		            layout: StackLayout {
		                orientation: LayoutOrientation.TopToBottom            
		            }
		
					TextField {
					    hintText: "Medicine name"
					    id: medicineNameField
					}
					
					Label {
					    visible: (medicineNameField.text=="")
					    textStyle {
					        color: Color.Red
					        fontSize: FontSize.Small
					    }
					    text: "Please enter the medicine's name" 
					}

					TextArea {
					    hintText: "Prescription"
					    id: medicineNotesEdit
					}
		        }
		
		        Container {
		            id: measuresContainer
		            visible: (eventField.selectedIndex==5)

		            layout: StackLayout {
		                orientation: LayoutOrientation.TopToBottom            
		            }
		
					Label {
					    text: qsTr("Weight (kg)")
					}
		
					TextField {
					    id: weightEdit
					    hintText: "weight"
					    inputMode: TextFieldInputMode.NumbersAndPunctuation
					}
					
					Label {
					    visible: (!(weightEdit.text>0))
					    textStyle {
					        color: Color.Red
					        fontSize: FontSize.Small
					    }
					    text: "Please enter the baby's weight" 
					}
		
					Label {
					    text: qsTr("Height (cm)")
					}
		
					TextField {
					    id: heightEdit
					    hintText: "height"
					    inputMode: TextFieldInputMode.NumbersAndPunctuation
					}
		
					Label {
					    visible: (!(heightEdit.text>0))
					    textStyle {
					        color: Color.Red
					        fontSize: FontSize.Small
					    }
					    text: "Please enter the baby's height" 
					}

					Label {
					    text: qsTr("Cephalic perimeter (cm)")
					}
		
					TextField {
						id: cephalicEdit
						hintText: "cephalic perimeter"
						inputMode: TextFieldInputMode.NumbersAndPunctuation
					}
		
					Label {
					    visible: (!(cephalicEdit.text>0))
					    textStyle {
					        color: Color.Red
					        fontSize: FontSize.Small
					    }
					    text: "Please enter the baby's cephalic perimeter" 
					}
		        }


	        }
	
	        Divider {
            }	
	
	        Container {
	            id: recurrenceContainer
	            layout: StackLayout {
	                orientation: LayoutOrientation.TopToBottom            
	            }
	
		        leftPadding: 10
		        topPadding: 10
		        rightPadding: 10
		        bottomPadding: 10

				Label {
				    text: qsTr("Recurrence")
		            textStyle {
		                fontSize: FontSize.Large
		            }
				}
	
		        DateTimePicker {
		            title: "End date" 
		            id: endDateField
		            minimum: startDateField.value
		        }
	
				Label {
				    text: qsTr("Repeat in (hours)")
				}
	
				TextField {
				    id: intervalField
				    hintText: "Hours"
				    text: "24"
					inputMode: TextFieldInputMode.NumbersAndPunctuation
				}

				Label {
				    visible: ( ((!(intervalField.text>0)) && (intervalField.text!="0")) || (intervalField.text.indexOf(".")>=0) )
				    textStyle {
				        color: Color.Red
				        fontSize: FontSize.Small
				    }
				    text: "Please enter the recurrence period in hours" 
				}
	        }

        }
        
    }

    actions: [
        ActionItem {
            title: "Save"
            imageSource: "asset:///images/ic_done.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            enabled: validateForm()
            
            onTriggered: {
                save();
                navigationPane.pop();
            }
        },
        
        ActionItem {
            title: "Remove event"
            imageSource: "asset:///images/ic_delete.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            enabled: (eventField.enabled==false)           
            
            onTriggered: {
                deleteEventDialog.show();
            }
        }
    ]
    
    attachedObjects: [
        SystemDialog {
            id: deleteEventDialog
            title: "Please confirm..."
            body: "Remove this event?"
            
            onFinished: {
                if (deleteEventDialog.result == 2) {
                    deleteEvent();
                    navigationPane.pop();
                }
            }
        }
    ] 
}
