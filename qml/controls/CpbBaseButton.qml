import QtQuick 2.15
import QtQuick.Templates 2.15

Button {
    id: root

    states: [
        State {
            name: "normal"
            when: !root.checked && !root.down && !root.hovered && root.enabled
        },
        State {
            name: "normal_hovered"
            when: !root.checked && !root.down && root.hovered && root.enabled
        },
        State {
            name: "normal_down"
            when: !root.checked && root.down && root.hovered && root.enabled
        },
        State {
            name: "checked"
            when: root.checked && !root.down && !root.hovered && root.enabled
        },
        State {
            name: "checked_hovered"
            when: root.checked && !root.down && root.hovered && root.enabled
        },
        State {
            name: "checked_down"
            when: root.checked && root.down && root.hovered && root.enabled
        },
        State {
            name: "normal_disabled"
            when: !root.checked && !root.enabled
        },
        State {
            name: "checked_disabled"
            when: root.checked && !root.enabled
        }
    ]
}
