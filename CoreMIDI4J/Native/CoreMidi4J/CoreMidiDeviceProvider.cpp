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

  MIDIDeviceRef deviceReference       = NULL;
  CFStringRef   deviceName            = NULL;
  CFStringRef   deviceManufacturer    = NULL;
  CFStringRef   deviceModel           = NULL;
  CFStringRef   deviceOffline         = NULL;
  SInt32        deviceUniqueID        = 0;
  SInt32        deviceDriverVersion   = 0;

  MIDIEntityRef entityReference       = NULL;
  CFStringRef   entityName            = NULL;
  CFStringRef   entityManufacturer    = NULL;
  CFStringRef   entityModel           = NULL;
  CFStringRef   entityOffline         = NULL;
  SInt32        entityUniqueID        = 0;
  SInt32        entityDriverVersion   = 0;

  // End point reference is in method parameters
  CFStringRef   endpointName          = NULL;
  CFStringRef   endpointManufacturer  = NULL;
  CFStringRef   endpointModel         = NULL;
  CFStringRef   endpointOffline       = NULL;
  SInt32        endpointUniqueID      = 0;
  SInt32        endpointDriverVersion = 0;
  
  // Find the Java CoreMIDIDeviceInfo class and its constructor
  jclass javaClass = env->FindClass("uk/co/xfactorylibrarians/coremidi4j/CoreMidiDeviceInfo");
  jmethodID constructor = env->GetMethodID(javaClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;IILjava/lang/String;II)V");

  // Get the endpoint properties
  MIDIObjectGetStringProperty (endPointReference, kMIDIPropertyName,          &endpointName);
  MIDIObjectGetStringProperty (endPointReference, kMIDIPropertyModel,         &endpointModel);
  MIDIObjectGetStringProperty (endPointReference, kMIDIPropertyManufacturer,  &endpointManufacturer);
  MIDIObjectGetStringProperty (endPointReference, kMIDIPropertyOffline,       &endpointOffline);
  MIDIObjectGetIntegerProperty(endPointReference, kMIDIPropertyUniqueID,      &endpointUniqueID);
  MIDIObjectGetIntegerProperty(endPointReference, kMIDIPropertyDriverVersion, &endpointDriverVersion);

  // Get the entity properties
  MIDIEndpointGetEntity(endPointReference, &entityReference);

  MIDIObjectGetStringProperty (entityReference, kMIDIPropertyName,          &entityName);
  MIDIObjectGetStringProperty (entityReference, kMIDIPropertyModel,         &entityModel);
  MIDIObjectGetStringProperty (entityReference, kMIDIPropertyManufacturer,  &entityManufacturer);
  MIDIObjectGetStringProperty (entityReference, kMIDIPropertyOffline,       &entityOffline);
  MIDIObjectGetIntegerProperty(entityReference, kMIDIPropertyUniqueID,      &entityUniqueID);
  MIDIObjectGetIntegerProperty(entityReference, kMIDIPropertyDriverVersion, &entityDriverVersion);

  // Get the device properties
  MIDIEntityGetDevice(entityReference, &deviceReference);

  MIDIObjectGetStringProperty (deviceReference, kMIDIPropertyName,          &deviceName); // Get this again in case our string build fails
  MIDIObjectGetStringProperty (deviceReference, kMIDIPropertyModel,         &deviceModel);
  MIDIObjectGetStringProperty (deviceReference, kMIDIPropertyManufacturer,  &deviceManufacturer);
  MIDIObjectGetStringProperty (deviceReference, kMIDIPropertyOffline,       &deviceOffline);
  MIDIObjectGetIntegerProperty(deviceReference, kMIDIPropertyUniqueID,      &deviceUniqueID);
  MIDIObjectGetIntegerProperty(deviceReference, kMIDIPropertyDriverVersion, &deviceDriverVersion);
  
  long numberOfEntities = MIDIDeviceGetNumberOfEntities(deviceReference);
  
  // Uncomment these lines if you wish to view information as received on the native side during debugging.
  //std::cout << "End Point " << std::endl;
  //std::cout << "  End Point Reference                  " << endPointReference << std::endl;
  //std::cout << "  End Point kMIDIPropertyName          " << CFStringGetCStringPtr (endpointName, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  End Point kMIDIPropertyModel         " << CFStringGetCStringPtr (endpointModel, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  End Point kMIDIPropertyManufacturer  " << CFStringGetCStringPtr (endpointManufacturer, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  End Point kMIDIPropertyOffline       " << endpointOffline << std::endl;
  //std::cout << "  End Point kMIDIPropertyUniqueID      " << endpointUniqueID << std::endl;
  //std::cout << "  End Point kMIDIPropertyDriverVersion " << endpointDriverVersion << std::endl;
  //std::cout << std::endl;
  //std::cout << "  Entity    Reference                  " << entityReference << std::endl;
  //std::cout << "  Entity    kMIDIPropertyName          " << CFStringGetCStringPtr (entityName, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Entity    kMIDIPropertyModel         " << CFStringGetCStringPtr (entityModel, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Entity    kMIDIPropertyManufacturer  " << CFStringGetCStringPtr (entityManufacturer, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Entity    kMIDIPropertyOffline       " << entityOffline << std::endl;
  //std::cout << "  Entity    kMIDIPropertyUniqueID      " << entityUniqueID << std::endl;
  //std::cout << "  Entity    kMIDIPropertyDriverVersion " << entityDriverVersion << std::endl;
  //std::cout << std::endl;
  //std::cout << "  Device    Reference                  " << deviceReference << std::endl;
  //std::cout << "  Device    kMIDIPropertyName          " << CFStringGetCStringPtr (deviceName, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Device    kMIDIPropertyModel         " << CFStringGetCStringPtr (deviceModel, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Device    kMIDIPropertyManufacturer  " << CFStringGetCStringPtr (deviceManufacturer, CFStringGetSystemEncoding() ) << std::endl;
  //std::cout << "  Device    kMIDIPropertyOffline       " << deviceOffline << std::endl;
  //std::cout << "  Device    kMIDIPropertyUniqueID      " << deviceUniqueID << std::endl;
  //std::cout << "  Device    kMIDIPropertyDriverVersion " << deviceDriverVersion << std::endl;
  //std::cout << std::endl;
  //std::cout << "  Number of entities                   " << numberOfEntities << std::endl;
  //std::cout << std::endl;

  // Build the Device Info name. Add "CoreMIDI4J - " to the start of our device name if we can
  // And if the device has more than one entity then add the entity name
  CFMutableStringRef buildName = CFStringCreateMutable(NULL, 0);
  CFStringRef deviceInfoName;
  
  if ( buildName != NULL ) {

    CFStringAppend(buildName, deviceName);
    
    if ( numberOfEntities > 1 ) {
      
      CFStringAppend(buildName, CFSTR(" "));
      CFStringAppend(buildName, entityName);
      
    }
    
    // Overwrite the deviceName with our updated one
    deviceInfoName = CFStringCreateCopy(NULL, buildName);

    // And release the temporary string
    CFRelease(buildName);

  }

  const char *deviceInfoNamePtr         = CFStringGetCStringPtr ( deviceInfoName,     CFStringGetSystemEncoding() );
  const char *deviceInfoManufacturerPtr = CFStringGetCStringPtr ( deviceManufacturer, CFStringGetSystemEncoding() );
  const char *deviceInfoDescriptionPtr  = CFStringGetCStringPtr ( deviceModel,        CFStringGetSystemEncoding() );
  
  const char *deviceNamePtr             = CFStringGetCStringPtr ( deviceName,         CFStringGetSystemEncoding() );
  const char *entityNamePtr             = CFStringGetCStringPtr ( entityName,         CFStringGetSystemEncoding() );
  const char *endPointNamePtr           = CFStringGetCStringPtr ( endpointName,       CFStringGetSystemEncoding() );
  
  // TODO - Have seen reference that the device neds to be initialised to get the version. As we are still getting zero, force the string for now
  const char *deviceInfoVersion         = "Unknown Version";
  
  // Create the Java Object
  jobject info = env->NewObject(javaClass,
                                constructor,
                                env->NewStringUTF(( deviceInfoNamePtr         != NULL ) ? deviceInfoNamePtr         : "** Internal Error getting Device Name!"),
                                env->NewStringUTF(( deviceInfoManufacturerPtr != NULL ) ? deviceInfoManufacturerPtr : "Unknown Manufacturer"),
                                env->NewStringUTF(( deviceInfoDescriptionPtr  != NULL ) ? deviceInfoDescriptionPtr  : "Unknown Description"),
                                env->NewStringUTF(deviceInfoVersion),
                                env->NewStringUTF(deviceNamePtr),
                                deviceReference,
                                deviceUniqueID,
                                env->NewStringUTF(entityNamePtr),
                                entityReference,
                                entityUniqueID,
                                env->NewStringUTF(endPointNamePtr),
                                endPointReference,
                                endpointUniqueID);

  return info;

}

