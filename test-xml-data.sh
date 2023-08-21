#!/bin/sh
#
# version 1
#
set -e

DIR=tests/gama-g3/input/sablino1910
XSD=./xml/gnu-gama-data.xsd
FLS="sablino1910-obs.xml sablino1910-adj.xml"

for f in $FLS 
do
    echo $DIR/$f
    #xmllint --schema $XSD --noout $DIR/$f
done


# for g in @INPUT_FILES@
# do
#   xmllint --schema @GAMA_XML@/gnu-gama-data.xsd --noout @G3_INPUT@/$g.xml
#   xmllint --schema @GAMA_XML@/gnu-gama-data.xsd --noout @G3_INPUT@/$g-adj.xml
# done
