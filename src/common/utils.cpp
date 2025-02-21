/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Rekols    <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"

#include <DSettings>
#include <DSettingsOption>
#include <DMessageManager>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QMimeDatabase>
#include <QJsonObject>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFontMetrics>
#include <QPainter>
#include <QString>
#include <QtMath>
#include <QWidget>
#include <QStandardPaths>
#include <KEncodingProber>
#include <QTextCodec>
#include <QImageReader>
#include <QCryptographicHash>
#include "qprocess.h"

QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
QT_END_NAMESPACE

QString Utils::m_systemLanguage;

QString Utils::getQrcPath(const QString &imageName)
{
    return QString(":/images/%1").arg(imageName);
}

QString Utils::getQssPath(const QString &qssName)
{
    return QString(":/qss/%1").arg(qssName);
}

QSize Utils::getRenderSize(int fontSize, const QString &string)
{
    QFont font;
    font.setPointSize(fontSize);
    QFontMetrics fm(font);

    int width = 0;
    int height = 0;

    for (const QString &line : string.split("\n")) {
        int lineWidth = fm.width(line);
        int lineHeight = fm.height();

        if (lineWidth > width) {
            width = lineWidth;
        }

        height += lineHeight;
    }

    return QSize(width, height);
}

void Utils::setFontSize(QPainter &painter, int textSize)
{
    QFont font = painter.font() ;
    font.setPointSize(textSize);
    painter.setFont(font);
}

void Utils::applyQss(QWidget *widget, const QString &qssName)
{
    QFile file(Utils::getQssPath(qssName));
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    widget->setStyleSheet(stylesheet);
    file.close();
}

float Utils::codecConfidenceForData(const QTextCodec *codec, const QByteArray &data, const QLocale::Country &country)
{
    qreal hep_count = 0;
    int non_base_latin_count = 0;
    qreal unidentification_count = 0;
    int replacement_count = 0;

    QTextDecoder decoder(codec);
    const QString &unicode_data = decoder.toUnicode(data);

    for (int i = 0; i < unicode_data.size(); ++i) {
        const QChar &ch = unicode_data.at(i);

        if (ch.unicode() > 0x7f)
            ++non_base_latin_count;

        switch (ch.script()) {
        case QChar::Script_Hiragana:
        case QChar::Script_Katakana:
            hep_count += (country == QLocale::Japan) ? 1.2 : 0.5;
            unidentification_count += (country == QLocale::Japan) ? 0 : 0.3;
            break;
        case QChar::Script_Han:
            hep_count += (country == QLocale::China) ? 1.2 : 0.5;
            unidentification_count += (country == QLocale::China) ? 0 : 0.3;
            break;
        case QChar::Script_Hangul:
            hep_count += (country == QLocale::NorthKorea) || (country == QLocale::SouthKorea) ? 1.2 : 0.5;
            unidentification_count += (country == QLocale::NorthKorea) || (country == QLocale::SouthKorea) ? 0 : 0.3;
            break;
        case QChar::Script_Cyrillic:
            hep_count += (country == QLocale::Russia) ? 1.2 : 0.5;
            unidentification_count += (country == QLocale::Russia) ? 0 : 0.3;
            break;
        case QChar::Script_Devanagari:
            hep_count += (country == QLocale::Nepal || country == QLocale::India) ? 1.2 : 0.5;
            unidentification_count += (country == QLocale::Nepal || country == QLocale::India) ? 0 : 0.3;
            break;
        default:
            // full-width character, emoji, 常用标点, 拉丁文补充1，天城文补充，CJK符号和标点符号（如：【】）
            if ((ch.unicode() >= 0xff00 && ch <= 0xffef)
                    || (ch.unicode() >= 0x2600 && ch.unicode() <= 0x27ff)
                    || (ch.unicode() >= 0x2000 && ch.unicode() <= 0x206f)
                    || (ch.unicode() >= 0x80 && ch.unicode() <= 0xff)
                    || (ch.unicode() >= 0xa8e0 && ch.unicode() <= 0xa8ff)
                    || (ch.unicode() >= 0x0900 && ch.unicode() <= 0x097f)
                    || (ch.unicode() >= 0x3000 && ch.unicode() <= 0x303f)) {
                ++hep_count;
            } else if (ch.isSurrogate() && ch.isHighSurrogate()) {
                ++i;

                if (i < unicode_data.size()) {
                    const QChar &next_ch = unicode_data.at(i);

                    if (!next_ch.isLowSurrogate()) {
                        --i;
                        break;
                    }

                    uint unicode = QChar::surrogateToUcs4(ch, next_ch);

                    // emoji
                    if (unicode >= 0x1f000 && unicode <= 0x1f6ff) {
                        hep_count += 2;
                    }
                }
            } else if (ch.unicode() == QChar::ReplacementCharacter) {
                ++replacement_count;
            } else if (ch.unicode() > 0x7f) {
                // 因为UTF-8编码的容错性很低，所以未识别的编码只需要判断是否为 QChar::ReplacementCharacter 就能排除
                if (codec->name() != "UTF-8")
                    ++unidentification_count;
            }
            break;
        }
    }

    float c = qreal(hep_count) / non_base_latin_count / 1.2;

    c -= qreal(replacement_count) / non_base_latin_count;
    c -= qreal(unidentification_count) / non_base_latin_count;

    return qMax(0.0f, c);
}

