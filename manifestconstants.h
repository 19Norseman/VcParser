#ifndef MANIFESTCONSTANTS_H
#define MANIFESTCONSTANTS_H
#include <stdexcept>
#include "license.h"

#define PREVIOUS_LENGTH 4
#define PREVIOUS_END (PREVIOUS_LENGTH-1)

enum versionnumber {
    v_none,
    v_2dot1,
    v_3,
    v_4
};

#define EXPERIMENTALPROPERTY "X-"

enum propertynumber {
    unknown_p,
    adr_p,
    agent_p,
    anniversary_p,
    bday_p,
    begin_p,
    caladruri_p,
    caluri_p,
    catergories_p,
    class_p,
    clientpidmap_p,
    email_p,
    end_p,
    fburl_p,
    fn_p,
    gender_p,
    geo_p,
    impp_p,
    key_p,
    kind_p,
    label_p,
    lang_p,
    logo_p,
    mailer_p,
    member_p,
    n_p,
    name_p,
    nickname_p,
    note_p,
    org_p,
    photo_p,
    prodid_p,
    profile_p,
    related_p,
    rev_p,
    role_p,
    sort_string_p,
    sound_p,
    source_p,
    tel_p,
    title_p,
    tz_p,
    uid_p,
    url_p,
    version_p,
    xml_p
};

enum p_cardinality {
    p_noneallowed,
    p_exactlyonemust,
    p_exactlyonemay,
    p_oneormoremust,
    p_oneormoremay
};


enum a_cardinality {
    a_noneallowed,
    a_exactlyonemust,
    a_exactlyonemay,
    a_oneormoremust,
    a_oneormoremay
};

enum itemError {
    noerror,
    emptyresult,
    successHasAttributes,
    successHasValue,
    successEol,
    successEOF,
    failure_cardinality,
    failure
};

enum itemErrorLevel {
    levelwarning,
    levelnotfatal,
    levelfatal
};

enum States {
    Blank,
    notBlank,
    hasProperty,
    hasAttribute,
    hasValue,
    done
};

enum encodingType {
    none,
    quotedprintable,
    base64
};

//Version constants
#define NUMBEROFVERSIONS (v_4+1) //includes v_none
#define VERSION2DOT1_NAME "2.1"
#define VERSION3_NAME "3.0"
#define VERSION4_NAME "4.0"

//PROPERTY CONSTANTS
#define NUMBEROFPROPERTYDEFINNITIONS (xml_p+1) //includes unknow
#define ADR_NAME "ADR"
#define AGENT_NAME "AGENT"
#define ANNIVERSARY_NAME "ANNIVERSARY"
#define BDAY_NAME "BDAY"
#define BEGIN_NAME "BEGIN"
#define CALADRURI_NAME "CALADRURI"
#define CALURI_NAME "CALURI"
#define CATEGORIES_NAME "CATAGORIES"
#define CLASS_NAME "CLASS"
#define CLIENTPIDMAP_NAME "CLIENTPIDMAP"
#define EMAIL_NAME "EMAIL"
#define END_NAME "END"
#define FBURL_NAME "FBURL"
#define FN_NAME "FN"
#define GENDER_NAME "GENDER"
#define GEO_NAME "GEO"
#define IMPP_NAME "IMPP"
#define KEY_NAME "KEY"
#define KIND_NAME "KIND"
#define LABEL_NAME "LABEL"
#define LANG_NAME "LANG"
#define LOGO_NAME "LOGO"
#define MAILER_NAME "MAILER"
#define MEMBER_NAME "MEMBER"
#define N_NAME "N"
#define NAME_NAME "NAME"
#define NICKNAME_NAME "NICKNAME"
#define NOTE_NAME "NOTE"
#define ORG_NAME "ORG"
#define PHOTO_NAME "PHOTO"
#define PRODID_NAME "PRODID"
#define PROFILE_NAME "PROFILE"
#define RELATED_NAME "RELATED"
#define REV_NAME "REV"
#define ROLE_NAME "ROLE"
#define SORT_STRING_NAME "SORT-STRING"
#define SOUND_NAME "SOUND"
#define SOURCE_NAME "SOURCE"
#define TEL_NAME "TEL"
#define TITLE_NAME "TITLE"
#define TZ_NAME "TZ"
#define UID_NAME "UID"
#define URL_NAME "URL"
#define VERSION_NAME "VERSION"
#define XML_NAME "XML"

//ASCII & character consants
#define ENEDOFFILE 0
#define CARRIAGE_RETURN '\r'
#define NEW_LINE '\n'
#define SPACE ' '
#define HORIZONTAL_TAB '\t'
#define QUOTED_PRINTABLE_FOLDING_SEQUENCE "=\r\n"
#define FOLDLENGTH 4
#define GROUP_TERMINATOR '.'
#define ENDOFVALUE '\n'
#define STARTOFATTRIBUTE ';'
#define STARTOFVALUE ':'
//#define ENDOFPROPERTY ';'
//#define ENDOFPROPERTIES ':'
#define QUOTED_PRINTABLE_ESCAPE '='
#define BASE64NAME "BASE64"
#define QUOTEDPRINTABLENAME "QUOTED-PRINTABLE"



