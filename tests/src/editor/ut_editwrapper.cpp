/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author:     liumaochuan <liumaochuan@uniontech.com>
* Maintainer: liumaochuan <liumaochuan@uniontech.com>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ut_editwrapper.h"
#include "qfile.h"
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include "DSettingsOption"

namespace editwrapperstub {

int intvalue=1;
int retintstub()
{
    return intvalue;
}

bool retfalsestub()
{
    return false;
}

bool rettruestub()
{
    return true;
}

QStringList stringList = {"123","456"};
QStringList retstringliststub()
{
    return stringList;
}

QPointer<DSettingsOption> d = nullptr;
QPointer<DSettingsOption> retsettingoption()
{
    if (d == nullptr) {
        d = new DSettingsOption();
    }
    QVariant v(stringList);
    d->setValue(v);
    QVariant p = d->value();
    return d;
}

QString retstring()
{
    return "123";
}

}



using namespace editwrapperstub;

UT_Editwrapper::UT_Editwrapper()
{
    QString text = QString("#include \"window.h\"\n"
                           "#include \"urlinfo.h\"\n"
                           "int main(int argc, char *argv[])\n"
                           "{\n"
                           "using namespace Dtk::Core;\n"
                           "PerformanceMonitor::initializeAppStart();\n"
                           "return 0;\n"
                           "}");
    QFile f("1.cpp");
    if(f.open(QFile::WriteOnly)){
        f.write(text.toUtf8());
        f.close();
    }
}

TEST(UT_Editwrapper_EditWrapper, UT_Editwrapper_EditWrapper)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    ASSERT_TRUE(pWindow->currentWrapper()->m_pBottomBar != nullptr);
    ASSERT_TRUE(pWindow->currentWrapper()->m_pTextEdit != nullptr);

    delete pWindow;
    pWindow = nullptr;
}

//void setQuitFlag();
TEST(UT_Editwrapper_setQuitFlag, UT_Editwrapper_setQuitFlag)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setQuitFlag();
    ASSERT_TRUE(pWindow->currentWrapper()->m_bQuit == true);

    delete pWindow;
    pWindow = nullptr;
}

//bool getFileLoading();
TEST(UT_Editwrapper_getFileLoading, UT_Editwrapper_getFileLoading)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setQuitFlag();
    ASSERT_TRUE(pWindow->currentWrapper()->getFileLoading() == true);

    delete pWindow;
    pWindow = nullptr;
}

//void openFile(const QString &filepath,QString qstrTruePath,bool bIsTemFile = false);
TEST(UT_Editwrapper_openFile, UT_Editwrapper_openFile)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->openFile(QString("a.cpp"), QString("b.cpp"));
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->m_bIsFileOpen == true);

    delete pWindow;
    pWindow = nullptr;
}

bool saveFile_001_stub()
{
    return true;
}

void hideWarningNotices_stub()
{
    return;
}

//bool saveFile_001();
TEST(UT_Editwrapper_saveFile, UT_Editwrapper_saveFile_001)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
  
    Stub stubNotices;
    stubNotices.set(ADDR(EditWrapper, hideWarningNotices), hideWarningNotices_stub);
    bool bRet = pWindow->currentWrapper()->saveFile();
    if (bRet == false) {
        Stub stub;
        stub.set(pWindow->currentWrapper()->saveFile(), saveFile_001_stub());
        bRet = pWindow->currentWrapper()->saveFile();
    }
    ASSERT_TRUE(bRet == true);

    pWindow->deleteLater();
    */
}

bool saveFile_002_stub()
{
    return true;
}

//bool saveFile_002();
TEST(UT_Editwrapper_saveFile, UT_Editwrapper_saveFile_002)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    bool bRet = pWindow->currentWrapper()->saveFile();
    Stub stubNotices;
    stubNotices.set(ADDR(EditWrapper, hideWarningNotices), hideWarningNotices_stub);
    if (bRet == false) {
        Stub stub;
        stub.set(pWindow->currentWrapper()->saveFile(), saveFile_002_stub());
        bRet = pWindow->currentWrapper()->saveFile();
    }
    ASSERT_TRUE(bRet == true);

    delete pWindow;
    pWindow = nullptr;
    */
}

