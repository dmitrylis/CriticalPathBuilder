import QtQuick 2.11
import QtQuick.Templates 2.4

ComboBox {
    id: root

    property string placeholderText: ""

    states: [
        State {
            name: "normal"
            when: !root.pressed && root.enabled && !root.focus && !root.activeFocus && !root.popup.visible
        },
        State {
            name: "focused"
            when: !root.pressed && root.enabled && (root.focus || root.activeFocus) && !root.popup.visible
        },
        State {
            name: "focused_pressed"
            when: root.pressed && root.enabled && (root.focus || root.activeFocus) && !root.popup.visible
        },
        State {
            name: "expanded"
            when: !root.pressed && root.enabled && (root.focus || root.activeFocus) && root.popup.visible
        },
        State {
            name: "expanded_pressed"
            when: root.pressed && root.enabled && (root.focus || root.activeFocus) && root.popup.visible
        },
        State {
            name: "disabled"
            when: !root.enabled
        }
    ]
}
