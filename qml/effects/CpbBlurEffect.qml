import QtQuick 2.15
import QtGraphicalEffects 1.12

GaussianBlur {
    id: root

    radius: 30
    samples: radius * 2
    cached: true
}