QByteArray Utils::detectEncode(const QByteArray &data, const QString &fileName)
{
    // Return local encoding if nothing in file.
    if (data.isEmpty()) {
        return QTextCodec::codecForLocale()->name();
    }

    if (QTextCodec *c = QTextCodec::codecForUtfText(data, nullptr)) {
        return c->name();
    }

    QMimeDatabase mime_database;
    const QMimeType &mime_type = fileName.isEmpty() ? mime_database.mimeTypeForData(data) : mime_database.mimeTypeForFileNameAndData(fileName, data);
    const QString &mimetype_name = mime_type.name();
    KEncodingProber::ProberType proberType = KEncodingProber::Universal;

    if (mimetype_name == QStringLiteral("application/xml")
            || mimetype_name == QStringLiteral("text/html")
            || mimetype_name == QStringLiteral("application/xhtml+xml")) {
        const QString &_data = QString::fromLatin1(data);
        QRegularExpression pattern("<\\bmeta.+\\bcharset=(?'charset'\\S+?)\\s*['\"/>]");

        pattern.setPatternOptions(QRegularExpression::DontCaptureOption | QRegularExpression::CaseInsensitiveOption);
        const QString &charset = pattern.match(_data, 0, QRegularExpression::PartialPreferFirstMatch,
                                               QRegularExpression::DontCheckSubjectStringMatchOption).captured("charset");

        if (!charset.isEmpty()) {
            return charset.toLatin1();
        }

        pattern.setPattern("<\\bmeta\\s+http-equiv=\"Content-Language\"\\s+content=\"(?'language'[a-zA-Z-]+)\"");

        const QString &language = pattern.match(_data, 0, QRegularExpression::PartialPreferFirstMatch,
                                                QRegularExpression::DontCheckSubjectStringMatchOption).captured("language");

        if (0 != language.size()) {
            QLocale l(language);

            switch (l.script()) {
            case QLocale::ArabicScript:
                proberType = KEncodingProber::Arabic;
                break;
            case QLocale::SimplifiedChineseScript:
                proberType = KEncodingProber::ChineseSimplified;
                break;
            case QLocale::TraditionalChineseScript:
                proberType = KEncodingProber::ChineseTraditional;
                break;
            case QLocale::CyrillicScript:
                proberType = KEncodingProber::Cyrillic;
                break;
            case QLocale::GreekScript:
                proberType = KEncodingProber::Greek;
                break;
            case QLocale::HebrewScript:
                proberType = KEncodingProber::Hebrew;
                break;
            case QLocale::JapaneseScript:
                proberType = KEncodingProber::Japanese;
                break;
            case QLocale::KoreanScript:
                proberType = KEncodingProber::Korean;
                break;
            case QLocale::ThaiScript:
                proberType = KEncodingProber::Thai;
                break;
            default:
                break;
            }
        }
    } else if (mimetype_name == "text/x-python") {
        QRegularExpression pattern("^#coding\\s*:\\s*(?'coding'\\S+)$");
        QTextStream stream(data);

        pattern.setPatternOptions(QRegularExpression::DontCaptureOption | QRegularExpression::CaseInsensitiveOption);
        stream.setCodec("latin1");

        while (!stream.atEnd()) {
            const QString &_data = stream.readLine();
            const QString &coding = pattern.match(_data, 0).captured("coding");

            if (!coding.isEmpty()) {
                return coding.toLatin1();
            }
        }
    }

    // for CJK
    const QList<QPair<KEncodingProber::ProberType, QLocale::Country>> fallback_list {
        {KEncodingProber::ChineseSimplified, QLocale::China},
        {KEncodingProber::ChineseTraditional, QLocale::China},
        {KEncodingProber::Japanese, QLocale::Japan},
        {KEncodingProber::Korean, QLocale::NorthKorea},
        //{KEncodingProber::Cyrillic, QLocale::Russia},
        //{KEncodingProber::Greek, QLocale::Greece},
        //{proberType, QLocale::system().country()}
    };

    KEncodingProber prober(proberType);
    prober.feed(data);
    float pre_confidence = prober.confidence();
    QByteArray pre_encoding = prober.encoding();

    QTextCodec *def_codec = QTextCodec::codecForLocale();
    QByteArray encoding;
    float confidence = 0;

    for (auto i : fallback_list) {
        prober.setProberType(i.first);
        prober.feed(data);

        float prober_confidence = prober.confidence();
        QByteArray prober_encoding = prober.encoding();

        if (i.first != proberType && qFuzzyIsNull(prober_confidence)) {
            prober_confidence = pre_confidence;
            prober_encoding = pre_encoding;
        }

    confidence:
        if (QTextCodec *codec = QTextCodec::codecForName(prober_encoding)) {
            if (def_codec == codec)
                def_codec = nullptr;

            float c = Utils::codecConfidenceForData(codec, data, i.second);

            if (prober_confidence > 0.5) {
                c = c / 2 + prober_confidence / 2;
            } else {
                c = c / 3 * 2 + prober_confidence / 3;
            }

            if (c > confidence) {
                confidence = c;
                encoding = prober_encoding;
            }

            if (i.first == KEncodingProber::ChineseTraditional && c < 0.5) {
                // test Big5
                c = Utils::codecConfidenceForData(QTextCodec::codecForName("Big5"), data, i.second);

                if (c > 0.5 && c > confidence) {
                    confidence = c;
                    encoding = "Big5";
                }
            }
        }

        if (i.first != proberType) {
            // 使用 proberType 类型探测出的结果结合此国家再次做编码检查
            i.first = proberType;
            prober_confidence = pre_confidence;
            prober_encoding = pre_encoding;
            goto confidence;
        }
    }

    if (def_codec && Utils::codecConfidenceForData(def_codec, data, QLocale::system().country()) > confidence) {
        return def_codec->name();
    }

    return encoding;
}

