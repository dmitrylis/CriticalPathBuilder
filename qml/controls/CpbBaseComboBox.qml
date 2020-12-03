import QtQuick 2.15
import QtQuick.Templates 2.15

ComboBox {
    id: root

    property string placeholderText: ""

    readonly property var currentData: {
        if (Array.isArray(root.model)) {
            return root.model[root.currentIndex]
        }
        return root.model.get(root.currentIndex)
    }

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