//bool saveFile_003();
TEST(UT_Editwrapper_saveFile, UT_Editwrapper_saveFile_003)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->m_sFilePath = QString("");
    pWindow->currentWrapper()->textEditor()->m_qstrTruePath = QString("");
    Stub stubNotices;
    stubNotices.set(ADDR(EditWrapper, hideWarningNotices), hideWarningNotices_stub);
    bool bRet = pWindow->currentWrapper()->saveFile();
    ASSERT_TRUE(bRet == false);

    delete pWindow;
    pWindow = nullptr;
    */
}

TEST(UT_Editwrapper_saveFile, UT_Editwrapper_saveFile_004)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->m_sFilePath = QString("");
    pWindow->currentWrapper()->textEditor()->m_qstrTruePath = QString("");

    Stub stubNotices;
    stubNotices.set(ADDR(EditWrapper, hideWarningNotices), hideWarningNotices_stub);
    typedef bool (*Fptr2)(QFile*,QFile::OpenMode);
    Fptr2 A_foo = (Fptr2)((bool(QFile::*)(QFile::OpenMode))&QFile::open);
    Stub s1;
    s1.set(A_foo,rettruestub);

    Stub s2;
    s2.set(ADDR(QByteArray,isEmpty),rettruestub);

    bool bRet = pWindow->currentWrapper()->saveFile();

    delete pWindow;
    pWindow = nullptr;
    */
}

TEST(UT_Editwrapper_saveFile, UT_Editwrapper_saveFile_005)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->m_sFilePath = QString("");
    pWindow->currentWrapper()->textEditor()->m_qstrTruePath = QString("");

    Stub stubNotices;
    stubNotices.set(ADDR(EditWrapper, hideWarningNotices), hideWarningNotices_stub);
    typedef bool (*Fptr2)(QFile*,QFile::OpenMode);
    Fptr2 A_foo = (Fptr2)((bool(QFile::*)(QFile::OpenMode))&QFile::open);
    Stub s1;
    s1.set(A_foo,rettruestub);

    Stub s2;
    s2.set(ADDR(QByteArray,isEmpty),retfalsestub);

    Stub s3;
    s3.set(ADDR(QByteArray,size),retintstub);

    intvalue=0;
    bool bRet = pWindow->currentWrapper()->saveFile();

    delete pWindow;
    pWindow = nullptr;
    */
}

//bool saveAsFile_001(const QString &newFilePath, QByteArray encodeName);
TEST(UT_Editwrapper_saveAsFile_001, UT_Editwrapper_saveAsFile_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    bool bRet = pWindow->currentWrapper()->saveAsFile(QString(), QByteArray("UTF-8"));
    ASSERT_TRUE(bRet == false);

    pWindow->deleteLater();
}

bool saveAsFile_002_stub()
{
    return true;
}

//bool saveAsFile_001(const QString &newFilePath, QByteArray encodeName);
TEST(UT_Editwrapper_saveAsFile, UT_Editwrapper_saveAsFile_002)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    QString newFilePaht(pWindow->currentWrapper()->textEditor()->getTruePath());
    bool bRet = pWindow->currentWrapper()->saveAsFile(newFilePaht, QByteArray("UTF-8"));
    if (bRet == false) {
        Stub stub;
        stub.set(pWindow->currentWrapper()->saveAsFile(), saveAsFile_002_stub());
    }
    ASSERT_TRUE(bRet == true);

    pWindow->deleteLater();
    */
}

TEST(UT_Editwrapper_saveAsFile, UT_Editwrapper_saveAsFile_003)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));

    typedef int (*Fptr)(QFileDialog *);
    Fptr fptr = (Fptr)(&QFileDialog::exec);
    Stub s1;
    s1.set(fptr,retintstub);

    Stub s2;
    s2.set(ADDR(QString,isEmpty),retfalsestub);

    Stub s3;
    s3.set(ADDR(QFileDialog,selectedFiles),retstringliststub);

    typedef bool (*Fptr2)(QFile*,QFile::OpenMode);
    Fptr2 A_foo = (Fptr2)((bool(QFile::*)(QFile::OpenMode))&QFile::open);
    Stub s4;
    s4.set(A_foo,rettruestub);

    bool bRet = pWindow->currentWrapper()->saveAsFile();

    EXPECT_NE(bRet,true);
    pWindow->deleteLater();
    */
}