QByteArray Utils::getEncode(const QByteArray &data)
{
    // try to get HTML header encoding.
    if (QTextCodec *codecForHtml = QTextCodec::codecForHtml(data, nullptr)) {
        return codecForHtml->name();
    }

    QTextCodec *codec = nullptr;
    KEncodingProber prober(KEncodingProber::Universal);
    prober.feed(data.constData(), data.size());

    // we found codec with some confidence ?
    if (prober.confidence() > 0.5) {
        codec = QTextCodec::codecForName(prober.encoding());
    }

    if (!codec) {
        return QByteArray();
    }

    return codec->name();
}

bool Utils::fileExists(const QString &path)
{
    QFileInfo check_file(path);

    return check_file.exists() && check_file.isFile();
}

bool Utils::fileIsWritable(const QString &path)
{
    QFileDevice::Permissions permissions = QFile(path).permissions();

    return permissions & QFileDevice::WriteUser;
}

bool Utils::fileIsHome(const QString &path)
{
    return path.startsWith(QDir::homePath());
}

QString Utils::getKeyshortcut(QKeyEvent *keyEvent)
{
    QStringList keys;
    Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
    if (modifiers != Qt::NoModifier) {
        if (modifiers.testFlag(Qt::MetaModifier)) {
            keys.append("Meta");
        }

        if (modifiers.testFlag(Qt::ControlModifier)) {
            keys.append("Ctrl");
        }

        if (modifiers.testFlag(Qt::AltModifier)) {
            keys.append("Alt");
        }

        if (modifiers.testFlag(Qt::ShiftModifier)) {
            keys.append("Shift");
        }

        // 添加小键盘处理，若为小键盘按键按下，组合键需添加 Num ，例如 Ctrl+Num+6 / Ctrl+Num+Up
        if (modifiers.testFlag(Qt::KeypadModifier)) {
            keys.append("Num");
        }
    }

    if (keyEvent->key() != 0 && keyEvent->key() != Qt::Key_unknown) {
        keys.append(QKeySequence(keyEvent->key()).toString());
    }

    for (int i = 0; i < keys.count(); i++) {
        if (keys.value(i).contains("Return")) {
            keys.replace(i, "Enter");
        }
    }

    return keys.join("+");
}

