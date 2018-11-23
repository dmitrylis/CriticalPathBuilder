import QtQuick 2.11
import QtQuick.Templates 2.4

Button {
    id: root

    states: [
        State {
            name: "normal"
            when: !root.checked && !root.down
        },
        State {
            name: "normal_down"
            when: !root.checked && root.down
        },
        State {
            name: "checked"
            when: root.checked && !root.down
        },
        State {
            name: "checked_down"
            when: root.checked && root.down
        }
    ]
}
