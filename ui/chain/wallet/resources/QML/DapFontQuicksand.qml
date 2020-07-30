import QtQuick 2.0
import "qrc:/"


Item
{

    ///@details dapFactor Scaling factor.
    property int dapFactor: 1

    //Add Font Loader
    DapFont
    {
        id: dapFonts
        dapFontPath: "qrc:/resources/fonts/Quicksand/"
        dapFontNames: ["Quicksand-Bold.ttf",
                    "Quicksand-Light.ttf",
                    "Quicksand-Medium.ttf",
                    "Quicksand-Regular.ttf",     //3
                    "Quicksand-SemiBold.ttf",
                    "Quicksand-VariableFont_wght.ttf"]
    }



    property font bold14:    Qt.font({
                                            family: dapFonts.dapProjectFonts[0].name,
                                            bold: true,
                                            italic: false,
                                            pixelSize: 14 * dapFactor
                                        })


    property font medium10:    Qt.font({
                                            family: dapFonts.dapProjectFonts[2].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 10 * dapFactor
                                        })

    property font medium11:    Qt.font({
                                            family: dapFonts.dapProjectFonts[2].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 11 * dapFactor
                                        })

    property font medium12:    Qt.font({
                                            family: dapFonts.dapProjectFonts[2].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 12 * dapFactor
                                        })

    property font medium27:    Qt.font({
                                            family: dapFonts.dapProjectFonts[2].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 27 * dapFactor
                                        })

    property font mediumBold16:    Qt.font({
                                            family: dapFonts.dapProjectFonts[2].name,
                                            bold: true,
                                            italic: false,
                                            pixelSize: 16 * dapFactor
                                        })

    property font regular12:    Qt.font({
                                            family: dapFonts.dapProjectFonts[3].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 14 * dapFactor
                                        })


    property font regular14:    Qt.font({
                                            family: dapFonts.dapProjectFonts[3].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 14 * dapFactor
                                        })

    property font regular16:    Qt.font({
                                            family: dapFonts.dapProjectFonts[3].name,
                                            bold: false,
                                            italic: false,
                                            pixelSize: 16 * dapFactor
                                        })

    property font regularCustom: Qt.font({   family: dapFonts.dapProjectFonts[3].name })






}  //root




