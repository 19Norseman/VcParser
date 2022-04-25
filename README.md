# VcParser
vcard, vcf, parser and manager
This repository contains an Qt Creator C++ implementation of a vcard (vcf) parser and merger.
It is a starting point for managing a vcard (vcf) collection.
The implementation provides the following services.
1) A liberal vcf parser for vcard version 2.1,3.0 and 4.0. Liberal means it provides
   basic syntax checkin but allows processing of unknown or experimental properties.
2) Optionally writes parsed, normalized input to a single  or multiple vcf files.
   Normalized means that all properties and parameters/attributes have been forced
   to uppercase and values for N and Phone properties have been converted to a standard
   format.
3) Optionally displays input in human readable as text and octal bytes.
4) Optionally displays parsed output by property, attribute/parameter, value.
5) Optionally strips all XI- , experimental properties.