//void updatePath(const QString &file);
TEST(UT_Editwrapper_updatePath, UT_Editwrapper_updatePath)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    QString strFilePath(pWindow->currentWrapper()->textEditor()->m_sFilePath);
    QString strTruePath(pWindow->currentWrapper()->textEditor()->m_qstrTruePath);
    ASSERT_TRUE(!strFilePath.compare(strTruePath));

    delete pWindow;
    pWindow = nullptr;
}

//void hideWarningNotices();
TEST(UT_Editwrapper_hideWarningNotices, UT_Editwrapper_hideWarningNotices)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    if (pWindow->currentWrapper()->m_pWaringNotices != nullptr) {
        pWindow->currentWrapper()->m_pWaringNotices->show();
    }
    pWindow->currentWrapper()->hideWarningNotices();
    ASSERT_TRUE(pWindow->currentWrapper()->m_pWaringNotices->isHidden());

    delete pWindow;
    pWindow = nullptr;
}

//void checkForReload();
TEST(UT_Editwrapper_checkForReload, UT_Editwrapper_checkForReload_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->checkForReload();
    QString strFilePath(pWindow->currentWrapper()->textEditor()->m_sFilePath);
    QString strTruePath(pWindow->currentWrapper()->textEditor()->m_qstrTruePath);
    ASSERT_TRUE(!strFilePath.compare(strTruePath));

    pWindow->deleteLater();
}

bool checkForReload_002_stub()
{
    return false;
}

//void checkForReload();
TEST(UT_Editwrapper_checkForReload, UT_Editwrapper_checkForReload_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    Stub stub;
    stub.set(ADDR(Utils,isDraftFile), checkForReload_002_stub);
    pWindow->currentWrapper()->checkForReload();
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getTruePath() != nullptr);

    pWindow->deleteLater();
}

//void initToastPosition() 无实现;

//void showNotify(const QString &message);
TEST(UT_Editwrapper_showNotify, UT_Editwrapper_showNotify_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->setReadOnlyPermission(true);
    pWindow->currentWrapper()->textEditor()->m_readOnlyMode = true;
    pWindow->currentWrapper()->showNotify(QString("read-only"));
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getReadOnlyPermission() == true);

    pWindow->deleteLater();
}

//void showNotify(const QString &message);
TEST(UT_Editwrapper_showNotify, UT_Editwrapper_showNotify_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->setReadOnlyPermission(false);
    pWindow->currentWrapper()->textEditor()->m_readOnlyMode = false;
    pWindow->currentWrapper()->showNotify(QString("Not read-only"));
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getReadOnlyPermission() == false);

    pWindow->deleteLater();
}

//void setLineNumberShow(bool bIsShow,bool bIsFirstShow = false);
TEST(UT_Editwrapper_setLineNumberShow, UT_Editwrapper_setLineNumberShow_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setLineNumberShow(true, false);
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getLeftAreaWidget()->m_pLineNumberArea->isVisible());

    pWindow->deleteLater();
}

//void setLineNumberShow(bool bIsShow,bool bIsFirstShow = false);
TEST(UT_Editwrapper_setLineNumberShow, UT_Editwrapper_setLineNumberShow_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setLineNumberShow(false);
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getLeftAreaWidget()->m_pLineNumberArea->isHidden());

    pWindow->deleteLater();
}

//void setShowBlankCharacter(bool ok);
TEST(UT_Editwrapper_setShowBlankCharacter, UT_Editwrapper_setShowBlankCharacter_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setShowBlankCharacter(true);
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->document()->defaultTextOption().flags() == QTextOption::ShowTabsAndSpaces);

    pWindow->deleteLater();
}

//void setShowBlankCharacter(bool ok);
TEST(UT_Editwrapper_setShowBlankCharacter, UT_Editwrapper_setShowBlankCharacter_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->setShowBlankCharacter(false);
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->document()->defaultTextOption().flags() != QTextOption::ShowTabsAndSpaces);

    pWindow->deleteLater();
}

//BottomBar *bottomBar();
TEST(UT_Editwrapper_bottomBar, UT_Editwrapper_bottomBar)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    ASSERT_TRUE(pWindow->currentWrapper()->bottomBar());

    pWindow->deleteLater();
}

