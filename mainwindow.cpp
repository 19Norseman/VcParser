#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycheckbox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //initialize array of property and attrribute definitions
    //name, 2.1 propertycardinality, 2.1 attributecardinality,3 propertycardinality,3 attributecardinality,4 propertycardinality,4 attributecardinality
    propertyArray[unknown_p].setDefinition("",p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[adr_p].setDefinition(ADR_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[agent_p].setDefinition(AGENT_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[anniversary_p].setDefinition(ANNIVERSARY_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_exactlyonemay,a_oneormoremust);
    propertyArray[bday_p].setDefinition(BDAY_NAME,p_exactlyonemay,a_noneallowed,p_exactlyonemay,a_noneallowed,p_exactlyonemay,a_oneormoremay);
    propertyArray[begin_p].setDefinition(BEGIN_NAME,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed);
    propertyArray[caladruri_p].setDefinition(CALADRURI_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[caluri_p].setDefinition(CALURI_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[catergories_p].setDefinition(CATEGORIES_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[class_p].setDefinition(CLASS_NAME,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[clientpidmap_p].setDefinition(CLIENTPIDMAP_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[email_p].setDefinition(EMAIL_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[end_p].setDefinition(END_NAME,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed);
    propertyArray[fburl_p].setDefinition(FBURL_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[fn_p].setDefinition(FN_NAME,p_exactlyonemay,a_oneormoremay,p_exactlyonemust,a_oneormoremay,p_exactlyonemust,a_oneormoremay);
    propertyArray[gender_p].setDefinition(GENDER_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[geo_p].setDefinition(GEO_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[impp_p].setDefinition(IMPP_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[key_p].setDefinition(KEY_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[kind_p].setDefinition(KIND_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[label_p].setDefinition(LABEL_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[lang_p].setDefinition(LANG_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[logo_p].setDefinition(LOGO_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[mailer_p].setDefinition(MAILER_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[member_p].setDefinition(MEMBER_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[n_p].setDefinition(N_NAME,p_exactlyonemust,a_oneormoremay,p_exactlyonemust,a_oneormoremay,p_exactlyonemust,a_oneormoremay);
    propertyArray[name_p].setDefinition(NAME_NAME,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[nickname_p].setDefinition(NICKNAME_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[note_p].setDefinition(NOTE_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[org_p].setDefinition(ORG_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[photo_p].setDefinition(PHOTO_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[prodid_p].setDefinition(PRODID_NAME,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[profile_p].setDefinition(PROFILE_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[related_p].setDefinition(RELATED_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    propertyArray[rev_p].setDefinition(REV_NAME,p_exactlyonemay,a_noneallowed,p_exactlyonemay,a_noneallowed,p_exactlyonemay,a_oneormoremay);
    propertyArray[role_p].setDefinition(ROLE_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[sort_string_p].setDefinition(SORT_STRING_NAME,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay,p_noneallowed,a_noneallowed);
    propertyArray[sound_p].setDefinition(SOUND_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[source_p].setDefinition(SOURCE_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[tel_p].setDefinition(TEL_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[title_p].setDefinition(TITLE_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[tz_p].setDefinition(TZ_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[uid_p].setDefinition(UID_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[url_p].setDefinition(URL_NAME,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay,p_oneormoremay,a_oneormoremay);
    propertyArray[version_p].setDefinition(VERSION_NAME,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed,p_exactlyonemust,a_noneallowed);
    propertyArray[xml_p].setDefinition(XML_NAME,p_noneallowed,a_noneallowed,p_noneallowed,a_noneallowed,p_oneormoremay,a_oneormoremay);
    //initialize property name hash table
    for (int i=1;i<NUMBEROFPROPERTYDEFINNITIONS;i++) {
        propertyNameHash[propertyArray[(propertynumber)i].getName()]=(propertynumber)i;
    }
    //initialize version name hash table
    versionNameHash[VERSION2DOT1_NAME]=v_2dot1;
    versionNameHash[VERSION3_NAME]=v_3;
    versionNameHash[VERSION4_NAME]=v_4;

    cardCount=0;
    startBlinkCount=0;
//Todo remove     continueBlinkCount=0;
    closed=false;
    ui->setupUi(this);
    //create a widget to contain layouts
    ptrToMainWidget=new QWidget();
    //Create an HBOXLayout to hold layouts
    ptrToMainLayout= new QVBoxLayout(ptrToMainWidget);
    //Create an HBoxlayout to hold application Checkboxes
    ptrToCheckBoxesLayout= new QHBoxLayout();
    //Create an HBoxlayout to hold application Pushbuttons
    ptrToButtonsLayout= new QHBoxLayout();
    //create a VBoxlayout to contain Input text edit
    ptrToInputTextLayout=new QVBoxLayout();
    //create an VBox Layout for parsed text edit
    ptrToOutputTextLayout=new QVBoxLayout();
    //create a VBoxlayout to contain Debug text edit
    ptrToDebugTextLayout=new QVBoxLayout();

    //Line Edit for VCARD count
    ptrToVcardCountLabel=new QLabel(W_VCARD_COUNT_LABEL);
    ptrToVCardCount= new QLineEdit(ptrToMainWidget);
    ptrToVCardCount->setToolTip("Displays count of vcards read from input.");
    ptrToVCardCount->setFixedWidth(VCARD_COUNT_WIDTH);
    //Create and initialize checkboxes
    ptrToOutputCheckBox=new MyCheckBox(W_OUTPUT_CHECKBOX,ptrToMainWidget);
    ptrToOutputCheckBox->setToolTip(OUTPUT_CHECKBOX_TOOL_TIP);
    outputCheckBoxState=0;
    ptrToMergeCheckBox=new MyCheckBox(W_MERGE_CHECKBOX,ptrToMainWidget);
    mergeCheckBoxState=0;
    ptrToMergeCheckBox->setToolTip(MERGE_CHECKBOX_TOOL_TIP);
    ptrToDisplayInputCheckBox= new MyCheckBox(W_DISPLAY_INPUT_CHECKBOX,ptrToMainWidget);
    ptrToDisplayInputCheckBox->setToolTip(DISPLAY_INPUT_CHECKBOX_TOOL_TIP);
    inputCheckBoxState=0;
    ptrToDisplayOctalCheckBox= new MyCheckBox(W_DISPLAY_OCTAL_CHECKBOX,ptrToMainWidget);
    octalCheckBoxState=0;
    ptrToDisplayOctalCheckBox->setToolTip(DISPLAY_OCTAL_CHECKBOX_TOOL_TIP);
    ptrToDisplayParsedCheckbox= new MyCheckBox(W_DISPLAY_PARSED_CHECKBOX,ptrToMainWidget);
    parsedCheckBoxState=0;
    ptrToDisplayParsedCheckbox->setToolTip(DISPLAY_PARSED_CHECKBOX_TOOL_TIP);
    ptrToStopOnVcardCheckbox = new MyCheckBox(W_STOP_AFTER_VACARD_CHECKBOX,ptrToMainWidget);
    ptrToStopOnVcardCheckbox->setToolTip(STOP_CHECKBOX_TOOL_TIP);
    stopCheckBoxState=0;
    ptrToOneFileCheckBox=new MyCheckBox(W_ONE_FILE_CHECKBOX,ptrToMainWidget);
    oneFileCheckBoxState=0;
    ptrToOneFileCheckBox->setToolTip(ONE_FILE_CHECKBOX_TOOL_TIP);

    ptrToStripXCheckBox=new MyCheckBox(W_STRIP_X_CHECKBOX,ptrToMainWidget);
    ptrToStripXCheckBox->setToolTip(STRIPX_CHECKBOX_TOOL_TIP);

    stripXcheckBoxState=0;

    //Connect checkbox signals to slots
    connect(ptrToOutputCheckBox,SIGNAL(clicked(bool)),this, SLOT(handleOutputState(bool)));
    connect(ptrToMergeCheckBox,SIGNAL(clicked(bool)),this, SLOT(handleMergeState(bool)));
    connect(ptrToDisplayInputCheckBox,SIGNAL(clicked(bool)),this, SLOT(handleDisplayInputState(bool)));
    connect(ptrToDisplayOctalCheckBox,SIGNAL(clicked(bool)),this, SLOT(handleDisplayOctalState(bool)));
    connect(ptrToDisplayParsedCheckbox,SIGNAL(clicked(bool)),this, SLOT(handleParsedDisplayState(bool)));
    connect(ptrToStopOnVcardCheckbox,SIGNAL(clicked(bool)),this, SLOT(handleStopState(bool)));
    connect(ptrToOneFileCheckBox,SIGNAL(clicked(bool)),this,SLOT(handleOneFileState(bool)));

    connect(ptrToStripXCheckBox,SIGNAL(clicked(bool)),this,SLOT(handleStripXState(bool)));

    //create pushbuttons
//Todo: remove    ptrToContinuePushButton = new QPushButton(W_CONTINUE_BUTTON,ptrToMainWidget);
//Todo: remove    ptrToContinuePushButton->setToolTip("Push to continue from pause or start processing.");
//Todo: remove    connect(ptrToContinuePushButton,SIGNAL(clicked(bool)),this, SLOT(handleContinueButtonState(bool)));
//Todo: remove    continueButtonState=0;
//Todo: remove    continueButtonIsWhite=1;
    ptrToStartPushButton = new QPushButton(W_START_BUTTON,ptrToMainWidget);
    ptrToStartPushButton->setToolTip("Push to start processing or continue from pause.");
    connect(ptrToStartPushButton,SIGNAL(clicked(bool)),this, SLOT(handleStartButtonState(bool)));
    startButtonState=0;
    startButtonIsWhite=0;
    //create a PlainTextEdit to display input
    // character by character as read
    ptrToInputText=new QPlainTextEdit();
    ptrToInputText->setToolTip("Displays text from input stream, byte by byte as read.");
    //Set wrap mode for input PlainTextEdit to do not wrap
    // we want the lines to exactly mimic the input
    ptrToInputText->setLineWrapMode(QPlainTextEdit::NoWrap);
    //create a label for the input text edi
    ptrToInputLabel=new QLabel(W_INPUT_LABEL);
    //create a PlainTextEdit to echo input in octal for debugging
    ptrToInputOctalText=new QPlainTextEdit();
    ptrToInputOctalText->setToolTip("Displays text from input stream byte by byte in unsigned octal.");
    //create a lable for ocatl input edit
    ptrToInputOctalLabel=new QLabel(W_OCTAL_INPUT_LABEL);
    //create a PlainTextEdit for parsed vcard data
    // identifies property name, attributes and value for each vcard content line
    ptrToOutputText=new QPlainTextEdit();
    ptrToOutputText->setToolTip("Display results of parsing input.");
    //create a lable for parsed data
    ptrToOutputLabel=new QLabel(W_PARSED_VCARD_DATA_LABEL);
    //Set wrap mode for parsed PlainTextEdit to do not wrap
    // we want the lines to exactly reflect the parsed data
    ptrToOutputText->setLineWrapMode(QPlainTextEdit::NoWrap);

    //Add the Checkboxes to the layouts
    ptrToCheckBoxesLayout->addWidget(ptrToVcardCountLabel);
    ptrToCheckBoxesLayout->addWidget(ptrToVCardCount);
    ptrToCheckBoxesLayout->addWidget(ptrToOutputCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToMergeCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToStripXCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToOneFileCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToDisplayInputCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToDisplayOctalCheckBox);
    ptrToCheckBoxesLayout->addWidget(ptrToDisplayParsedCheckbox);
    ptrToCheckBoxesLayout->addWidget(ptrToStopOnVcardCheckbox);
    //Add the Pushbuttons to layouts
    ptrToButtonsLayout->addSpacing(BUTTONSPACER);
    ptrToButtonsLayout->addWidget(ptrToStartPushButton);
//Todo: remove    ptrToButtonsLayout->addWidget(ptrToContinuePushButton);
    ptrToButtonsLayout->addSpacing(BUTTONSPACER);

    //add input PlainTextEdit widgets
    ptrToInputTextLayout->addWidget(ptrToInputLabel);
    ptrToInputTextLayout->addWidget(ptrToInputText);
    //add output debug widgets
    ptrToDebugTextLayout->addWidget(ptrToInputOctalLabel);
    ptrToDebugTextLayout->addWidget(ptrToInputOctalText);
    //parsed output widgets
    ptrToOutputTextLayout->addWidget(ptrToOutputLabel);
    ptrToOutputTextLayout->addWidget(ptrToOutputText);
    ptrToMainLayout->addLayout(ptrToCheckBoxesLayout);
    ptrToMainLayout->addLayout(ptrToButtonsLayout);
    ptrToMainLayout->addLayout(ptrToInputTextLayout);
    ptrToMainLayout->addLayout(ptrToDebugTextLayout);
    ptrToMainLayout->addLayout(ptrToOutputTextLayout);
    //set window title
    setWindowTitle(W_MAIN_WINDOW_TITLE);
    //add layout container to window
    setCentralWidget(ptrToMainWidget);

}


PropertyDefinition *MainWindow::getPtrToPropertyDefinition(int index) {
    return &propertyArray[index];
}

int MainWindow::getPropertyHashValue(QString name,versionnumber version) {
    int hashValue=propertyNameHash.value(name);
    //If the cardinality of the property is p_noneallowed, it means this property is undefined for this version
    if (getPtrToPropertyDefinition(hashValue)->getPropertyCardinality(version)==p_noneallowed) {
        hashValue=unknown_p;
    }
   return hashValue;
}

int  MainWindow::getVersionHashValue(QString name) {
    return versionNameHash.value(name);
}



void MainWindow::incrementVcardCount(void) {
    cardCount++;
}
int MainWindow::getVcardCount() {
    return cardCount;
}


bool MainWindow::getIsClosed() {
    return closed;
}

//Get state of one file checkbox
int MainWindow::getOneFileState() {
    return oneFileCheckBoxState;
}

//Get state of stripX checkbox
int MainWindow::getStripXState() {
    return stripXcheckBoxState;
}

//Get state of Display Output checkbox
int MainWindow::getOutputState() {
    return outputCheckBoxState;
}

//Get state of Display Input checkbox
int MainWindow::getMergeState() {
    return mergeCheckBoxState;
}


//Get state of Display Input checkbox
int MainWindow::getInputDisplayState() {
    return inputCheckBoxState;
}


//Get state of Display Octal checkbox
int MainWindow::getOctalDisplayState() {
    return octalCheckBoxState;
}

//Get state of display parsed output checkbox
int MainWindow::getParsedDisplayState(){
    return parsedCheckBoxState;
}

//Get State of Stop checkbox
int MainWindow::getStopState(){
    return stopCheckBoxState;
}

//get state of start button and reset it
int MainWindow::getStartButtonState() {
    int result=startButtonState;
    startButtonState=0;
    return result;
}
void MainWindow::blinkStartButton() {
    if (startBlinkCount++>=STARTBLINKRATE) {
    QPalette pal = ptrToStartPushButton->palette();
        if (startButtonIsWhite) {
            pal.setColor(QPalette::Button, QColor(Qt::blue));
            startButtonIsWhite=0;
        } else {
            pal.setColor(QPalette::Button, QColor(Qt::white));
            startButtonIsWhite=1;
        }
        ptrToStartPushButton->setAutoFillBackground(true);
        ptrToStartPushButton->setPalette(pal);
        ptrToStartPushButton->update();
        startBlinkCount=0;
    }
    return;
}

#if 0
//get state of continue button and reset it
int MainWindow::getContinueButtonState() {
    int result=continueButtonState;
    continueButtonState=0;
    return result;
}

void MainWindow::blinkContinueButton() {
    if (continueBlinkCount++>=CONTINUEBLINKRATE) {
        QPalette pal = ptrToContinuePushButton->palette();
        if (continueButtonIsWhite) {
            pal.setColor(QPalette::Button, QColor(Qt::blue));
            continueButtonIsWhite=0;
        } else {
            pal.setColor(QPalette::Button, QColor(Qt::white));
            continueButtonIsWhite=1;
        }
        ptrToContinuePushButton->setAutoFillBackground(true);
        ptrToContinuePushButton->setPalette(pal);
        ptrToContinuePushButton->update();
        continueBlinkCount=0;
    }
    return;
}
#endif
//Slots to handle UI events
//Checkbox for write output
void MainWindow::handleOutputState(bool checked) {
 Q_UNUSED(checked);
 outputCheckBoxState=ptrToOutputCheckBox->isChecked();
}

void MainWindow::handleOneFileState(bool checked) {
    Q_UNUSED(checked);
    oneFileCheckBoxState=ptrToOneFileCheckBox->isChecked();
}

void MainWindow::handleStripXState(bool checked) {
    Q_UNUSED(checked);
    stripXcheckBoxState=ptrToStripXCheckBox->isChecked();
}

void MainWindow::handleMergeState(bool checked) {
 Q_UNUSED(checked);
 mergeCheckBoxState=ptrToMergeCheckBox->isChecked();
}

//Checkbox for octal display of input for debugging
void MainWindow::handleDisplayInputState(bool checked) {
 Q_UNUSED(checked);
 inputCheckBoxState=ptrToDisplayInputCheckBox->isChecked();
}
//Checkbox for octal display of input for debugging
void MainWindow::handleDisplayOctalState(bool checked) {
 Q_UNUSED(checked);
 octalCheckBoxState=ptrToDisplayOctalCheckBox->isChecked();
}
//Checkbox for formatted display of parsed data
void MainWindow::handleParsedDisplayState(bool checked) {
    Q_UNUSED(checked);
    parsedCheckBoxState=ptrToDisplayParsedCheckbox->isChecked();
}
//Checkbox to stop after every vcard
void MainWindow::handleStopState(bool checked) {
    Q_UNUSED(checked);
    stopCheckBoxState = ptrToStopOnVcardCheckbox->isChecked();
}

//Slot to handle push button to start vcard processing
void MainWindow::handleStartButtonState(bool checked) {
    Q_UNUSED(checked);
    startButtonState=true;
}

#if 0
//slot to handle Push button to continue vcard processing
void MainWindow::handleContinueButtonState(bool checked) {
    Q_UNUSED(checked);
    continueButtonState=true;
}
#endif

QPlainTextEdit *MainWindow::getInputEditText() {
    return ptrToInputText;
}

QPlainTextEdit *MainWindow::getInputOctalEditText() {
    return ptrToInputOctalText;
}

QLabel *MainWindow::getInputLabel() {
    return ptrToInputLabel;
}

QLabel *MainWindow::getInputOctalLabel() {
    return ptrToInputOctalLabel;
}


QPlainTextEdit *MainWindow::getOutputEditText() {
    return ptrToOutputText;
}
QLabel *MainWindow::getOutputLabel() {
    return ptrToOutputLabel;
}

QLineEdit *MainWindow::getVcardLineEdit() {
    return ptrToVCardCount;
}

MainWindow::~MainWindow()
{
    delete ptrToVcardCountLabel;
    delete ptrToVCardCount;
    delete ptrToOutputText;
    delete ptrToOutputLabel;
    delete ptrToInputOctalText;
    delete ptrToInputText;
    delete ptrToInputOctalLabel;
    delete ptrToInputLabel;
//TODO remove    delete ptrToContinuePushButton;
    delete ptrToStartPushButton;
    delete ptrToOutputCheckBox;
    delete ptrToStopOnVcardCheckbox;
    delete ptrToDisplayParsedCheckbox;
    delete ptrToDisplayInputCheckBox;
    delete ptrToDisplayOctalCheckBox;
    delete ptrToCheckBoxesLayout;
    delete ptrToInputTextLayout;
    delete ptrToDebugTextLayout;
    delete ptrToOutputTextLayout;
    delete ptrToMainLayout;
    delete ptrToMainWidget;
    delete ui;
}


void MainWindow::closeEvent (QCloseEvent *event)
{
        closed=true;
        event->accept();

}
