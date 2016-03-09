/**
 * Title:        CoreMIDI4J
 * Description:  Core MIDI Device Provider for Java on OS X
 * Copyright:    Copyright (c) 2015-2016
 * Company:      x.factory Librarians
 *
 * @author Derek Cook
 *
 * CoreMIDI4J is an open source Service Provider Interface for supporting external MIDI devices on MAC OS X
 *
 * This file is part of the XCODE project that provides the native implementation of CoreMIDI4J
 *
 * CREDITS - This library uses principles established by OSXMIDI4J, but converted so it operates at the JNI level with no additional libraries required
 *
 */

#include "CoreMidiDeviceProvider.h"

/////////////////////////////////////////////////////////
// Native functions for CoreMidiDeviceProvider
/////////////////////////////////////////////////////////

/*
 * Gets the number of MIDI sources provided by the Core MIDI system
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getNumberOfSources
 * Signature: ()I
 *
 * @param env		The JNI environment
 * @param obj   The reference to the java object instance that called this native method
 *
 * @return      The number of MIDI sources provided by the Core MIDI system
 *
 */

JNIEXPORT jint JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getNumberOfSources(JNIEnv *env, jobject obj) {

  return (jint) MIDIGetNumberOfSources();

}

/*
 * Gets the number of MIDI destinations provided by the Core MIDI system
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getNumberOfDestinations
 * Signature: ()I
 *
 * @param env    The JNI environment
 * @param obj    The reference to the java object instance that called this native method
 *
 * @return       The number of MIDI destinations provided by the Core MIDI system
 *
 */

JNIEXPORT jint JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getNumberOfDestinations(JNIEnv *env, jobject obj) {

  return (jint) MIDIGetNumberOfDestinations();

}

/*
 * Gets the specified Core MIDI Source
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getSource
 * Signature: (I)I
 *
 * @param env            The JNI environment
 * @param obj            The reference to the java object instance that called this native method
 * @param sourceIndex    The index of the MIDI source to get
 *
 * @return               The specified Core MIDI Source
 *
 * @throws               CoreMidiEXception if the source index is not valid
 *
 */

JNIEXPORT jint JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getSource(JNIEnv *env, jobject obj, jint sourceIndex) {

  if ( sourceIndex >= MIDIGetNumberOfSources() ) {

    ThrowException(env,CFSTR("MIDIGetSource"),sourceIndex);

  }

  return MIDIGetSource(sourceIndex);

}

/*
 * Gets the specified Core MIDI Destination
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getDestination
 * Signature: (I)I
 *
 * @param env                   The JNI environment
 * @param obj                   The reference to the java object instance that called this native method
 * @param destinationIndex      The index of the MIDI destination to get
 *
 * @return                      The specified Core MIDI Destination
 *
 * @throws                      CoreMidiEXception if the destination index is not valid
 *
 */

JNIEXPORT jint JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getDestination(JNIEnv *env, jobject obj, jint destinationIndex) {

  if ( destinationIndex >= MIDIGetNumberOfDestinations() ) {

    ThrowException(env,CFSTR("MIDIGetDestination"), destinationIndex);

  }

  return MIDIGetDestination(destinationIndex);

}

/*
 * Gets the unique ID (UID) of the specified end point
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getUniqueID
 * Signature: (I)I
 *
 * @param env                   The JNI environment
 * @param obj                   The reference to the java object instance that called this native method
 * @param endPointReference     The end point reference
 *
 * @return                      The unique ID (UID) of the specified end point
 *
 */

JNIEXPORT jint JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getUniqueID(JNIEnv *env, jobject obj, jint endPointReference) {

  SInt32 uid = 0;

  MIDIObjectGetIntegerProperty(endPointReference, kMIDIPropertyUniqueID, &uid);

  return uid;

}

