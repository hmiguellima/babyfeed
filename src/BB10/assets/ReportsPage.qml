import bb.cascades 1.0

Page {
    id: reportScreen
    objectName: "reportScreen"

    property string gender: "boy"

    signal htmlLoaded(int type)

    onCreationCompleted: {
        console.debug("qml:ReportsPageLoaded");
    }

    function setTitle(title) {
        pageTitle.title=title;
        console.debug("setTitle:"+title);
    }
    
    titleBar: TitleBar {
        id: pageTitle
    }

    content: Container {
        leftPadding: 10
        topPadding: 10

        SegmentedControl {
            id: chartType
            options: [
                Option {
                    text: "Height"
                    value: "h"
                    selected: true
                },
                Option {
                    text: "Weight"
                    value: "w"
                },
                Option {
                    text: "Cephalic"
                    value: "c"
                }
            ]
            
            onSelectedValueChanged: {
                switch (selectedIndex) {
                    case 0:
                        htmlContainer.url = "local:///assets/html/height_" + gender + ".html";
                        break;
                    case 1:
                        htmlContainer.url = "local:///assets/html/weight_" + gender + ".html";
                        break;
                    case 2:
                        htmlContainer.url = "local:///assets/html/cephalic_" + gender + ".html";
                        break;
                }
            }
        }
        
        WebView {
            id: htmlContainer
            url: "local:///assets/html/height_" + gender + ".html";
            onLoadingChanged: {
                if (loadRequest.status == WebLoadStatus.Succeeded)    
                    htmlLoaded(chartType.selectedIndex);                    
            }
        }       

    }
    
    /*
    actions: [
        ActionItem {
            title: "Settings"
            imageSource: "asset:///images/ic_settings.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                settingsSheet.open();
            }
        }
    ]
    */
    
    
    attachedObjects: [
        Sheet {
            id: settingsSheet
            
            content: Page {
                titleBar: TitleBar {
                    title: "Growth chart settings"
                    
                    acceptAction: ActionItem {
                        title: "Ok"
                        
                        onTriggered: {
                            settingsSheet.close();
                        }
                    }
                }
                
                content: Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.TopToBottom            
                    }
                    
                    leftPadding: 10
                    topPadding: 10
                    
                    DropDown {
                        id: unitTypeField
                        title: "Weight units"
                        selectedIndex: 0
                        
                        Option {
                            text: "Kilograms"
                        }
                        
                        Option {
                            text: "Pounds"
                        }
                    }
                }
            }
        }
    ]

    function setChartData(data) {
        htmlContainer.postMessage(data);
        console.debug("setChartData:"+data);
    }
}