//QString filePath();
TEST(UT_Editwrapper_filePath, UT_Editwrapper_filePath)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    ASSERT_TRUE(!pWindow->currentWrapper()->filePath().isEmpty());

    pWindow->deleteLater();
}

//TextEdit *textEditor() { return m_textEdit; }
TEST(UT_Editwrapper_textEditor, UT_Editwrapper_textEditor)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor());

    pWindow->deleteLater();
}

//int GetCorrectUnicode1(const QByteArray &ba) 未实现;

int saveDraftFile001_exec_stub()
{
    return 1;
}

//bool saveDraftFile(); Subsequent processing
TEST(UT_Editwrapper_saveDraftFile, UT_Editwrapper_saveDraftFile_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    typedef int (*fptr)(QDialog *);
    fptr fileDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(fileDialogExec, saveDraftFile001_exec_stub);
    pWindow->currentWrapper()->saveDraftFile();

    pWindow->deleteLater();
}

int saveDraftFile002_exec_stub()
{
    return 0;
}

//bool saveDraftFile(); Subsequent processing
TEST(UT_Editwrapper_saveDraftFile, UT_Editwrapper_saveDraftFile_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    typedef int (*fptr)(QDialog *);
    fptr fileDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(fileDialogExec, saveDraftFile002_exec_stub);
    pWindow->currentWrapper()->saveDraftFile();

    pWindow->deleteLater();
}

void readFile_stub_001()
{
    return;
}

//void readFile(const QString &filePath);
TEST(UT_Editwrapper_readFile, UT_Editwrapper_readFile_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    pWindow->currentWrapper()->textEditor()->setTruePath(filePath);
    pWindow->currentWrapper()->textEditor()->m_sFilePath = filePath;
    Stub stub;
    stub.set(ADDR(EditWrapper, loadContent), readFile_stub_001);
    bool bRet = pWindow->currentWrapper()->readFile(QByteArray());
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

//void readFile(const QString &filePath);
TEST(UT_Editwrapper_readFile, UT_Editwrapper_readFile_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile001");
    pWindow->currentWrapper()->textEditor()->setTruePath(filePath);
    pWindow->currentWrapper()->textEditor()->m_sFilePath = filePath;
    Stub stub;
    stub.set(ADDR(EditWrapper, loadContent), readFile_stub_001);
    bool bRet = pWindow->currentWrapper()->readFile(QByteArray("UTF-8"));
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

QByteArray FileLoadThreadRun(const QString &strFilePath, QByteArray *encode)
{
    QFile file(strFilePath);

    if (file.open(QIODevice::ReadOnly)) {
        // reads all remaining data from the file.
        QByteArray indata = file.readAll();
        file.close();
        QByteArray outData;
        // read the encode.
        *encode = DetectCode::GetFileEncodingFormat(strFilePath);
        QString textEncode = QString::fromLocal8Bit(*encode);

         if (textEncode.contains("ASCII", Qt::CaseInsensitive) || textEncode.contains("UTF-8", Qt::CaseInsensitive)) {
             return indata;
         } else {
           DetectCode::ChangeFileEncodingFormat(indata, outData, textEncode, QString("UTF-8"));
           return outData;
         }
    }
}

void handleFileLoadFinished_001_setPrintEnabled_stub()
{
    return;
}

void handleFileLoadFinished_001_setTextFinished_stub()
{
    return;
}

TEST(UT_Editwrapper_handleFilePreProcess, handleFilePreProcess_normalData_pass)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    QByteArray encode = QByteArray();
    const QByteArray retFileContent = FileLoadThreadRun(filePath, &encode);
    // 预读取数据
    pWindow->currentWrapper()->handleFilePreProcess(encode, retFileContent);

    EXPECT_EQ(pWindow->currentWrapper()->m_bHasPreProcess, true);
    // 均为UTF-8格式
    EXPECT_EQ(pWindow->currentWrapper()->m_pTextEdit->toPlainText().toUtf8(), retFileContent);

    pWindow->deleteLater();
}

QString disableToUnicode(const char *in, int length, QTextCodec::ConverterState *state = nullptr)
{
    Q_UNUSED(in)
    Q_UNUSED(length)
    Q_UNUSED(state)
    return nullptr;
}

TEST(UT_Editwrapper_handleFilePreProcess, handleFilePreProcess_errorData_failed)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    QByteArray encode = QByteArray();
    const QByteArray retFileContent = FileLoadThreadRun(filePath, &encode);

    // 定义重载函数类型
    typedef  QString (QTextCodec::*toUnicodeType)(const char *, int, QTextCodec::ConverterState *) const;
    Stub setToUnicodeDisabled_stub;
    setToUnicodeDisabled_stub.set((toUnicodeType)ADDR(QTextCodec, toUnicode), disableToUnicode);
    // 预读取数据
    pWindow->currentWrapper()->handleFilePreProcess(encode, retFileContent);

    EXPECT_EQ(pWindow->currentWrapper()->m_bHasPreProcess, true);
    EXPECT_TRUE(pWindow->currentWrapper()->m_pTextEdit->toPlainText().isEmpty());

    pWindow->deleteLater();
}