QString Utils::getKeyshortcutFromKeymap(Settings *settings, const QString &keyCategory, const QString &keyName)
{
    return settings->settings->option(QString("shortcuts.%1.%2").arg(keyCategory).arg(keyName))->value().toString();
}

QPixmap Utils::dropShadow(const QPixmap &source, qreal radius, const QColor &color, const QPoint &offset)
{
    QImage shadow = dropShadow(source, radius, color);
    shadow.setDevicePixelRatio(source.devicePixelRatio());

    QPainter pa(&shadow);
    pa.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pa.drawPixmap(radius - offset.x(), radius - offset.y(), source);
    pa.end();

    return QPixmap::fromImage(shadow);
}

QImage Utils::dropShadow(const QPixmap &px, qreal radius, const QColor &color)
{
    if (px.isNull()) {
        return QImage();
    }

    QImage tmp(px.size() * px.devicePixelRatio() + QSize(radius * 2, radius * 2), QImage::Format_ARGB32_Premultiplied);
    tmp.setDevicePixelRatio(px.devicePixelRatio());
    tmp.fill(0);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawPixmap(QPoint(radius, radius), px);
    tmpPainter.end();

    // Blur the alpha channel.
    QImage blurred(tmp.size() * px.devicePixelRatio(), QImage::Format_ARGB32_Premultiplied);
    blurred.setDevicePixelRatio(px.devicePixelRatio());
    blurred.fill(0);
    QPainter blurPainter(&blurred);
    qt_blurImage(&blurPainter, tmp, radius, false, true);
    blurPainter.end();
    if (color == QColor(Qt::black)) {
        return blurred;
    }
    tmp = blurred;

    // Blacken the image...
    tmpPainter.begin(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(tmp.rect(), color);
    tmpPainter.end();

    return tmp;
}

qreal Utils::easeInOut(qreal x)
{
    return (1 - qCos(M_PI * x)) / 2;
}

qreal Utils::easeInQuad(qreal x)
{
    return qPow(x, 2);
}

qreal Utils::easeOutQuad(qreal x)
{
    return -1 * qPow(x - 1, 2) + 1;
}

qreal Utils::easeInQuint(qreal x)
{
    return qPow(x, 5);
}

qreal Utils::easeOutQuint(qreal x)
{
    return qPow(x - 1, 5) + 1;
}

QVariantMap Utils::getThemeMapFromPath(const QString &filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open " << filepath;
        return QVariantMap();
    }

    QTextStream in(&file);
    const QString jsonStr = in.readAll();
    file.close();

    QByteArray jsonBytes = jsonStr.toLocal8Bit();
    QJsonDocument document = QJsonDocument::fromJson(jsonBytes);
    QJsonObject object = document.object();

    return object.toVariantMap();
}

