import QtQuick 2.5
import QOmdb 1.0

Item {
    width: 240
    height: 480
    QOmdb {
        id: omdb
        title: "Back to the Future"
        plot: QOmdb.Short

        onFinished: {
            if(isJson) {
                var data = JSON.parse(doc)
                for (var key in data) {
                    listview.model.append({"key": key, "info": data[key]})
                }
            }
        }
    }

    ListModel {
        id: samplemodel
    }

    ListView {
        id: listview
        model: samplemodel
        anchors.fill: parent
        delegate: Row {
            Text { text: key }
            Text { text: " -> " }
            Text { text: info }
        }
    }

    Component.onCompleted: omdb.fetch()
} 