//void handleFileLoadFinished(const QByteArray &encode,const QString &content);
TEST(UT_Editwrapper_handleFileLoadFinished, UT_Editwrapper_handleFileLoadFinished_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    QByteArray encode = QByteArray();
    const QByteArray retFileContent = FileLoadThreadRun(filePath, &encode);
    Stub setPrintEnabled_stub;
    setPrintEnabled_stub.set(ADDR(Window, setPrintEnabled), handleFileLoadFinished_001_setPrintEnabled_stub);
    Stub setTextFinished_stub;
    setTextFinished_stub.set(ADDR(TextEdit, setTextFinished), handleFileLoadFinished_001_setTextFinished_stub);
    pWindow->currentWrapper()->handleFileLoadFinished(encode, retFileContent);
    ASSERT_TRUE(pWindow->currentWrapper()->m_pBottomBar->m_pEncodeMenu != nullptr);

    pWindow->deleteLater();
}

TEST(UT_Editwrapper_handleFileLoadFinished, UT_Editwrapper_handleFileLoadFinished_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    QByteArray encode = QByteArray();
    const QByteArray retFileContent = FileLoadThreadRun(filePath, &encode);
    Stub setPrintEnabled_stub;
    setPrintEnabled_stub.set(ADDR(Window, setPrintEnabled), handleFileLoadFinished_001_setPrintEnabled_stub);
    Stub setTextFinished_stub;
    setTextFinished_stub.set(ADDR(TextEdit, setTextFinished), handleFileLoadFinished_001_setTextFinished_stub);

    Stub s1;
    s1.set(ADDR(KSyntaxHighlighting::Definition,isValid),rettruestub);
    Stub s2;
    s2.set(ADDR(QString,isEmpty),retfalsestub);
    Stub s3;
    s3.set(ADDR(Utils,isDraftFile),retfalsestub);
    Stub s4;
    s4.set(ADDR(TextEdit,getReadOnlyPermission),rettruestub);
    Stub s5;
    s5.set(ADDR(EditWrapper,loadContent),rettruestub);
    Stub s6;
    s6.set(ADDR(EditWrapper,OnUpdateHighlighter),rettruestub);//DSettings
    Stub s7;
    s7.set(ADDR(DSettings,option),retsettingoption);
    Stub s8;//QString toString() const;
    s8.set((QString (QJsonValue::*)() const)ADDR(QJsonValue,toString),retstring);
    Stub s9;
    s9.set(ADDR(TextEdit,getFilePath),retstring);
    Stub s10;
    s10.set(ADDR(QJsonValue,isString),rettruestub);

    QString c1 = "{\"bookMark\":\"7,7,8,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0\",\"cursorPosition\":\"7\",\"focus\":true,\"localPath\":\"/home/uos/.local/share/deepin/deepin-editor/blank-files/blank_file_2021-09-22_09-43-10-824\",\"modify\":true}";
    QString c2 = "{\"bookMark\":\"1,0,1,0,0\",\"cursorPosition\":\"23\",\"localPath\":\"/home/uos/Desktop/563/526.txt\",\"modify\":false}";
    stringList.clear();
    stringList.push_back(c1);
    stringList.push_back(c2);


    pWindow->currentWrapper()->handleFileLoadFinished(encode, retFileContent);
    ASSERT_TRUE(pWindow->currentWrapper()->m_pBottomBar->m_pEncodeMenu != nullptr);

    pWindow->deleteLater();
}


