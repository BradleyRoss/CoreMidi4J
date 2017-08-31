/*
 * Title:        CoreMIDI4J
 * Description:  Core MIDI Device Provider for Java on OS X
 * Copyright:    Copyright (c) 2015-2016
 * Company:      x.factory Librarians
 *
 * @author Derek Cook
 * 
 * CoreMIDI4J is an open source Service Provider Interface for supporting external MIDI devices on MAC OS X
 * 
 * CREDITS - This library uses principles established by OSXMIDI4J, but converted so it operates at the JNI level with no additional libraries required
 * 
 */

package uk.co.xfactorylibrarians.coremidi4j;

import java.util.ArrayList;
import java.util.List;

/**
 * CoreMidiClient class
 *
 */

public class CoreMidiClient {

  private final int midiClientReference;

  private final List<CoreMidiNotification> notificationListeners = new ArrayList<CoreMidiNotification>();

  /**
   * Constructor for class
   * 
   * @param name 	The name of the client		
   * 
   * @throws 			CoreMidiException if the client cannot be initialized
   * 
   */

  public CoreMidiClient(String name) throws CoreMidiException {

    midiClientReference = this.createClient(name);

  }

  /**
   * Creates a new CoreMidiInputPort
   * 
   * @param name	The name of the port
   * 
   * @return			A new CoreMidiInputPort
   * 
   * @throws 			CoreMidiException if the port cannot be created
   * 
   */

  public CoreMidiInputPort inputPortCreate(final String name) throws CoreMidiException {

    return new CoreMidiInputPort(midiClientReference,name);

  }

  /**
   * Creates a new CoreMidiOutputPort
   * 
   * @param name	The name of the port
   * 
   * @return			A new CoreMidiOutputPort
   * 
   * @throws 			CoreMidiException if the port cannot be created
   * 
   */

  public CoreMidiOutputPort outputPortCreate(final String name) throws CoreMidiException {

    return new CoreMidiOutputPort(midiClientReference,name);

  }

  /**
   * The message callback for receiving notifications about changes in the MIDI environment from the JNI code.
   * <p>A reference to this method is created by the C++ method
   *    Java_uk_co_xfactorylibrarians_coremidi4j_CoreMidiClient_createClient
   *    which in turn is called by {@link #createClient(String) }.</p>
   *    
   * @throws CoreMidiException if a problem occurs passing along the notification
   * 
   */

  public void notifyCallback() throws CoreMidiException  {

    // Debug code - uncomment to see this function being called
    //System.out.println("** CoreMidiClient - MIDI Environment Changed");

    synchronized(this) {

      // Iterate through the listeners (if any) and call them to advise that the environment has changed    	
      for ( CoreMidiNotification listener : notificationListeners ) {

        listener.midiSystemUpdated();

      }

    }

  }

  /**
   * Adds a notification listener to the listener list maintained by this class
   * 
   * @param listener	The CoreMidiNotification listener to add
   * 
   */

  public void addNotificationListener(CoreMidiNotification listener) {

    // Need to ensure that any CoreMidiDeviceProvider objects are at the head of the notification list, so that the device map is updated before other listeners are called
    if ( listener instanceof CoreMidiDeviceProvider ) {

      notificationListeners.add(0,listener);

    } else {

      notificationListeners.add(listener);

    }

  }

  /**
   * Removes a notification listener from the listener list maintained by this class
   * 
   * @param listener	The CoreMidiNotification listener to remove
   * 
   */

  public void removeNotificationListener(CoreMidiNotification listener) {

    notificationListeners.remove(listener);

  }

  //////////////////////////////
  ///// JNI Interfaces
  //////////////////////////////

  /*
   * Static initializer for loading the native library
   *
   */

  static {

    try {

      Loader.load();

    } catch (Throwable t) {

      System.err.println("Unable to load native library, CoreMIDI4J will stay inactive: " + t);

    }

  }

  /**
   * Creates the MIDI Client
   * 
   * @param clientName 					The name of the client
   * 
   * @return										A reference to the MIDI client
   * 
   * @throws CoreMidiException	if the client cannot be created
   *
   */

  private native int createClient(String clientName) throws CoreMidiException;

  /**
   * Disposes of a CoreMIDI Client
   * 
   * @param clientReference		The reference of the client to dispose of
   * 
   * @throws 									CoreMidiException if there is a problem disposing of the client
   * 
   */

  private native void disposeClient(int clientReference) throws CoreMidiException;

}
