#!/bin/sh
# It appears that CoreMidiDeviceInfo no longer has native
# methods.
#
# It also appears that getUniqueID has been replaced by
# getdeviceUniqueID, getEndpointUniqueID in CoreMidiDeviceProvider
#
javah -classpath ./target/classes \
    -o ./CoreMidi4J.h \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiClient \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiDestination \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiDeviceProvider \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiDeviceInfo \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiInputPort \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiOutputPort \
    uk.co.xfactorylibrarians.coremidi4j.CoreMidiSource
