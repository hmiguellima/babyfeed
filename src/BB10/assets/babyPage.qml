import bb.cascades 1.0
import bb.system 1.0

Page {
    id: babyScreen
    objectName: "babyScreen"

    signal prevDateClicked()
    signal nextDateClicked()
    signal prevMonthClicked()
    signal nextMonthClicked()
    signal dateChanged(int ano, int mes, int dia)
    signal uncheckEventClicked(int index)
    signal checkEventClicked(int index)
    signal editEventClicked(int eventId)
    signal deleteEventClicked(int eventId)
    signal timerEventClicked()
    signal manualEventClicked()
    signal reportsClicked()
    signal deleteBaby()
    signal capturePhotoClicked()
    signal saveBaby()
    signal cancel()

    property string photoUrl: "asset:///images/baby_boy_icon.png"
    property alias name: babyNameField.text
    property alias birthday: birthdayField.value
    property alias age: babyAgeLabel.text
    property alias measures: babyMeasuresLabel.text 
    property alias gender: genderField.selectedIndex
    property alias timerEnabled: timerEnabledField.checked
    property alias minutes: minutesField.text
    property int babyId 
    property alias currentDate: currentDateLabel.text
    
    onCreationCompleted: {
        console.debug("qml:babyPageLoaded");
    }

    function setTitle(title) {
        //pageTitle.title=title;
        console.debug("setTitle:"+title);
    }
    
    function newBaby() {
        editBabySheet.title = "New baby";
        editBabySheet.open();      
    }

    /*
    titleBar: TitleBar {
        id: pageTitle
    }
    */

    content: Container {
        layout: DockLayout {}

        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            topPadding: 400

	        ListView {
	            id: eventsList
	            dataModel: eventsModel
	
	            onTriggered: {
	                var eventItem=dataModel.data(indexPath);
	                var eventId = eventItem.id;
	                
	                if (eventId!=-1)
	                    editEventClicked(eventId);                
	            }
	
	            layout: StackListLayout {
	                headerMode: ListHeaderMode.None
	            }
	
	            listItemComponents: [
	                ListItemComponent {
	                    StandardListItem {
	                        id: eventsListItem
	                        title: ListItemData.desc
	                        imageSource: ListItemData.iconUrl
	                        
	                        contextActions: [
	                            ActionSet {
                                    title: "Event"
                                    
                                    ActionItem {
                                        title: "Delete"
                                        imageSource: "asset:///images/ic_delete.png"
                                        enabled: (ListItemData.id!=-1)
                                        onTriggered: {
	                                       var eventId = ListItemData.id;

                                           eventsListItem.ListItem.view.fireEventDeleteEvent(eventId);                                           
                                        }
                                    }
                                }
	                        ]
	                    }
			         }
		        ]
		        
			    function fireEventDeleteEvent(eventId) {
			        deleteEventDialog.eventId=eventId;
			        deleteEventDialog.show();
			    }
		    }
        }	        
	    
        Container {
            verticalAlignment: VerticalAlignment.Top
            horizontalAlignment: HorizontalAlignment.Fill
            bottomMargin: 1
            background: Color.Yellow
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom            
            }
            
	        // Baby Header
	        
	        Container {
	            layout: DockLayout {}
	            horizontalAlignment: HorizontalAlignment.Fill
	            leftPadding: 10
	            topPadding: 10
                background: Color.create("#F0F0F0")        
	            
	            Container {
	                horizontalAlignment: HorizontalAlignment.Fill
	                verticalAlignment: VerticalAlignment.Fill
	                
	                leftPadding: 200
	                topMargin: 5
	                
	                layout: StackLayout {
	                    orientation: LayoutOrientation.TopToBottom            
	                }
	                Label {
	                    text: name
	                    textStyle {
                            fontSize: FontSize.XLarge
                        }
	                }
	                Label {
	                    id: babyAgeLabel
	                    text: "0 years"
	                }
	                Label {
	                    id: babyMeasuresLabel
	                    text: "W: 0, H: 0, C: 0"
	                }
	            }
	            
	            Container {
	                horizontalAlignment: HorizontalAlignment.Left
	                verticalAlignment: VerticalAlignment.Fill
	                background: Color.LightGray
	                leftPadding: 5
	                topPadding: 5
	                rightPadding: 5
	                bottomPadding: 5
	                preferredHeight: 250
	                preferredWidth: 190

		            ImageButton {
                        defaultImageSource: photoUrl
                        pressedImageSource: photoUrl
		                minHeight: 240
		                maxHeight: 240
		                minWidth: 180
		                maxWidth: 180
		                
		                onClicked: {
		                    editBabySheet.open();
		                }
		            }
	            }     
	            
	        }

            // Date Filter
            
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 10
                bottomPadding: 0
                layout: DockLayout {}
                background: Color.create("#F0F0F0")        

                Container {
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Left

                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight            
                    }

	                Button {
	                    leftMargin: 0
	                    rightMargin: 0
	                    maxWidth: 14
	                    text: "<<"
	                    onClicked: {
	                        prevMonthClicked();
	                    }
	                }
	
	                Button {
	                    leftMargin: 0
	                    rightMargin: 0
	                    maxWidth: 18
	                    text: "<"
	                    onClicked: {
	                        prevDateClicked();
	                    }
	                }
                }
                
                Container {
                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Center
                    background: Color.Yellow
                    leftPadding: 5
                    rightPadding: 5
                    
                    layout: DockLayout {}

	                Label {
	                    verticalAlignment: VerticalAlignment.Center
	                    horizontalAlignment: HorizontalAlignment.Center
	                    
	                    id: currentDateLabel
	                    text: "2013/01/01"
	                    textStyle {
	                        fontSize: FontSize.Medium
	                        fontWeight: FontWeight.Bold
	                    }
	                }
                }


                Container {
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Right
                    leftMargin: 0
                    rightMargin: 0
                    leftPadding: 0
                    rightPadding: 0

                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight            
                    }

	                Button {
	                    leftMargin: 0
	                    rightMargin: 0
	                    maxWidth: 18
	                    text: ">"
	                    onClicked: {
	                        nextDateClicked();
	                    }
	                }

	                Button {
	                    leftMargin: 0
	                    rightMargin: 0
	                    maxWidth: 14
	                    text: ">>"
	                    onClicked: {
	                        nextMonthClicked();
	                    }
	                }
	            }
            }

            Divider {}
        }
	    
    } 
    
    actions: [
        ActionItem {
            title: "Timer event"
            imageSource: "asset:///images/timer_icon.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                timerEventClicked();
            }
        },
        ActionItem {
            title: "Custom event"
            imageSource: "asset:///images/new_event_icon.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                manualEventClicked();
            }
        },
        ActionItem {
            title: "Charts"
            imageSource: "asset:///images/chart_icon.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                reportsClicked();
            }
        },
        ActionItem {
            title: "Edit baby"
            imageSource: "asset:///images/ic_edit.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                editBabySheet.open();
            }
        },
        ActionItem {
            title: "Remove baby"
            imageSource: "asset:///images/ic_delete.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            
            onTriggered: {
                deleteBabyDialog.show();
            }
        }
    ]

    
    attachedObjects: [
        SystemDialog {
            id: deleteBabyDialog
            title: "Please confirm..."
            body: "Remove this baby?"
            
            onFinished: {
                if (deleteBabyDialog.result == 2) {
                    deleteBaby();
                    navigationPane.pop();
                }
            }
        }, 
        
        SystemDialog {
            id: deleteEventDialog
            title: "Please confirm..."
            body: "Remove this event?"
            
            property int eventId
            
            onFinished: {
                if (deleteEventDialog.result == 2) {
                    deleteEventClicked(deleteEventDialog.eventId);
                }
            }
        }, 

        Sheet {
            id: editBabySheet
            property alias title: title.title
            
            content: Page {
                titleBar: TitleBar {
                    id: title
                    
                    acceptAction: ActionItem {
                        title: "Save"
                        enabled: ((name!="") && (minutesField.text >0))
                        
                        onTriggered: {
                            editBabySheet.close();
                            saveBaby();
                        }
                    }
                    
                    dismissAction: ActionItem {
                        title: "Cancel"
                        
                        onTriggered: {
                            editBabySheet.close();
                            if (babyId==-1)
                                navigationPane.pop();
                            else
                                cancel();
                        }
                    }
                }
                
                content: ScrollView {
			        scrollViewProperties {
			            scrollMode: ScrollMode.Vertical
			        }
        
                    Container {
	                    layout: StackLayout {
	                        orientation: LayoutOrientation.TopToBottom
	                        
	                    }
	                    
	                    leftPadding: 20.0
	                    topPadding: 20.0
	                    rightPadding: 20.0
	                    bottomPadding: 20.0
	
			            Container {
			                horizontalAlignment: HorizontalAlignment.Left
			                verticalAlignment: VerticalAlignment.Fill
			                background: Color.LightGray
			                leftPadding: 5
			                topPadding: 5
			                rightPadding: 5
			                bottomPadding: 5
			                preferredHeight: 250
			                preferredWidth: 190
	
		                    ImageButton {
		                        id: photoBtn
		                        defaultImageSource: photoUrl
		                        pressedImageSource: photoUrl
				                minHeight: 240
				                maxHeight: 240
				                minWidth: 180
				                maxWidth: 180
		                        
		                        onClicked: {
		                            babyScreen.capturePhotoClicked();
		                        }
		                    }
	                    }
	                    
	                    TextField {
	                        id: babyNameField
	                        text: name
	                        hintText: "Name"
	                    }
	
						Label {
						    visible: (name=="")
						    textStyle {
						        color: Color.Red
						        fontSize: FontSize.Small
						    }
						    text: "Please enter the baby's name" 
						}
	
	                    DateTimePicker {
	                        title: "Birthday" 
	                        id: birthdayField
	                    }
	
	                    DropDown {
	                        id: genderField
	                        title: "Gender"
	                        
	                        Option {
	                            text: "Boy"
	                        }
	                        
	                        Option {
	                            text: "Girl"
	                        }
	                        
	                        onSelectedIndexChanged: {
	                            if (babyId==-1) {
	                                if (selectedIndex==0)
	                                    photoUrl="asset:///images/baby_boy_icon.png";
	                                else                                    
	                                    photoUrl="asset:///images/baby_girl_icon.png";
	                            }
	                        }
	                    }
	
	                    Divider { }
	                    
	                    Label {
	                        text: "Timer alarms"
	                    }
	
	                    ToggleButton {
	                        id: timerEnabledField
	                    }
	                    
	                    Label {
	                        text: "Minutes between feeds"
	                    }
	                    
	                    TextField {
	                        id: minutesField
	                        inputMode: TextFieldInputMode.NumbersAndPunctuation
	                        hintText: "minutes"
	                    }
	                    
						Label {
						    visible: (!(minutesField.text>0) || (minutesField.text.indexOf(".")>=0) )
						    textStyle {
						        color: Color.Red
						        fontSize: FontSize.Small
						    }
						    text: "Please enter the minutes between feeds" 
						}
	                    
                    }        
                }
            }
        }
    ]
}
