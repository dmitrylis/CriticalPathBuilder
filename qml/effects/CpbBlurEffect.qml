import QtQuick 2.11
import QtGraphicalEffects 1.0

GaussianBlur {
    id: root

    radius: 30
    samples: radius * 2
    cached: true
}
