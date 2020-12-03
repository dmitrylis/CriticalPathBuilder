import QtQuick 2.15

CpbTextInput {
    id: root

    onPressed: {
        _tooltipManager.showEmployeTooltip(root)
    }
}