bool Utils::isMimeTypeSupport(const QString &filepath)
{
    QString mimeType = QMimeDatabase().mimeTypeForFile(filepath).name();

    if (mimeType.startsWith("text/")) {
        return true;
    }

    if (filepath.endsWith("pub")) {
        return true;
    }
    // Please check full mime type list from: https://www.freeformatter.com/mime-types-list.html
    QStringList textMimeTypes;
    textMimeTypes << "application/cmd"
                  << "application/javascript"
                  << "application/json"
                  << "application/pkix-cert"
                  << "application/octet-stream"
                  << "application/sql"
                  << "application/vnd.apple.mpegurl"
                  << "application/vnd.nokia.qt.qmakeprofile"
                  << "application/vnd.nokia.xml.qt.resource"
                  << "application/x-desktop"
                  << "application/x-designer"
                  << "application/x-empty"
                  << "application/x-msdos-program"
                  << "application/x-pearl"
                  << "application/x-php"
                  << "application/x-shellscript"
                  << "application/x-sh"
                  << "application/x-theme"
                  << "application/x-cue"
                  << "application/x-csh"
                  << "application/x-asp"
                  << "application/x-subrip"
                  << "application/x-text"
                  << "application/x-trash"
                  << "application/x-xbel"
                  << "application/x-yaml"
                  << "application/x-pem-key"
                  << "application/xml"
                  << "application/yaml"
                  << "application/x-zerosize"
                  << "image/svg+xml"
                  << "application/x-perl"
                  << "application/x-ruby"
                  << "application/x-mpegURL"
                  << "application/x-wine-extension-ini"
                  << "model/vrml"
                  << "application/pkix-cert+pem"
                  << "application/x-pak"
                  << "application/x-code-workspace";

    if (textMimeTypes.contains(mimeType)) {
        return true;
    }

    return false;
}

bool Utils::isDraftFile(const QString &filepath)
{
    QString draftDir = QDir(Utils::cleanPath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)).first())
                       .filePath("blank-files");
    draftDir = QDir::cleanPath(draftDir);
    QString dir = QFileInfo(filepath).dir().absolutePath();
    return dir == draftDir;
}

/**
 * @param filepath 文件路径
 * @return 返回传入文件路径 \a filepath 是否在备份文件夹 backup-files 中
 */
bool Utils::isBackupFile(const QString &filepath)
{
    QString backupDir = QDir(Utils::cleanPath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)).first())
                        .filePath("backup-files");
    QString dir = QFileInfo(filepath).dir().absolutePath();
    return dir == backupDir;
}

QStringList Utils::cleanPath(const QStringList &filePaths)
{
    QStringList paths;
    for (QString path : filePaths) {
        paths.push_back(QDir::cleanPath(path));
    }

    return paths;
}

const QStringList Utils::getEncodeList()
{
    QStringList encodeList;

    for (int mib : QTextCodec::availableMibs()) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);
        QString encodeName = QString(codec->name()).toUpper();

        if (encodeName != "UTF-8" && !encodeList.contains(encodeName)) {
            encodeList.append(encodeName);
        }
    }

    encodeList.sort();
    encodeList.prepend("UTF-8");

    return encodeList;
}

