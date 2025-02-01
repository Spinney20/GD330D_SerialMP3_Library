/*--------------------------------------------------------------
  SerialMP3.h - Custom Library for Serial MP3 Player (GD3300D)
  This library is designed to facilitate communication between
  Arduino and the GD3300D Serial MP3 Player module.
  INSPIRED BY THE LIBRARY FOR THE ORIGINAL V.1.0.0. MP3 PLAYER
  --------------------------------------------------------------*/

#include "stdint.h"
#include "Arduino.h"
#include "SerialMP3.h"

SerialMP3::SerialMP3(uint8_t rx, uint8_t tx) {
    serial_mp3 = new SoftwareSerial(rx, tx);
    debug_mode = false;  // Debugging disabled by default
}

// Enable or disable debug mode
void SerialMP3::enableDebug(bool status) {
    debug_mode = status;
}

// Initialize MP3 module
void SerialMP3::init() {
    serial_mp3->begin(9600); // Start communication at 9600 baud rate
    delay(500);  // Allow time for initialization
    reset();  // Reset the module
    delay(500);
    sendCommand(CMD_SELECT_DEVICE, 2); // Select microSD card as default storage
    delay(500);
    
    if (debug_mode) {
        Serial.println("MP3 Player Initialized Successfully!");
    }
}

uint8_t SerialMP3::available() {
    return serial_mp3->available();
}

char SerialMP3::read() {
    return serial_mp3->read();
}

// Basic playback commands
void SerialMP3::play() {
    sendCommand(CMD_PLAY);
}

void SerialMP3::play(uint8_t index) {
    sendCommand(CMD_PLAY_INDEX, index);
}

void SerialMP3::play(uint8_t index, uint8_t volume) {
    sendCommand(CMD_PLAY_VOLUME, volume, index);
}

void SerialMP3::playNext() {
    sendCommand(CMD_NEXT);
}

void SerialMP3::playPrevious() {
    sendCommand(CMD_PREVIOUS);
}

void SerialMP3::playFolder(uint8_t folder) {
    sendCommand(CMD_PLAY_FOLDER_FILE, folder);
}

void SerialMP3::playFolderFile(uint8_t folder, uint8_t file) {
    sendCommand(CMD_PLAY_FOLDER_FILE, folder, file);
}

// Volume control
void SerialMP3::increaseVolume() {
    sendCommand(CMD_VOLUME_UP);
}

void SerialMP3::decreaseVolume() {
    sendCommand(CMD_VOLUME_DOWN);
}

void SerialMP3::setVolume(uint8_t volume) {
    sendCommand(CMD_SET_VOLUME, volume);
}

// Playback modes
void SerialMP3::playSingleCycle(uint8_t index) {
    sendCommand(CMD_SINGLE_CYCLE_PLAY, index);
}

void SerialMP3::playSingleCycle(uint8_t folder, uint8_t index) {
    sendCommand(CMD_SINGLE_CYCLE_PLAY, folder, index);
}

void SerialMP3::pause() {
    sendCommand(CMD_PAUSE);
}

void SerialMP3::stop() {
    sendCommand(CMD_STOP);
}

void SerialMP3::sleep() {
    sendCommand(CMD_SLEEP_MODE);
}

void SerialMP3::wakeUp() {
    sendCommand(CMD_WAKE_UP);
}

void SerialMP3::reset() {
    sendCommand(CMD_RESET);
}

// Query commands
void SerialMP3::queryStatus() {
    sendCommand(CMD_QUERY_STATUS);
}
void SerialMP3::queryVolume() {
    sendCommand(CMD_QUERY_VOLUME);
}
void SerialMP3::queryTotalTracks() {
    sendCommand(CMD_QUERY_TOTAL_TRACKS);
}
void SerialMP3::queryCurrentTrack() {
    sendCommand(CMD_QUERY_CURRENT_TRACK);
}
void SerialMP3::queryTracksInFolder() {
    sendCommand(CMD_QUERY_FOLDER_TRACKS);
}
void SerialMP3::queryTotalFolders() {
    sendCommand(CMD_QUERY_TOTAL_FOLDERS);
}

// Send a command without additional parameters
void SerialMP3::sendCommand(uint8_t command) {
    sendCommand(command, 0, 0);
}

// Send a command with one data parameter
void SerialMP3::sendCommand(uint8_t command, uint8_t param) {
    sendCommand(command, 0, param);
}

// Send a command with two data parameters
void SerialMP3::sendCommand(uint8_t command, uint8_t param1, uint8_t param2) {
    uint8_t commandBuffer[8] = {0};
    String debugMessage = "";

    delay(20);
    commandBuffer[0] = 0x7E;    // Start byte
    commandBuffer[1] = 0xFF;    // Version byte
    commandBuffer[2] = 0x06;    // Command length (excluding start/end bytes)
    commandBuffer[3] = command; // Command byte
    commandBuffer[4] = 0x01;    // Feedback: 0x00 = No feedback, 0x01 = Feedback
    commandBuffer[5] = param1;  // Data high byte
    commandBuffer[6] = param2;  // Data low byte
    commandBuffer[7] = 0xEF;    // End byte

    for (int i = 0; i < 8; i++) {
        serial_mp3->write(commandBuffer[i]);
        debugMessage += formatHex(commandBuffer[i]);
    }

    if (debug_mode) {
        Serial.print("Command Sent: ");
        Serial.println(debugMessage);
    }
}

// Converts a byte into a formatted hex string
String SerialMP3::formatHex(uint8_t value) {
    String hexString = "0x";
    if (value < 16) hexString += "0";
    hexString += String(value, HEX);
    hexString += " ";
    return hexString;
}

// Reads and formats the MP3 player's response
String SerialMP3::readResponse() {
    uint8_t responseBuffer[10] = {0};
    String responseMessage = "";

    if (serial_mp3->available()) {
        for (uint8_t i = 0; i < 10 && serial_mp3->available(); i++) {
            responseBuffer[i] = serial_mp3->read();
            responseMessage += formatHex(responseBuffer[i]);
        }
    }
    return responseMessage;
}
