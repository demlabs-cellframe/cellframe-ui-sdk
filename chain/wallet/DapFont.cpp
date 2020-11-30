#include "DapFont.h"

DapFont::DapFont(QObject *parent) : QObject(parent)
{
    m_fonts["thin"] =       { ":/resources/fonts/Blinker/Blinker-Thin.ttf",       QFont::Thin        };
    m_fonts["extraLight"] = { ":/resources/fonts/Blinker/Blinker-ExtraLight.ttf", QFont::ExtraLight  };
    m_fonts["light"] =      { ":/resources/fonts/Blinker/Blinker-Light.ttf",      QFont::Light       };
    m_fonts["regular"] =    { ":/resources/fonts/Blinker/Blinker-Regular.ttf",    QFont::Normal      };
    m_fonts["semiBold"] =   { ":/resources/fonts/Blinker/Blinker-SemiBold.ttf",   QFont::DemiBold    };
    m_fonts["bold"] =       { ":/resources/fonts/Blinker/Blinker-Bold.ttf",       QFont::Bold        };
    m_fonts["extraBold"] =  { ":/resources/fonts/Blinker/Blinker-ExtraBold.ttf",  QFont::ExtraBold   };
    m_fonts["black"] =      { ":/resources/fonts/Blinker/Blinker-Black.ttf",      QFont::Black       };

    for (auto &el:m_fonts)
    {
        int id = QFontDatabase::addApplicationFont(el.source);
        el.font = QFont(QFontDatabase::applicationFontFamilies(id).at(0));
        el.font.setWeight(el.weight);
    }
}

