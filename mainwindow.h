#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QCloseEvent>
#include <QHash>

#include "manifestconstants.h"
#include "propertydefinition.h"
#include "streamreader.h"
#include "mycheckbox.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class OctalCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void closeEvent (QCloseEvent *event);
    int getOutputState();
    int getOneFileState();
    int getStripXState();
    int getMergeState();
    int getInputDisplayState();
    int getOctalDisplayState();
    int getParsedDisplayState();
    int getStopState();
    int getStartButtonState();
    void blinkStartButton();
//Todo remove    int getContinueButtonState();
//Todo remove     void blinkContinueButton();
    QLineEdit *getVcardLineEdit();
    QPlainTextEdit *getInputEditText();
    QLabel *getInputLabel();
    QLabel *getInputOctalLabel();
    QPlainTextEdit *getInputOctalEditText();
    QLabel *getOutputLabel();
    QPlainTextEdit *getOutputEditText();
    bool getIsClosed();
    int getPropertyHashValue(QString name,versionnumber version);
    int getVersionHashValue(QString name);
    void incrementVcardCount(void);
    int getVcardCount();
    PropertyDefinition *getPtrToPropertyDefinition(int index);
    ~MainWindow();
    char messageBuffer[MAX_MESSAGE_BUFFER];
public slots:
    void handleOutputState(bool checked);
    void handleOneFileState(bool checked);
    void handleStripXState(bool checked);
    void handleMergeState(bool checked);
    void handleDisplayInputState(bool checked);
    void handleDisplayOctalState(bool checked);
    void handleParsedDisplayState(bool checked);
    void handleStopState(bool checked);
    void handleStartButtonState(bool checked);
//Todo remove     void handleContinueButtonState(bool checked);

private:
    Ui::MainWindow *ui;
    QWidget *ptrToMainWidget;
    QHash<QString,propertynumber> propertyNameHash;
    QHash<QString,versionnumber> versionNameHash;
    PropertyDefinition propertyArray[NUMBEROFPROPERTYDEFINNITIONS];
    //layouts
    QVBoxLayout *ptrToMainLayout;
    QVBoxLayout *ptrToInputTextLayout;
    QVBoxLayout *ptrToDebugTextLayout;
    QVBoxLayout *ptrToOutputTextLayout;
    QHBoxLayout *ptrToCheckBoxesLayout;
    QHBoxLayout *ptrToButtonsLayout;
    //widgets
    //controls
    //line edits
    QLabel *ptrToVcardCountLabel;
    QLineEdit *ptrToVCardCount;
    //checkboxes
    MyCheckBox *ptrToOutputCheckBox;
    int outputCheckBoxState;
    MyCheckBox *ptrToMergeCheckBox;
    int mergeCheckBoxState;
    MyCheckBox *ptrToOneFileCheckBox;
    int oneFileCheckBoxState;
    MyCheckBox *ptrToStripXCheckBox;
    int stripXcheckBoxState;
    MyCheckBox *ptrToDisplayInputCheckBox;
    int inputCheckBoxState;

    MyCheckBox *ptrToDisplayOctalCheckBox;
    int octalCheckBoxState;
    MyCheckBox *ptrToDisplayParsedCheckbox;
    int parsedCheckBoxState;
    MyCheckBox *ptrToStopOnVcardCheckbox;
    int stopCheckBoxState;
    //pushbuttonts
//Todo: remove    QPushButton *ptrToContinuePushButton;
//Todo: remove    int continueButtonIsWhite;
//Todo: remove    int continueButtonState;
    QPushButton *ptrToStartPushButton;
    int startButtonIsWhite;
    int startButtonState;
    //PlainTextEdit windows
    QLabel *ptrToInputLabel;
    QLabel *ptrToInputOctalLabel;
    QPlainTextEdit *ptrToInputText;
    QPlainTextEdit *ptrToInputOctalText;
    QLabel *ptrToOutputLabel;
    QPlainTextEdit *ptrToOutputText;
    bool closed;
    //Other
    int cardCount;
//Todo remove     int  continueBlinkCount;
    int  startBlinkCount;

};
#endif // MAINWINDOW_H