/*
 * Creates and gets a MidiDevice.Info object for the specified end point reference
 *
 * Class:     com_coremidi4j_CoreMidiDeviceProvider
 * Method:    getMidiDeviceInfo
 * Signature: (I)Ljavax/sound/midi/MidiDevice/Info;
 *
 * @param env                   The JNI environment
 * @param obj                   The reference to the java object instance that called this native method
 * @param endPointReference     The end point reference
 *
 * @return                      A MidiDevice.Info object for the specified end point reference
 *
 */

JNIEXPORT jobject JNICALL Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiDeviceProvider_getMidiDeviceInfo(JNIEnv *env, jobject obj, jint endPointReference) {

  CFStringRef name = NULL;
  CFStringRef deviceName = NULL;
  CFStringRef	description = NULL;
  CFStringRef manufacturer = NULL;
  SInt32 version;
  SInt32 uid;
  
  // Temp for debugging
  OSStatus status1;
  OSStatus status2;
  OSStatus status3;
  OSStatus status4;
  OSStatus status5;
  OSStatus status6;

  // Find the Java CoreMIDIDeviceInfo class and its constructor
  jclass javaClass = env->FindClass("uk/co/xfactorylibrarians/coremidi4j/CoreMidiDeviceInfo");
  jmethodID constructor = env->GetMethodID(javaClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)V");

  // Get the device properties
  status1 = MIDIObjectGetStringProperty(endPointReference, kMIDIPropertyName, &name);
  status2 = MIDIObjectGetStringProperty(endPointReference, kMIDIPropertyName, &deviceName); // Get this again in case our string build fails
  status3 = MIDIObjectGetStringProperty(endPointReference, kMIDIPropertyModel, &description);
  status4 = MIDIObjectGetStringProperty(endPointReference, kMIDIPropertyManufacturer, &manufacturer);
  status5 = MIDIObjectGetIntegerProperty(endPointReference, kMIDIPropertyDriverVersion, &version);
  status6 = MIDIObjectGetIntegerProperty(endPointReference, kMIDIPropertyUniqueID, &uid);

  const char *debugName = CFStringGetCStringPtr ( name, CFStringGetSystemEncoding() );
  const char *debugDescription = CFStringGetCStringPtr ( description, CFStringGetSystemEncoding() );
  const char *debugManufacturer = CFStringGetCStringPtr ( manufacturer, CFStringGetSystemEncoding() );

  printf(" ** Debug - End Point Ref: %8.8x, %8.8x\n",0, endPointReference);
  printf(" ** Debug - Name         : %8.8x, %s\n",status1, ( debugName         != NULL ) ? debugName         : "NULL Pointer");
  printf(" ** Debug - Description  : %8.8x, %s\n",status3, ( debugDescription  != NULL ) ? debugDescription  : "NULL Pointer");
  printf(" ** Debug - Manufacturer : %8.8x, %s\n",status4, ( debugManufacturer != NULL ) ? debugManufacturer : "NULL Pointer");
  printf(" ** Debug - Version      : %8.8x, %8.8x\n",status5, version);
  printf(" ** Debug - UID          : %8.8x, %8.8x\n",status6, uid);

  CFMutableStringRef buildName = CFStringCreateMutable(NULL, 0);

  // Add "CoreMIDI4J - " to the start of our device name if we can
  if (buildName) {

    CFStringAppend(buildName, CFSTR("CoreMIDI4J - "));
    CFStringAppend(buildName, name);

    // Overwrite the deviceName with our updated one
    deviceName = CFStringCreateCopy(NULL, buildName);

    // And release the temporary string
    CFRelease(buildName);

  }

  // Create the Java Object
  jobject info = env->NewObject(javaClass,
                                constructor,
                                env->NewStringUTF(CFStringGetCStringPtr(deviceName, CFStringGetSystemEncoding())),
                                env->NewStringUTF(CFStringGetCStringPtr(manufacturer, CFStringGetSystemEncoding())),
                                env->NewStringUTF(CFStringGetCStringPtr(description, CFStringGetSystemEncoding())),
                                version,
                                endPointReference,
                                uid);

  return info;

}

