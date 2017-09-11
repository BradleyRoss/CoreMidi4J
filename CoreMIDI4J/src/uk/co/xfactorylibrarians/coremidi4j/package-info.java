/**
 * A set of classes for enabling the javax.sound.midi package
 * to interact with CoreData on Mac OS X.
 * <h3>CoreMidiClient</h3>
 * <ul>
 * <li>String createClient(String)</li>
 * <li>void disposeClient(int)</li>
 * </ul>
 * <h3>CoreMidiDestination</h3>
 * <ul>
 * <li>int createInputPort(int, java.lang.String)</li>
 * <li>long midiPortConnectSource(int,CoreMidiSource)</li>
 * <li>void midiPortDisconnectSource(int, CoreMidiSource)</li>
 * </ul>
 * <h3>CoreMidiDeviceProvider</h3>
 * <ul>
 * <li>CoreMidiDeviceInfo getMidiDeviceInfo(int)</li>
 * </ul>
 * <h3>CoreMidiInputPort</h3>
 * <ul>
 * <li>int createInputPort(int, java.lang.String)</li>
 * <li>jobject midiPortConnectSource(int, CoreMidiSource)</li>
 * <li>void midiPortDisconnectSource9int, long, CoreMidiSource)</li>
 * </ul>
 * <h3>CoreMidiOutputPort</h3>
 * <ul>
 * <li>int createOutputPort(int, java.lang.String)</li>
 * <li>void sendMidiMessage(int, int, javax.sound.midi.MidiMessage, long)</li>
 * </ul>
 * <h3>CoreMidiSource</h3>
 * <ul>
 * <li>long getMicrosecondTime();</li>
 * </ul>
 * 
 * 
 */
package uk.co.xfactorylibrarians.coremidi4j;