//Literal Strings
#define OUTPUT_CHECKBOX_TOOL_TIP "Check if you want output written to file"
#define MERGE_CHECKBOX_TOOL_TIP "Check if you want to merge duplcates.\r\nIf unchecked input is parsed for correctness\r\nand possibly written to output."
#define DISPLAY_INPUT_CHECKBOX_TOOL_TIP "Check if you want input displayed for debugging.\r\nWARNING: slow!"
#define DISPLAY_OCTAL_CHECKBOX_TOOL_TIP "Check if you want input displayed in octal for debugging.\r\nWARNING: slow!"
#define DISPLAY_PARSED_CHECKBOX_TOOL_TIP    "Check if you want parsed values displayed for debugging.\r\nWARNING: slow!"
#define STOP_CHECKBOX_TOOL_TIP "Check if you want processing to pause after every vcard.\r\nUseful for debugging.\r\nClick Continue or Start to resume Processing"
#define ONE_FILE_CHECKBOX_TOOL_TIP "Check if you want output vcf files in one file, else they are in individual files."
#define STRIPX_CHECKBOX_TOOL_TIP "Check if you want all custom properties, \"X-\", stripped."
#define INPUT_FILE_DIALOG_TITLE "Select VCF File to process"
#define OUTPUT_FILE_DIALOG_TITLE "Select Output file"
#define OUTPUT_DIRECTORY_DIALOG_TITLE "Select Output directory"
#define FILE_SEARCH_PATH "/home"
#define VCF_FILE_WILD_CARD "*.vcf"
#define MB_MAIN_CLOSED_MESSAGE "Main: User canceld or closed. Application will exit."
#define MB_MAIN_EOF_MESSAGE "MAIN: Exited AT EOF"
#define W_VCARD_COUNT_LABEL "Count of vards read:"
#define VCARD_COUNT_WIDTH 50
#define W_OUTPUT_CHECKBOX "Write output"
#define W_MERGE_CHECKBOX "Merge duplicates"
#define W_DISPLAY_INPUT_CHECKBOX "Display input"
#define W_DISPLAY_OCTAL_CHECKBOX "Display octal"
#define W_DISPLAY_PARSED_CHECKBOX "Display parsed"
#define W_STOP_AFTER_VACARD_CHECKBOX "Stop after vcard"
#define W_CONTINUE_BUTTON "Continue"
#define W_START_BUTTON "Start/Continue"
#define W_INPUT_LABEL "Vcard Input"
#define W_OCTAL_INPUT_LABEL "Vcard Octal Input"
#define W_PARSED_VCARD_DATA_LABEL "Vcard Data"
#define W_MAIN_WINDOW_TITLE "Vcard Parser"
#define W_ONE_FILE_CHECKBOX "One output file"
#define W_STRIP_X_CHECKBOX "Strip X properties"



//Result Strings
//Note result string have format "item type: text"
// If passed from lower level item to higher level item you may get "item type:item type: text"
#define MAX_MESSAGE_BUFFER 1024
#define PROPDEF_ERROR "Error initialize property definitions"
#define MAIN_VCARD_ERROR "Main: Bad Vcard: "
#define MAIN_DONE "Main Done: "
#define VALUE_EOF_ERROR "Value: EOF while reading value"
#define VALUE_BLANK_ERROR "Value: Value is blank or empty."
#define VALUE_READ_SUCCESS "Value: Read value."
#define ATTRIBUTE_EOF_ERROR "Attribute: EOF while reading attribute."
#define ATTRIBUTE_SUCCESS "Attribute: Attribute has a value."
#define ATTRIBUTE_NO_VALUE_ERROR "Attribute: Attribute has no value."
#define PROPERTY_EOF_SUCCESS "Read all vcards in input."
#define PROPERTY_EOF_ERROR "Property: EOF while reading property"
#define PROPERTY_BLANK_LINE "Property: Blank line while reading property"
#define PROPERTY_NO_VALUE_ERROR "Property: Property without value."
#define PROPERTY_NO_END_ERROR "Property: Text without end of property."
#define PROPERTY_BLANK_ERROR "Property: Blank property"
#define CONTENTLINE_EOF "ContentLine: EOF"
#define VCARD_PROPERTY_CARDINALITY_ERROR "Vcard %i: %s property cardinality error. Cardinality is %i."
#define VCARD_ATTRIBUTE_CARDINALITY_ERROR "Vcard %i: Property %s attribute cardinality error. Attribute cardinality is %i."
#define VCARD_BEGIN_CARDINALITY_ERROR "Vcard: BEGIN cardinality is incorrect."
#define VCARD_BEGIN_ATTRIBUTE_CARDINALITY_ERROR "Vcard: BEGIN attribute cardinalithy is incorrect."
#define VCARD_VERSION_CARDINALITY_ERROR "Vcard: VERSION cardinality is incorrect."
#define VCARD_FN_CARDINALITY_ERROR "Vcard: FN cardinality is incorrect."
#define VCARD_SUCCESS "VCARD: Read VCARD"

//Parsed output strings
#define VALUE_LABEL "\r**VALUE**:"
#define ATTRIBUTE_LABEL "\r**Attribute**"
#define GROUP_LABEL "\r**Group**:"
#define PROPERTY_LABEL "\r**Property**:"


//Random constants
#define BUTTONSPACER 600
//TODO remove #define CONTINUEBLINKRATE 3
#define STARTBLINKRATE 4
#define TEXTCHUNKSIZE 128   //wild guess at an appropriate value



#endif // MANIFESTCONSTANTS_H
