#ifndef DAPFONT_H
#define DAPFONT_H

#include <QObject>
#include <QMap>
#include <QFontDatabase>

class DapFont : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFont regular11 READ regular10 CONSTANT)
    Q_PROPERTY(QFont regular11 READ regular11 CONSTANT)
    Q_PROPERTY(QFont regular12 READ regular12 CONSTANT)
    Q_PROPERTY(QFont regular14 READ regular14 CONSTANT)
    Q_PROPERTY(QFont regular16 READ regular16 CONSTANT)
    Q_PROPERTY(QFont regular18 READ regular18 CONSTANT)
    Q_PROPERTY(QFont regular24 READ regular24 CONSTANT)
    Q_PROPERTY(QFont regular26 READ regular26 CONSTANT)
    Q_PROPERTY(QFont regular28 READ regular28 CONSTANT)

    Q_PROPERTY(QFont semiBold12 READ semiBold12 CONSTANT)
    Q_PROPERTY(QFont semiBold14 READ semiBold14 CONSTANT)
    Q_PROPERTY(QFont semiBold16 READ semiBold16 CONSTANT)
    Q_PROPERTY(QFont semiBold18 READ semiBold18 CONSTANT)

public:
    explicit DapFont(QObject *parent = nullptr);

    QFont regular10() { m_fonts["regular"].font.setPixelSize(10*pt); return m_fonts["regular"].font; }
    QFont regular11() { m_fonts["regular"].font.setPixelSize(11*pt); return m_fonts["regular"].font; }
    QFont regular12() { m_fonts["regular"].font.setPixelSize(12*pt); return m_fonts["regular"].font; }
    QFont regular14() { m_fonts["regular"].font.setPixelSize(14*pt); return m_fonts["regular"].font; }
    QFont regular16() { m_fonts["regular"].font.setPixelSize(16*pt); return m_fonts["regular"].font; }
    QFont regular18() { m_fonts["regular"].font.setPixelSize(18*pt); return m_fonts["regular"].font; }
    QFont regular24() { m_fonts["regular"].font.setPixelSize(24*pt); return m_fonts["regular"].font; }
    QFont regular26() { m_fonts["regular"].font.setPixelSize(26*pt); return m_fonts["regular"].font; }
    QFont regular28() { m_fonts["regular"].font.setPixelSize(28*pt); return m_fonts["regular"].font; }

    QFont semiBold12() { m_fonts["semiBold"].font.setPixelSize(12*pt); return m_fonts["semiBold"].font; }
    QFont semiBold14() { m_fonts["semiBold"].font.setPixelSize(14*pt); return m_fonts["semiBold"].font; }
    QFont semiBold16() { m_fonts["semiBold"].font.setPixelSize(16*pt); return m_fonts["semiBold"].font; }
    QFont semiBold18() { m_fonts["semiBold"].font.setPixelSize(18*pt); return m_fonts["semiBold"].font; }

private:
    int pt = 1; //dpi factor
    struct Fonts
    {
        Fonts() = default;
        Fonts(QString a_source, int a_weight) : source(a_source), weight(a_weight) {}
        QString source{};
        int weight{};
        QFont font{};
    };
    QMap<QString, Fonts> m_fonts;
};

#endif // DAPFONT_H
