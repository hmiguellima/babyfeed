import bb.cascades 1.0
import bb.system 1.0

Page {
    id: mainScreen
    objectName: "mainScreen"    

    signal showBabyPage(int babyId)
    signal deleteBabyClicked(int babyId)

    onCreationCompleted: {
        console.debug("qml:mainPageLoaded");
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
        
        ListView {
            id: babiesList
            verticalAlignment: VerticalAlignment.Fill
            dataModel: babiesModel

            onTriggered: {
                var babyItem=dataModel.data(indexPath);

                showBabyPage(babyItem.id);
            }

            layout: StackListLayout {
                headerMode: ListHeaderMode.None
            }

            listItemComponents: [
		        ListItemComponent {
		            Container {
		                id: babiesListItem
		                
		                background: buttonBack.imagePaint
		                
		                layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom      
                        }

					    attachedObjects: [
					        ImagePaintDefinition {
					            id:buttonBack
					            repeatPattern: RepeatPattern.X
					            imageSource: "asset:///images/baby_button.png"
					        }
					    ]

				        Container {
				            layout: DockLayout {}
				            leftPadding: 10
				            topPadding: 10
				            bottomMargin: 10
				            
				            Container {
				                horizontalAlignment: HorizontalAlignment.Left
				                verticalAlignment: VerticalAlignment.Fill
				                background: Color.LightGray
				                leftPadding: 5
				                topPadding: 5
				                rightPadding: 5
				                preferredHeight: 250
				                preferredWidth: 190
				                visible: (ListItemData.id!="-1")
			
					            ImageView {
					                imageSource: ListItemData.photoUrl
					                minHeight: 240
					                maxHeight: 240
					                minWidth: 180
					                maxWidth: 180
					            }
				            }     
				            
				            Container {
				                horizontalAlignment: HorizontalAlignment.Fill
				                verticalAlignment: VerticalAlignment.Fill
				                
				                leftPadding: (ListItemData.id!="-1"?200:0)
				                topMargin: 5
				                
				                layout: StackLayout {
				                    orientation: LayoutOrientation.TopToBottom            
				                }
				                Label {
				                    text: ListItemData.name
				                    textStyle {
			                            fontSize: FontSize.XLarge
			                        }
				                }
				                Label {
				                    id: babyAgeLabel
				                    visible: (ListItemData.id!="-1")
				                    text: ListItemData.age
				                }
				                Label {
				                    id: babyMeasuresLabel
				                    visible: (ListItemData.id!="-1")
				                    text: ListItemData.measures
				                }
				            }
				        }

			            Divider {
			            }
			            
			            contextActions: [
                            ActionSet {
                                title: "Baby"
                                
                                ActionItem {
                                    title: "Delete"
                                    imageSource: "asset:///images/ic_delete.png"
                                    enabled: (ListItemData.id!=-1)
                                    onTriggered: {
                                       var babyId = ListItemData.id;

                                       babiesListItem.ListItem.view.fireDeleteBaby(babyId);                                           
                                    }
                                }
                            }
			            ]
		            }
		        }
	        ]
	        
		    function fireDeleteBaby(babyId) {
		        deleteBabyDialog.babyId=babyId;
		        deleteBabyDialog.show();
		    }
	    }
    }
    
    actions: [
        ActionItem {
            title: "New baby"
            imageSource: "asset:///images/ic_add.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                showBabyPage(-1);
            }
        },
        
        ActionItem {
            title: "About"
            imageSource: "asset:///images/ic_info.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                aboutSheet.open();
            }
        }
    ]
    
    attachedObjects: [
        Sheet {
            id: aboutSheet
            
            content: Page {
                titleBar: TitleBar {
                    title: "About & Disclaimer"
                    
                    acceptAction: ActionItem {
                        title: "Ok"
                        
                        onTriggered: {
                            aboutSheet.close();
                        }
                    }
                }
                
                content: WebView {
                    url: "local:///assets/html/about.html";
                }
            }
        },
        
        SystemDialog {
            id: deleteBabyDialog
            title: "Please confirm..."
            body: "Remove this baby?"
            
            property int babyId
            
            onFinished: {
                if (deleteBabyDialog.result == 2) {
                    deleteBabyClicked(deleteBabyDialog.babyId);
                }
            }
        } 
        
    ]
    
}
