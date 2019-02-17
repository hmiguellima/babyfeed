import bb.cascades 1.0
import bb.system 1.0

NavigationPane {
    id: navigationPane
    
    signal screenLoaded(string name)
    signal aboutClicked()
    signal backupClicked()
    signal restoreClicked()
    signal helpClicked()
    signal langClicked(string lang)
    signal exportClicked(string email)
    
    attachedObjects: [
        ComponentDefinition {
            id: mainPage;
            source: "asset:///mainPage.qml";
        },
        
        ComponentDefinition {
            id: babyPage;
            source: "asset:///babyPage.qml";
        },
        
        ComponentDefinition {
            id: checkInOutPage;
            source: "asset:///CheckInOutPage.qml";
        },
        
        
        ComponentDefinition {
            id: manualEventPage;
            source: "asset:///ManualEventPage.qml";
        },
        
        ComponentDefinition {
            id: reportsPage;
            source: "asset:///ReportsPage.qml";
        },
        
        SystemToast {
	         id: messageBox
        }    
    ]

    onTopChanged: {
        console.debug("qml:onTopChanged:"+page.objectName);
        navigationPane.screenLoaded(page.objectName);
    }

    onPopTransitionEnded: {
        page.destroy();
        console.debug("qml:onPopTransitionEnded:"+page.objectName);
    }
    
    function showMessageBox(message) {
        messageBox.body=message;
        messageBox.show();        
    }
    
    function showScreen(name) {
        var newPage=null;
        
        console.debug("qml:showScreen:"+name);
        
        switch (name) {
            case "main": 
                newPage = mainPage.createObject();
                break;
            case "baby": 
                newPage = babyPage.createObject();
                break;
            case "checkinout": 
                newPage = checkInOutPage.createObject();
                break;
            case "manualevent": 
                newPage = manualEventPage.createObject();
                break;
            case "reports": 
                newPage = reportsPage.createObject();
                break;
        }

        if (newPage!=null)
            navigationPane.push(newPage);
    }
}
