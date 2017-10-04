import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import GOL 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Game of life")

    Row {
        anchors.fill: parent
        Column {
            Button {
                id: startButton
                width: 100
                text: timer.running ? "Stop" : "Start"
                onClicked: timer.running = !timer.running
            }
            Button {
                width: 100
                text: "Step"
                onClicked: gol.step()
            }
            Button {
                width: 100
                text: "Reset"
                onClicked: gol.reset()
            }
            Label {
                text: "Speed: "+(101-timer.interval)
            }

            Slider {
                id: speedSlider
                width: 100
                from: 1
                to: 100
                stepSize: 1
                live: true
                value: 10
            }
            Label {
                text: "Size: "+gol.size
            }

            Slider {
                id: sizeSlider
                width: 100
                from: 32
                to: 512
                live: true
                value: 32
            }
        }
        GOL {
            id: gol
            width: Math.min(parent.width-startButton.width, parent.height)
            height: width
            size: sizeSlider.value
        }
    }

    Timer {
        id: timer
        repeat: true
        interval: 101-speedSlider.value
        onTriggered: gol.step()
    }
}