QPixmap Utils::renderSVG(const QString &filePath, const QSize &size, bool bIsScale)
{
    int scaled = 1;

    if (qApp->devicePixelRatio() == 1.25 && bIsScale) {
        scaled = 2;
    }

    QPixmap pixmap(size * scaled);
    pixmap.fill(Qt::transparent);
    QImageReader reader;

    reader.setFileName(filePath);

    if (reader.canRead()) {
        reader.setScaledSize(size * scaled);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(scaled);
    } else {
        pixmap.load(filePath);
    }

    return pixmap;
}

QList<QColor> Utils::getHiglightColorList()
{
    QList<QColor> listColor;
    listColor.append(QColor("#FFA503"));
    listColor.append(QColor("#FF1C49"));
    listColor.append(QColor("#9023FC"));
    listColor.append(QColor("#3468FF"));
    listColor.append(QColor("#00C7E1"));
    listColor.append(QColor("#05EA6B"));
    listColor.append(QColor("#FEF144"));
    listColor.append(QColor("#D5D5D1"));
    return listColor;
}

void Utils::clearChildrenFocus(QObject *objParent)
{
    // 可以获取焦点的控件名称列表
    QStringList foucswidgetlist;
    //foucswidgetlist << "QLineEdit" << TERM_WIDGET_NAME;

    //qDebug() << "checkChildrenFocus start" << objParent->children().size();
    for (QObject *obj : objParent->children()) {
        if (!obj->isWidgetType()) {
            continue;
        }
        QWidget *widget = static_cast<QWidget *>(obj);
        if (Qt::NoFocus != widget->focusPolicy()) {
            //qDebug() << widget << widget->focusPolicy() << widget->metaObject()->className();
            if (!foucswidgetlist.contains(widget->metaObject()->className())) {
                widget->setFocusPolicy(Qt::NoFocus);
            }
        }
        clearChildrenFocus(obj);
    }

    //qDebug() << "checkChildrenFocus over" << objParent->children().size();
}

void Utils::clearChildrenFoucusEx(QWidget *pWidget)
{
    pWidget->clearFocus();

    QObjectList childern = pWidget->children();

    if (childern.size() <= 0) return;

    foreach (QObject *child, childern) {
        if (!child->isWidgetType()) {
            continue;
        }

        QWidget *obj = static_cast<QWidget *>(child);
        clearChildrenFoucusEx(obj);
    }
}

void Utils::setChildrenFocus(QWidget *pWidget, Qt::FocusPolicy policy)
{
    pWidget->setFocusPolicy(policy);

    QObjectList childern = pWidget->children();

    if (childern.size() <= 0) return;

    foreach (QObject *child, childern) {
        if (!child->isWidgetType()) {
            continue;
        }

        QWidget *obj = static_cast<QWidget *>(child);
        setChildrenFocus(obj, policy);
    }
}

int Utils::getProcessCountByName(const char *pstrName)
{
    FILE *fp = NULL;
    int count = -1;
    char command[1024];

    if (NULL == pstrName || strlen(pstrName) == 0) {
        return count;
    }

    memset(command, 0, sizeof(command));
    sprintf(command, "ps -ef | grep %s | grep -v grep | wc -l", pstrName);

    if ((fp = popen(command, "r")) != NULL) {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        if ((fgets(buf, sizeof(buf) - 1, fp)) != NULL) {
            count = atoi(buf);
        }
        pclose(fp);
    } else {
        qDebug() << ">>> popen error";
    }

    return count;
}

void Utils::killProcessByName(const char *pstrName)
{
    if (pstrName != NULL && strlen(pstrName) > 0) {
        char command[1024];
        memset(command, 0, sizeof(command));
        sprintf(command, "killall %s", pstrName);
        system(command);
    }
}

QString Utils::getStringMD5Hash(const QString &input)
{
    QByteArray byteArray;
    byteArray.append(input);
    QByteArray md5Path = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);

    return md5Path.toHex();
}