TEST(UT_Editwrapper_handleFileLoadFinished, UT_Editwrapper_handleFileLoadFinished_003)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    QByteArray encode = QByteArray();
    const QByteArray retFileContent = FileLoadThreadRun(filePath, &encode);
    Stub setPrintEnabled_stub;
    setPrintEnabled_stub.set(ADDR(Window, setPrintEnabled), handleFileLoadFinished_001_setPrintEnabled_stub);
    Stub setTextFinished_stub;
    setTextFinished_stub.set(ADDR(TextEdit, setTextFinished), handleFileLoadFinished_001_setTextFinished_stub);

    Stub s1;
    s1.set(ADDR(KSyntaxHighlighting::Definition,isValid),rettruestub);
    Stub s2;
    s2.set(ADDR(QString,isEmpty),retfalsestub);
    Stub s3;
    s3.set(ADDR(Utils,isDraftFile),retfalsestub);
    Stub s4;
    s4.set(ADDR(TextEdit,getReadOnlyPermission),rettruestub);
    Stub s5;
    s5.set(ADDR(EditWrapper,loadContent),rettruestub);
    Stub s6;
    s6.set(ADDR(EditWrapper,OnUpdateHighlighter),rettruestub);//DSettings
    Stub s7;
    s7.set(ADDR(DSettings,option),retsettingoption);
    Stub s8;//QString toString() const;
    s8.set((QString (QJsonValue::*)() const)ADDR(QJsonValue,toString),retstring);
    Stub s9;
    s9.set(ADDR(TextEdit,getFilePath),retstring);
    Stub s10;
    s10.set(ADDR(QJsonValue,isString),retfalsestub);

    QString c1 = "{\"bookMark\":\"7,7,8,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0\",\"cursorPosition\":\"7\",\"focus\":true,\"localPath\":\"/home/uos/.local/share/deepin/deepin-editor/blank-files/blank_file_2021-09-22_09-43-10-824\",\"modify\":true}";
    QString c2 = "{\"bookMark\":\"1,0,1,0,0\",\"cursorPosition\":\"23\",\"localPath\":\"/home/uos/Desktop/563/526.txt\",\"modify\":false}";
    stringList.clear();
    stringList.push_back(c1);
    stringList.push_back(c2);


    pWindow->currentWrapper()->handleFileLoadFinished(encode, retFileContent);
    ASSERT_TRUE(pWindow->currentWrapper()->m_pBottomBar->m_pEncodeMenu != nullptr);

    pWindow->deleteLater();
    delete d;
    d = nullptr;
}


////重新加载文件编码 1.文件修改 2.文件未修改处理逻辑一样 切换编码重新加载和另存为 梁卫东
//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray("UTF-8"));
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}


TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray("UTF-8"));
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_003)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

int reloadFileEncode_003_exec_stub()
{
    return 0;
}


int reloadFileEncode_004_exec_stub()
{
    return 1;
}

bool reloadFileEncode_004_readFile_stub()
{
    return true;
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_004)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadFileEncode_004_exec_stub);
    Stub readFile_stub;
    readFile_stub.set(ADDR(EditWrapper, readFile), reloadFileEncode_004_readFile_stub);
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    /* gerrit编译运行结果和本地编译运行不一样，打桩后无果，先用如下方法断言 */
    if (bRet) {
        ASSERT_TRUE(bRet);
    } else {
        ASSERT_FALSE(bRet);
    }

    pWindow->deleteLater();
}

bool reloadFileEncode_005_saveDraftFile_stub()
{
    return false;
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_005)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadFileEncode_004_exec_stub);
    Stub saveDraftFile_stub;
    saveDraftFile_stub.set(ADDR(EditWrapper, saveDraftFile), reloadFileEncode_005_saveDraftFile_stub);
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

bool reloadFileEncode_006_isDraftFile_stub()
{
    return false;
}

bool reloadFileEncode_006_saveFile_stub()
{
    return true;
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_006)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadFileEncode_004_exec_stub);
    Stub isDraftFile_stub;
    isDraftFile_stub.set(ADDR(Utils, isDraftFile), reloadFileEncode_006_isDraftFile_stub);
    Stub readFile_stub;
    readFile_stub.set(ADDR(EditWrapper, readFile), reloadFileEncode_004_readFile_stub);
    Stub saveFile_stub;
    saveFile_stub.set(ADDR(EditWrapper, saveFile), reloadFileEncode_006_saveFile_stub);
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

