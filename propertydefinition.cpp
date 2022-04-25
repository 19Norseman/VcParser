#include "propertydefinition.h"

PropertyDefinition::PropertyDefinition()
{
    setDefinition();
}


PropertyDefinition::~PropertyDefinition()
{

}

void PropertyDefinition::setDefinition(QString name,
                                       p_cardinality v_2dot1PCardinality,a_cardinality v_2dot1ACardinality,
                                       p_cardinality v_3PCardinality,a_cardinality v_3ACardinality,
                                       p_cardinality v_4PCardinality,a_cardinality v_4ACardinality
                                       ) {
    propertyName=name;
    v_dot1PropertyCardinality=v_2dot1PCardinality;
    v_dot1AttributeCardinality=v_2dot1ACardinality;
    v_3PropertyCardinality=v_3PCardinality;
    v_3AttributeCardinality=v_3ACardinality;
    v_4PropertyCardinality=v_4PCardinality;
    v_4AttributeCardinality=v_4ACardinality;
}
QString PropertyDefinition::getName() {
    return propertyName;
}
p_cardinality PropertyDefinition::getPropertyCardinality(versionnumber currversion) {
    p_cardinality result;
    switch (currversion) {
    case v_2dot1:
         result=v_dot1PropertyCardinality;
         break;
    case v_3:
        result=v_3PropertyCardinality;
        break;
    case v_4:
        result=v_4PropertyCardinality;
        break;
     default:
        result=v_dot1PropertyCardinality;
        break;
     }
    return result;
}

a_cardinality PropertyDefinition::getAttributeCardinality(versionnumber currversion) {
    a_cardinality result;
    switch (currversion) {
    case v_2dot1:
        result=v_dot1AttributeCardinality;
        break;
    case v_3:
         result=v_3AttributeCardinality;
        break;
    case v_4:
         result=v_4AttributeCardinality;
        break;
    default:
        result=v_dot1AttributeCardinality;
        break;
     }
    return result;
}
