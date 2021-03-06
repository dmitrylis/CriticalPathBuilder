import QtQuick 2.15
import QtQuick.Templates 2.15

TextField {
    id: root

    selectByMouse: true

    states: [
        State {
            name: "no_text"
            when: root.text === "" && root.enabled && !root.focus && !root.activeFocus
        },
        State {
            name: "has_text"
            when: root.text !== "" && root.enabled && !root.focus && !root.activeFocus
        },
        State {
            name: "focused"
            when: root.enabled && (root.focus || root.activeFocus)
        },
        State {
            name: "no_text_disabled"
            when: root.text === "" && !root.enabled
        },
        State {
            name: "has_text_disabled"
            when: root.text !== "" && !root.enabled
        }
    ]
}