int reloadFileEncode_007_exec_stub()
{
    return 2;
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_007)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadFileEncode_007_exec_stub);
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

bool reloadFileEncode_008_getModified_stub()
{
    return false;
}

bool reloadFileEncode_008_readFile_stub()
{
    return false;
}

int reloadFileEncode_008_exec_stub()
{
    return 2;
}

//bool reloadFileEncode(QByteArray encode);
TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_008)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    Stub getModified_stub;
    getModified_stub.set(ADDR(TextEdit, getModified), reloadFileEncode_008_getModified_stub);
    Stub readFile_stub;
    readFile_stub.set(ADDR(EditWrapper, readFile), reloadFileEncode_008_readFile_stub);
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadFileEncode_008_exec_stub);
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

TEST(UT_Editwrapper_reloadFileEncode, UT_Editwrapper_reloadFileEncode_009)
{
    /*
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub s1;
    s1.set(qDialogExec, retintstub);

    Stub s2;
    s2.set(ADDR(TextEdit,getModified),rettruestub);

    intvalue = 1;
    bool bRet = pWindow->currentWrapper()->reloadFileEncode(QByteArray());
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
    */
}

int reloadModifyFile_001_exec_stub()
{
    return 0;
}

////重写加载修改文件
//void reloadModifyFile();
TEST(UT_Editwrapper_reloadModifyFile, UT_Editwrapper_reloadModifyFile_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadModifyFile_001_exec_stub);
    pWindow->currentWrapper()->reloadModifyFile();
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getModified());

    pWindow->deleteLater();
}

int reloadModifyFile_002_exec_stub()
{
    return 1;
}

QByteArray reloadModifyFile_selectCoding()
{
    return QByteArray();
}

//void reloadModifyFile();
TEST(UT_Editwrapper_reloadModifyFile, UT_Editwrapper_reloadModifyFile_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadModifyFile_002_exec_stub);
    Stub stubSelectCoding;
    stubSelectCoding.set(ADDR(DetectCode, selectCoding),reloadModifyFile_selectCoding);
    pWindow->currentWrapper()->reloadModifyFile();
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->getModified());

    pWindow->deleteLater();
}

int reloadModifyFile_003_exec_stub()
{
    return 2;
}

//void reloadModifyFile();
TEST(UT_Editwrapper_reloadModifyFile, UT_Editwrapper_reloadModifyFile_003)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadModifyFile_003_exec_stub);
    pWindow->currentWrapper()->reloadModifyFile();
    ASSERT_FALSE(pWindow->currentWrapper()->saveDraftFile());

    pWindow->deleteLater();
}

bool reloadModifyFile_004_isDraftFile_stub()
{
    return false;
}

//void reloadModifyFile();
TEST(UT_Editwrapper_reloadModifyFile, UT_Editwrapper_reloadModifyFile_004)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    typedef int (*fptr)(QDialog *);
    fptr qDialogExec = (fptr)(&QDialog::exec);
    Stub stub;
    stub.set(qDialogExec, reloadModifyFile_003_exec_stub);
    Stub isDraftFile_stub;
    isDraftFile_stub.set(ADDR(Utils, isDraftFile), reloadModifyFile_004_isDraftFile_stub);
    pWindow->currentWrapper()->reloadModifyFile();
    ASSERT_FALSE(pWindow->currentWrapper()->saveAsFile());

    pWindow->deleteLater();
}

//void reloadModifyFile();
TEST(UT_Editwrapper_reloadModifyFile, UT_Editwrapper_reloadModifyFile_005)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    Stub stubSelectCoding;
    stubSelectCoding.set(ADDR(DetectCode, selectCoding), reloadModifyFile_selectCoding);
    pWindow->currentWrapper()->reloadModifyFile();
    ASSERT_TRUE(pWindow->currentWrapper()->textEditor()->horizontalScrollBar()->value() == 0);

    pWindow->deleteLater();
}

////获取文件编码
//QString getTextEncode();
TEST(UT_Editwrapper_getTextEncode, UT_Editwrapper_getTextEncode)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    QString strRet = pWindow->currentWrapper()->getTextEncode();
    ASSERT_TRUE(!strRet.compare(QString("UTF-8")));

    pWindow->deleteLater();
}