bool Utils::activeWindowFromDock(quintptr winId)
{
    bool bRet = true;
    // new interface use application as id
    QDBusInterface dockDbusInterface("com.deepin.dde.daemon.Dock",
                                     "/com/deepin/dde/daemon/Dock",
                                     "com.deepin.dde.daemon.Dock");
    QDBusReply<void> reply = dockDbusInterface.call("ActivateWindow", winId);
    if (!reply.isValid()) {
        qDebug() << "call com.deepin.dde.daemon.Dock failed" << reply.error();
        bRet = false;
    }

    return bRet;
}

bool Utils::isShareDirAndReadOnly(const QString &filePath)
{
    bool ret = false;

    const QString sharePath = "/var/lib/samba/usershares";
    QDir shareDir(sharePath);
    if (shareDir.exists()) {
        QFileInfo fileInfo(filePath);
        auto name = fileInfo.dir().dirName();
        if (shareDir.exists(name)) {
            QFile file(sharePath + "/" + name);
            if (file.open(QIODevice::ReadOnly)) {
                QString fileContent = file.readAll();
                if (fileContent.contains(":R"))
                    ret = true;
                file.close();
            }
        }
    }

    return ret;

}

QString Utils::getSystemLan()
{
    if (!m_systemLanguage.isEmpty()) {
        return m_systemLanguage;
    } else {
        QDBusInterface ie("com.deepin.daemon.LangSelector",
                          "/com/deepin/daemon/LangSelector",
                          "com.deepin.daemon.LangSelector",
                          QDBusConnection::sessionBus());

        m_systemLanguage = ie.property("CurrentLocale").toString();
        return m_systemLanguage;
    }
}


//judge whether the protocol is wayland
bool Utils::isWayland()
{
    static QString protocol;
    if (protocol.isEmpty()) {
        protocol = QProcessEnvironment::systemEnvironment().value("XDG_SESSION_TYPE");
    }

    return protocol.contains("wayland");

}

QString Utils::lineFeed(const QString &text, int nWidth, const QFont &font, int nElidedRow)
{
    if (nElidedRow < 0)
        nElidedRow = 2;

    QString strText = text;
    QStringList strListLine;
    QFontMetrics fm(font);
    // 一行就直接中间截断显示
    if (1 == nElidedRow)
        return fm.elidedText(text, Qt::ElideMiddle, nWidth);

    if (!strText.isEmpty()) {
        for (int i = 1; i <= strText.size(); i++) {
            if (fm.width(strText.left(i)) >= nWidth) {
                if (strListLine.size() + 1 == nElidedRow)
                    break;

                strListLine.append(strText.left(i - 1));
                strText = strText.right(strText.size() - i + 1);
                i = 0;
            }
        }
    }

    // 多行时，对最后一行字符左侧省略
    if (!strListLine.isEmpty()) {
        strText = fm.elidedText(strText, Qt::ElideLeft, nWidth);
        strListLine.append(strText);
        strText = strListLine.join('\n');
    }

    return strText;
}

/**
 * @brief 判断 [ \a x1, \a y1] 和 [ \a x2, \a y2] 区间是否存在交集
 * @param x1 固定区间左边界
 * @param y1 固定区间右边界
 * @param x2 移动区间左边界
 * @param y2 移动区间右边界
 * @return RegionType 返回重叠区间类型
 */
Utils::RegionIntersectType Utils::checkRegionIntersect(int x1, int y1, int x2, int y2)
{
    if (y1 < x2) {
        return ERight;
    } else if (x1 > y2) {
        return ELeft;
    } else {
        // 区间存在交集，判断交集类型
        // 活动区间左边界超过固定区间左边界
        bool outLeftBound = x1 > x2;
        // 活动区间右边界超过固定区间右边界
        bool outRightBound = y1 < y2;

        if (outLeftBound && outRightBound) {
            return EIntersectOutter;
        } else if (outLeftBound) {
            return EIntersectLeft;
        } else if (outRightBound) {
            return EIntersectRight;
        } else {
            return EIntersectInner;
        }
    }
}
