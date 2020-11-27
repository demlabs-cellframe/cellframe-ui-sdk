import QtQuick 2.0
import "qrc:/"

Item {
    FontLoader{ id: fontThin;       source: "qrc:/resources/fonts/Blinker/Blinker-Thin.ttf"         }
    FontLoader{ id: fontExtraLight; source: "qrc:/resources/fonts/Blinker/Blinker-ExtraLight.ttf"   }
    FontLoader{ id: fontLight;      source: "qrc:/resources/fonts/Blinker/Blinker-Light.ttf"        }
    FontLoader{ id: fontRegular;    source: "qrc:/resources/fonts/Blinker/Blinker-Regular.ttf"      }
    FontLoader{ id: fontBold;       source: "qrc:/resources/fonts/Blinker/Blinker-Bold.ttf"         }
    FontLoader{ id: fontSemiBold;   source: "qrc:/resources/fonts/Blinker/Blinker-SemiBold.ttf"     }
    FontLoader{ id: fontExtraBold;  source: "qrc:/resources/fonts/Blinker/Blinker-ExtraBold.ttf"    }
    FontLoader{ id: fontBlack;      source: "qrc:/resources/fonts/Blinker/Blinker-Black.ttf"        }

    property font regular11: Qt.font({ family: fontRegular.name, pixelSize: 11*pt })
    property font regular12: Qt.font({ family: fontRegular.name, pixelSize: 12*pt })
    property font regular14: Qt.font({ family: fontRegular.name, pixelSize: 14*pt })
    property font regular16: Qt.font({ family: fontRegular.name, pixelSize: 16*pt })
    property font regular18: Qt.font({ family: fontRegular.name, pixelSize: 18*pt })
    property font regular24: Qt.font({ family: fontRegular.name, pixelSize: 24*pt })
    property font regular26: Qt.font({ family: fontRegular.name, pixelSize: 26*pt })
    property font regular28: Qt.font({ family: fontRegular.name, pixelSize: 28*pt })

    property font semiBold12: Qt.font({ family: fontSemiBold.name, weight: Font.DemiBold, pixelSize: 12*pt })
    property font semiBold14: Qt.font({ family: fontSemiBold.name, weight: Font.DemiBold, pixelSize: 14*pt })
    property font semiBold16: Qt.font({ family: fontSemiBold.name, weight: Font.DemiBold, pixelSize: 16*pt })
    property font semiBold18: Qt.font({ family: fontSemiBold.name, weight: Font.DemiBold, pixelSize: 18*pt })
}
