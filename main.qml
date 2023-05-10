import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import my_types.test.t 1.0
Window {
    color: "#FAFAFA"
    minimumWidth: 380
    maximumWidth: 380
    minimumHeight: 800
    maximumHeight: 800
    property bool bg2: false
    function enableWeight(is) {
        l1.visible = is
        editSize.visible = is
        bg2 = is
    }

    visible: true
    title: qsTr("Рюкзак калькулятор")
    ColumnLayout {
        anchors.fill:parent
        spacing: 30
        Rectangle {
            id: settingsArea
            border { width:1; color:"green" }
            Layout.leftMargin: 40
            Layout.topMargin: 40
            width:300
            height:230
            Grid {
                anchors.centerIn: parent
                spacing: 20
                width:250
                height:150
                columns: 2
                Label {
                    text: qsTr("Тип")
                }
                ComboBox {
                    id: limitEdit
                    model: ["Неограничен.", "Ограничен."]
                    onCurrentIndexChanged : {
                        uniqueEdit.visible = currentIndex == 1
                        uniqueLabel.visible = currentIndex == 1
                    }
                }

                Label {
                    visible:false
                    id: uniqueLabel
                    text: qsTr("Уникальные(1-0)")
                }
                CheckBox {
                    id: uniqueEdit
                    visible:false
                }

                Label {
                    text: qsTr("Количество рюкзаков")
                }
                ComboBox {
                    model: ["1"]
                }
                Label {
                    text: qsTr("Количество аргументов")
                }
                ComboBox {
                    id: bugArgEdit
                    model: ["1","2"]
                }
                Item { width:1; height:1 }
                Button {
                    text: qsTr("Далее")
                    width: 80
                    height:30
                    onClicked: {
                        bt1.enabled = true
                        bt2.enabled = true
                        settingsArea.enabled = false
                        editArea.enabled = true
                        if(bugArgEdit.currentIndex == 0) {
                            enableWeight(false)
                            if(uniqueEdit.checked) {
                                mainView.model = MainModel1_0_1
                                return
                            }
                            if(limitEdit.currentIndex === 0) {
                                mainView.model = MainModelUnlimited_1
                                return
                            }
                            if(limitEdit.currentIndex === 1) {
                                mainView.model = MainModelLimited_1
                                return
                            }
                        }else {
                            enableWeight(true)
                            if(uniqueEdit.checked) {
                                mainView.model = MainModel1_0_2
                                return
                            }
                            if(limitEdit.currentIndex === 0) {
                                mainView.model = MainModelUnlimited_2
                                return
                            }
                            if(limitEdit.currentIndex === 1) {
                                mainView.model = MainModelLimited_2
                                return
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            enabled: false
            id: editArea
            width:300
            height:400
            border { width:1; color:"green" }
            Layout.leftMargin: 40
            ColumnLayout {
                anchors.fill: parent
                Item { height: 10}
                spacing:10
                RowLayout {
                    Layout.leftMargin: 25
                    width: 200
                    height: 30

                    Button {
                        width: 80
                        height:30
                        text: qsTr("Добавить")
                        onClicked: {
                            mainView.model.push()
                        }
                    }
                    Button {
                        width: 80
                        height:30
                        text: qsTr("Удалить")
                        onClicked: {
                            if(mainView.currentIndex !== -1)
                                mainView.model.remove(mainView.currentIndex)
                        }
                    }
                    Item {Layout.fillWidth: true}
                }
                RowLayout {
                    Layout.leftMargin: 85
                    width: 200
                    height: 30
                    spacing: 0
                    Repeater {
                        model: mainView.model.columnCount() === 2 ? ["Стоим.","Вес"]
                             : mainView.model.columnCount() === 3 ? ["Стоим.", bg2 ? "Вес" : "Кол.", "Размер"]
                                                                  : ["Стоим.", "Кол.", "Вес", "Размер"]
                        Label {
                            Layout.minimumWidth: (200 / mainView.model.columnCount())
                            text: modelData
                        }
                    }
                }
                Rectangle {
                Layout.alignment: Qt.AlignHCenter
                border { width:1; color:"black" }
                    width:250
                    height:275
                    ScrollView {
                        anchors.fill: parent
                        ListView {
                            width:250
                            height:275
                            id: mainView
                            model: 0
                            delegate: Row {
                                property alias inputs: inputModel
                                    Rectangle {
                                        width: 50
                                        height: 20
                                        border { width:1; color: "#aaa" }
                                        color: "gray"
                                        Text {
                                            anchors.centerIn: parent
                                            text: index + 1
                                            color:"white"
                                        }
                                        MouseArea {
                                            hoverEnabled: true
                                            anchors.fill: parent
                                            onClicked: mainView.currentIndex = index
                                        }
                                    }

                                Repeater {
                                    id: inputModel
                                    model: (mainView.model.columnCount() === 2) ? [arg1,arg2]
                                         : (mainView.model.columnCount() === 3) ? [arg1,arg2,arg3] : [arg1,arg2,arg3,arg4]
                                    TextField {
                                        width: (200 / mainView.model.columnCount())
                                        text: modelData
                                        horizontalAlignment: TextInput.AlignHCenter
                                    }
                                }
                            }
                            highlight: Rectangle {
                                   z:3
                                   color:"#20000000"
                            }
                            focus: true
                            clip:true
                        }
                    }
                }
                RowLayout {
                    width: 200
                    height: 30
                    Item {Layout.fillWidth: true}
                    Label {  text: qsTr("Масса рюкзака") }

                    TextField {
                       horizontalAlignment: TextInput.AlignHCenter
                       id: editWeight
                       Layout.maximumWidth: 50
                       text: "0"
                    }
                    Label { id: l1; text: qsTr("Объем рюкзака") }
                    TextField {
                       horizontalAlignment: TextInput.AlignHCenter
                       id: editSize
                       Layout.maximumWidth: 50
                       text: "0"
                    }
                    Item {Layout.fillWidth: true}
                }
                Item {Layout.fillHeight: true}
            }
        }

        RowLayout {
            width: 300
            height: 70
            spacing:10
            Layout.leftMargin: 40
            Button {
                width: 80
                height:30
                id: bt1
                enabled: false
                text: qsTr("Результат")
                onClicked: {
                    for(var i=0;i < mainView.model.rowCount();i++) {
                        if(mainView.model.columnCount() === 2)
                            mainView.model.update(i, mainView.itemAtIndex(i).inputs.itemAt(0).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(1).text)
                        if(mainView.model.columnCount() === 3)
                            mainView.model.update(i, mainView.itemAtIndex(i).inputs.itemAt(0).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(1).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(2).text)
                        if(mainView.model.columnCount() === 4)
                            mainView.model.update(i, mainView.itemAtIndex(i).inputs.itemAt(0).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(1).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(2).text,
                                                     mainView.itemAtIndex(i).inputs.itemAt(3).text)
                    }
                    if(bg2)
                        mainView.model.setBg(editWeight.text,editSize.text)
                    else
                        mainView.model.bgWeight = editWeight.text
                    answer.text = mainView.model.getResult()
                    answer.color = "red"
                }
            }
            Button {
                width: 80
                height:30
                id: bt2
                enabled: false
                text: qsTr("Сброс настроек")
                onClicked: {
                    bt1.enabled = false
                    bt2.enabled = false
                    settingsArea.enabled = true
                    editArea.enabled = false
                    mainView.model.reset();
                    mainView.model = 0
                    answer.text = "-"
                }
            }

            Label {
                text: qsTr("Макс:")
            }
            Rectangle {
                width:90
                height:20
                border {width:1; color: "green" }
                Label {
                    anchors.centerIn: parent
                    id: answer
                    text: "-"
                }
            }
            Item { Layout.fillWidth: true }
        }

        Item{Layout.fillHeight: true}
    }
}
