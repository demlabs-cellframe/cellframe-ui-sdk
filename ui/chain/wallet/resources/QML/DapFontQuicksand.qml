import QtQuick 2.0
import "qrc:/"

Item
{
    ///@details dapMainFontTheme ID of item with all project fonts.
    property alias dapMainFontTheme: dapFontsObjects
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
                        "Quicksand-Regular.ttf",
                        "Quicksand-SemiBold.ttf"]

    }

    QtObject
    {

        id: dapFontsObjects

        /////////////////////BOLD/////////////////////////////////////////////////////
        ///@details dapFontQuicksandBold14 Font of Quicksand font family (bold, 14pt)
        property font dapFontQuicksandBold14:                Qt.font({
                                                                         family: dapFonts.dapProjectFonts[0].name,
                                                                         styleName: "Bold",
                                                                         pixelSize: 14 * dapFactor
                                                                    })
        ///@details dapFontQuicksandBold16 Font of Quicksand font family (bold, 16pt)
        property font dapFontQuicksandBold16:                Qt.font({
                                                                         family: dapFonts.dapProjectFonts[0].name,
                                                                         styleName: "Bold",
                                                                         pixelSize: 16 * dapFactor
                                                                    })

        ///@details dapFontQuicksandBoldCustom Font of Quicksand font family (bold, without parameters)
        property font dapFontQuicksandBoldCustom:              Qt.font({
                                                                           family: dapFonts.dapProjectFonts[0].name,
                                                                           styleName: "Bold"
                                                                       })

        /////////////////////LIGHT/////////////////////////////////////////////////////
        ///@details dapFontQuicksandLight14 Font of Quicksand font family (light, 14pt)
        property font dapFontQuicksandLight14:                 Qt.font({
                                                                           family: dapFonts.dapProjectFonts[1].name,
                                                                           styleName: "Light",
                                                                           pixelSize: 14 * dapFactor
                                                                       })
        ///@details dapFontQuicksandLight16 Font of Quicksand font family (light, 16pt)
        property font dapFontQuicksandLight16:                 Qt.font({
                                                                           family: dapFonts.dapProjectFonts[1].name,
                                                                           styleName: "Light",
                                                                           pixelSize: 16 * dapFactor
                                                                       })

        ///@details dapFontQuicksandLightCustom Font of Quicksand font family (light, without parameters)
        property font dapFontQuicksandLightCustom:             Qt.font({
                                                                           family: dapFonts.dapProjectFonts[1].name,
                                                                           styleName: "Light"
                                                                       })

        /////////////////////MEDIUM/////////////////////////////////////////////////////
        ///@details dapFontQuicksandMedium14 Font of Quicksand font family (medium, 14pt)
        property font dapFontQuicksandMedium14:                Qt.font({
                                                                           family: dapFonts.dapProjectFonts[2].name,
                                                                           styleName: "Medium",
                                                                           pixelSize: 14 * dapFactor
                                                                       })

        ///@details dapFontQuicksandMedium16 Font of Quicksand font family (medium, 16pt)
        property font dapFontQuicksandMedium16:                Qt.font({
                                                                           family: dapFonts.dapProjectFonts[2].name,
                                                                           styleName: "Medium",
                                                                           pixelSize: 16 * dapFactor
                                                                       })

        ///@details dapFontQuicksandMediumCustom Font of Quicksand font family (medium, without parameters)
        property font dapFontQuicksandMediumCustom:            Qt.font({
                                                                           family: dapFonts.dapProjectFonts[2].name,
                                                                           styleName: "Medium"
                                                                       })

        /////////////////////REGULAR/////////////////////////////////////////////////////
        ///@details dapFontQuicksandRegular14 Font of Quicksand font family (regular, 14pt)
        property font dapFontQuicksandRegular14:               Qt.font({
                                                                           family: dapFonts.dapProjectFonts[3].name,
                                                                           styleName: "Regular",
                                                                           pixelSize: 14 * dapFactor
                                                                       })



        ///@details dapFontQuicksandRegular12 Font of Quicksand font family (regular, 12pt)
        property font dapFontQuicksandRegular12:               Qt.font({
                                                                           family: dapFonts.dapProjectFonts[3].name,
                                                                           styleName: "Regular",
                                                                           pixelSize: 12 * dapFactor
                                                                       })

        ///@details dapFontQuicksandRegular16 Font of Quicksand font family (regular, 16pt)
        property font dapFontQuicksandRegular16:               Qt.font({
                                                                           family: dapFonts.dapProjectFonts[3].name,
                                                                           styleName: "Regular",
                                                                           pixelSize: 16 * dapFactor
                                                                       })

        ///@details dapFontQuicksandRegular18 Font of Quicksand font family (regular, 18pt)
        property font dapFontQuicksandRegular18:                Qt.font({
                                                                           family: dapFonts.dapProjectFonts[3].name,
                                                                           styleName: "Regular",
                                                                           pixelSize: 18 * dapFactor
                                                                       })


        ///@details dapFontQuicksandRegularCustom Font of Quicksand font family (regular, without parameters)
        property font dapFontQuicksandRegularCustom:            Qt.font({
                                                                          family: dapFonts.dapProjectFonts[3].name,
                                                                          styleName: "Regular"
                                                                      })

        /////////////////////SEMIBOLD/////////////////////////////////////////////////////
        ///@details dapFontQuicksandSemiBold14 Font of Quicksand font family (SemiBold, 14pt)
        property font dapFontQuicksandSemiBold14:               Qt.font({
                                                                            family: dapFonts.dapProjectFonts[4].name,
                                                                            styleName: "SemiBold",
                                                                            pixelSize: 14 * dapFactor
                                                                        })

        ///@details dapFontQuicksandSemiBoldCustom Font of Quicksand font family (SemiBold, without parameters)
        property font dapFontQuicksandSemiBoldCustom:              Qt.font({
                                                                               family: dapFonts.dapProjectFonts[4].name,
                                                                               styleName: "SemiBold"
                                                                           })

    }

}
