# VcParser
vcard, vcf, parser and manager
This repository contains a Qt Creator C++ implementation of a vcard (vcf) parser and merger.
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
6) Optionally merges duplicates when creating output file(s).
   Merge means, all vcards with the exact same value of N property are merged into 1 vcard.
   To provide the greatest acceptability to vcard readers the merged version
   is forced to vcard version 2.1. Merging is accomplished by taking the
   first encountered vcard with a given value of the N property, designated the source, and comparing
   it to all other vcards with same value of the N property, designated targets.
   a) If a target has a property that is not in the source, the target property is
      added to the source.
   b) If the target has a property that is in the source, but the value of the target
      property differs from the source property AND the allowed cardinality of the
      property is "one or more", the target property is added to the source.
   Only the source vcard is written to the output.