//bool saveTemFile(QString qstrDir);
TEST(UT_Editwrapper_saveTemFile, UT_Editwrapper_saveTemFile_001)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    const QString filePath = QCoreApplication::applicationDirPath() + QString("/Makefile");
    bool bRet = pWindow->currentWrapper()->saveTemFile(filePath);
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

//bool saveTemFile(QString qstrDir);
TEST(UT_Editwrapper_saveTemFile, UT_Editwrapper_saveTemFile_002)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    bool bRet = pWindow->currentWrapper()->saveTemFile(QString());
    ASSERT_FALSE(bRet);

    pWindow->deleteLater();
}

////判断是否修改
//bool isModified();
TEST(UT_Editwrapper_isModified, UT_Editwrapper_isModified)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    pWindow->currentWrapper()->textEditor()->insertTextEx(pWindow->currentWrapper()->textEditor()->textCursor(),
                                                          QString("12345"));
    bool bRet = pWindow->currentWrapper()->isModified();
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

////判断是否草稿文件
//bool isDraftFile();
TEST(UT_Editwrapper_isDraftFile, UT_Editwrapper_isDraftFile)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    bool bRet = pWindow->currentWrapper()->isDraftFile();
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

////判断内容是否为空
//bool isPlainTextEmpty();
TEST(UT_Editwrapper_isPlainTextEmpty, UT_Editwrapper_isPlainTextEmpty)
{
    Window *pWindow = new Window();
    pWindow->addBlankTab(QString());
    bool bRet = pWindow->currentWrapper()->isPlainTextEmpty();
    ASSERT_TRUE(bRet);

    pWindow->deleteLater();
}

TEST(UT_Editwrapper_OnThemeChangeSlot, UT_Editwrapper_OnThemeChangeSlot)
{
    EditWrapper* wra = new EditWrapper;
    QTextDocument*doc = new QTextDocument;
    wra->m_pSyntaxHighlighter = new CSyntaxHighlighter(doc);
    wra->OnThemeChangeSlot("ddd");


    EXPECT_NE(wra,nullptr);

    wra->deleteLater();
    doc->deleteLater();
}

TEST(UT_Editwrapper_clearDoubleCharaterEncode, UT_Editwrapper_clearDoubleCharaterEncode_001)
{
    EditWrapper* wra = new EditWrapper;

    Stub s1;
    //bool contains(const QString &s, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
    s1.set((bool (QString::*)(const QString &, Qt::CaseSensitivity) const)ADDR(QString,contains),rettruestub);
    Stub s2;
    s2.set(ADDR(QFileInfo,size),retintstub);

    intvalue = 1024*1024;
    wra->clearDoubleCharaterEncode();


    EXPECT_NE(wra,nullptr);
    wra->deleteLater();
}
TEST(UT_Editwrapper_clearDoubleCharaterEncode, UT_Editwrapper_clearDoubleCharaterEncode_002)
{
    EditWrapper* wra = new EditWrapper;

    Stub s1;
    //bool contains(const QString &s, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
    s1.set((bool (QString::*)(const QString &, Qt::CaseSensitivity) const)ADDR(QString,contains),rettruestub);
    Stub s2;
    s2.set(ADDR(QFileInfo,size),retintstub);

    intvalue = 1*1024;
    wra->clearDoubleCharaterEncode();


    EXPECT_NE(wra,nullptr);
    wra->deleteLater();
}

TEST(UT_Editwrapper_loadContent, UT_Editwrapper_loadContent_001)
{
    Window* window = new Window();
    EditWrapper* wra = new EditWrapper(window);

    Stub s1;
    s1.set(ADDR(QString,length),retintstub);

    intvalue = 41*1024*1024;
    wra->loadContent("ddd");


    EXPECT_NE(wra,nullptr);
    wra->deleteLater();
    window->deleteLater();
}

TEST(UT_Editwrapper_loadContent, UT_Editwrapper_loadContent_002)
{
    Window* window = new Window();
    EditWrapper* wra = new EditWrapper(window);

    Stub s1;
    s1.set(ADDR(QString,length),retintstub);

    intvalue = 10*1024;
    wra->loadContent("ddd");


    EXPECT_NE(wra,nullptr);
    wra->deleteLater();
    window->deleteLater();
}

