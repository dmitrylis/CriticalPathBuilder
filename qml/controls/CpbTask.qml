import QtQuick 2.11

import "../singletons"

Item {
    function rand(min,max,num){
          return Math.floor(Math.floor(Math.random()*(max-min+1)+min) / num) * num;
    }

    x: rand(0, 1500, 100)
    y: rand(0, 300, 100)
    width: rand(100, 400, 100)
    height: 100 

    Rectangle {
        anchors {
            fill: parent
            margins: CpbStyle.marginTiny
        }
    }
}
