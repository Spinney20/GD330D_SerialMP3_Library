/*--------------------------------------------------------------------
  SerialMP3.h - Library for Serial MP3 Player board GD3300D/TD5580A chip.
--------------------------------------------------------------------*/

#ifndef SerialMP3_h
#define SerialMP3_h

#include "stdint.h"
#include "Arduino.h"
#include "SoftwareSerial.h"

/*-------------- Control Commands --------------*/
#define CMD_NEXT              0x01 // Play next track
#define CMD_PREVIOUS          0x02 // Play previous track
#define CMD_PLAY_INDEX        0x03 // Play specific track (1 -> 255)
#define CMD_VOLUME_UP         0x04 // Increase volume
#define CMD_VOLUME_DOWN       0x05 // Decrease volume
#define CMD_SET_VOLUME        0x06 // Set volume level (0 -> 30)
#define CMD_SINGLE_CYCLE_PLAY 0x08 // Play single file in loop
#define CMD_SELECT_DEVICE     0x09 // Select storage device (microSD: 2)
#define CMD_SLEEP_MODE        0x0A // Enter sleep mode
#define CMD_WAKE_UP           0x0B // Wake up from sleep mode
#define CMD_RESET             0x0C // Reset the MP3 module
#define CMD_PLAY              0x0D // Start playback
#define CMD_PAUSE             0x0E // Pause playback
#define CMD_PLAY_FOLDER_FILE  0x0F // Play specific file from folder
#define CMD_STOP              0x16 // Stop playback
#define CMD_CYCLE_FOLDER      0x17 // Loop play entire folder
#define CMD_SHUFFLE_PLAY      0x18 // Shuffle play all tracks
#define CMD_SET_SINGLE_CYCLE  0x19 // Enable/disable single cycle play
#define CMD_PLAY_VOLUME       0x22 // Set volume and play track

/*-------------- Query Commands --------------*/
#define CMD_QUERY_STATUS            0x42 // Query playback status
#define CMD_QUERY_VOLUME            0x43 // Query current volume
#define CMD_QUERY_TOTAL_SONG        0x48 // Query total number of tracks
#define CMD_QUERY_SONG              0x4C // Query currently playing track
#define CMD_QUERY_TOTAL_SONG_FOLDER 0x4E // Query total number of tracks in folder
#define CMD_QUERY_TOTAL_FOLDER      0x4F // Query total number of folders

/*---------------- SerialMP3 Class ----------------*/
class SerialMP3 {
public:
    SerialMP3(uint8_t rx, uint8_t tx); // Constructor with RX and TX pins
    
    void showDebug(bool status); // Enable/disable debug output

    void init(); // Initialize the MP3 module
    uint8_t available(); // Check if data is available
    char read(); // Read incoming serial data

    void sendCommand(uint8_t command); // Send a command without parameters
    void sendCommand(uint8_t command, uint8_t data2); // Send command with one parameter
    void sendCommand(uint8_t command, uint8_t data1, uint8_t data2); // Send command with two parameters
    
    // Playback control
    void play(); // Play the current track
    void play(uint8_t trackNumber); // Play a specific track
    void play(uint8_t trackNumber, uint8_t volume); // Play track with specified volume

    void playNext(); // Play the next track
    void playPrevious(); // Play the previous track
    void playFolder(uint8_t folderNumber); // Play all tracks in the specified folder
    void playFolderFile(uint8_t folderNumber, uint8_t fileNumber); // Play a specific file from a folder

    // Volume control
    void volumeUp(); // Increase volume
    void volumeDown(); // Decrease volume
    void setVolume(uint8_t volume); // Set volume level (0 - 30)

    // Playback modes
    void playSingleCycle(uint8_t trackNumber); // Loop a single track
    void playSingleCycle(uint8_t folderNumber, uint8_t fileNumber); // Loop a single file in a folder
    
    void pause(); // Pause playback
    void stop(); // Stop playback

    void sleep(); // Put MP3 module into sleep mode
    void wakeup(); // Wake up from sleep mode
    void reset(); // Reset the MP3 module

    // Query functions
    void queryStatus(); // Get playback status
    void queryVolume(); // Get current volume level
    void queryTotalSong(); // Get total number of songs
    void querySongCurrent(); // Get currently playing song
    void queryTotalSongInFolder(); // Get total songs in the current folder
    void queryTotalFolder(); // Get total number of folders

    String decodeMP3Answer(); // Decode and return MP3 module response

private:
    SoftwareSerial *serial_mp3; // Software Serial instance for communication
    String answerString(); // Get response string from MP3 module
    String byteToStringHex(uint8_t byte); // Convert byte to hex string
    bool show_debug; // Debug flag
    uint8_t answer_buff[10] = {0}; // Buffer for response data
};

#endif
