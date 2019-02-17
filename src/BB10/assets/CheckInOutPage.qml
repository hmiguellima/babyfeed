import bb.cascades 1.0
import bb.system 1.0

Page {
    id: checkInOutScreen
    objectName: "checkInOutScreen"

    property alias eventIndex: eventField.selectedIndex
    property alias timerText: timerLabel.text
    property bool running: false
    
    signal startClicked()
    signal stopClicked()
        
    onCreationCompleted: {
        console.debug("qml:checkInOutPageLoaded");
    }

    function setTitle(title) {
        pageTitle.title=title;
        console.debug("setTitle:"+title);
    }
    
    titleBar: TitleBar {
        id: pageTitle
    }
    
    content: Container {
        layout: DockLayout {}

        DropDown {
            id: eventField
            enabled: (running==false)
            title: "Feeding event"
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

            onSelectedIndexChanged: {
            }
        }
                        
        Label {
            id: timerLabel
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            topPadding: 30
            
            text: "00:00"
            textStyle {
                fontSize: FontSize.PointValue
                fontSizeValue: 50
            }
        }
    }
    
    actions: [
        ActionItem {
            title: "Start"
            enabled: (running==false)
            imageSource: "asset:///images/play.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                startClicked();
            }
        },
        ActionItem {
            title: "Stop"
            enabled: (running==true)
            imageSource: "asset:///images/ic_done.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                stopClicked();
                navigationPane.pop();
            }
        }
    ]
}