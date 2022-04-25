#ifndef PROPERTYDEFINITION_H
#define PROPERTYDEFINITION_H
#include <QString>
#include <QHash>

#include "manifestconstants.h"

class PropertyDefinition
{
public:
    PropertyDefinition();
    ~PropertyDefinition();
    void setDefinition(QString name="",
                       p_cardinality v_dot1PCardinality=p_noneallowed,a_cardinality v_dot1ACardinality=a_noneallowed,
                       p_cardinality v_3PCardinality=p_noneallowed,a_cardinality v_3ACardinality=a_noneallowed,
                       p_cardinality v_4PCardinality=p_noneallowed,a_cardinality v_4ACardinality=a_noneallowed);
    QString getName();
    p_cardinality getPropertyCardinality(versionnumber currversion);
    a_cardinality getAttributeCardinality(versionnumber currversion);
//private:
QString propertyName="";
p_cardinality  v_dot1PropertyCardinality=p_noneallowed;
a_cardinality  v_dot1AttributeCardinality=a_noneallowed;
p_cardinality  v_3PropertyCardinality=p_noneallowed;
a_cardinality  v_3AttributeCardinality=a_noneallowed;
p_cardinality  v_4PropertyCardinality=p_noneallowed;
a_cardinality  v_4AttributeCardinality=a_noneallowed;
};

#endif // PROPERTYDEFINITION_H
