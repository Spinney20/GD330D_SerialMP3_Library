# GD3300D Serial MP3 Library

This is an **Arduino library** for controlling the **GD3300D Serial MP3 Player Module** via UART communication. This library allows playing, pausing, stopping, skipping tracks, and adjusting volume through simple commands.

## Features
- Play, pause, and stop MP3 tracks
- Play a specific file or folder
- Increase/decrease volume
- Query current track, volume, and status
- Supports loop playback and shuffle play

---

## Installation

### Manual Installation
1. **Download** the library ZIP from the repository.
2. Open **Arduino IDE**.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**.
4. Select the downloaded **ZIP file** and install it.
5. Restart **Arduino IDE** if necessary.

---

## Wiring Instructions
The MP3 module communicates via UART (SoftwareSerial) with Arduino.

| MP3 Module | Arduino | Description |
|------------|---------|-------------|
| **VCC**    | 5V      | Power (5V) |
| **GND**    | GND     | Ground |
| **RX**     | 10      | Serial TX from Arduino (SoftwareSerial) |
| **TX**     | 11      | Serial RX from Arduino (SoftwareSerial) |
| **SPK**   | Speaker | Connect to speaker |

---

## Example Usage
After installation, open the example sketch in Arduino IDE:

1. **Go to** `File` -> `Examples` -> `GD3300D_SerialMP3_Library` -> `GD3300D_MP3Player`.
2. **Upload the code** to the Arduino board.
3. Open **Serial Monitor** (`9600 baud`) to interact with the MP3 module.

### Example Code
This example demonstrates how to play, pause, skip, and adjust the volume.

```cpp
#include <SerialMP3.h>

#define RX_PIN 10
#define TX_PIN 11

SerialMP3 mp3(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  mp3.init();
  mp3.setVolume(20); // Set volume to 20
  mp3.play(1); // Play track 1
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '>') mp3.playNext();
    if (command == '<') mp3.PlayPrevious();
    if (command == 'p') mp3.pause();
    if (command == '+') mp3.volumeUp();
    if (command == '-') mp3.volumeDown();
  }
}
```

### How It Works
- The **MP3 module** communicates with Arduino using **SoftwareSerial (RX/TX)**.
- The **setVolume(20)** sets the volume level between 0-30.
- The **play(1)** plays the first MP3 file (`001.mp3`) from the microSD card.
- The **Serial Monitor** allows manual control with commands:
  - `>` = Next Track
  - `<` = Previous Track
  - `p` = Pause
  - `+` = Volume Up
  - `-` = Volume Down

---

## File Naming Convention
Ensure the **microSD card** is formatted as **FAT32**, and MP3 files are named as follows:
```
001.mp3
002.mp3
003.mp3
...
```
If using folders:
```
/01/001.mp3
/01/002.mp3
/02/001.mp3
```

---

## Advanced Functions
The library supports additional features such as querying the current track, looping, and shuffle mode:

```cpp
mp3.queryVolume();  // Get current volume
mp3.queryStatus();  // Get playback status
mp3.playFolderFile(2, 1); // Play track 1 in folder 2
mp3.setVolume(10); // Set volume to 10
mp3.stop(); // Stop playback
```

---

## Troubleshooting
### No Sound Output?
- Ensure **MP3 files are in the correct format (128kbps CBR, 44.1kHz MP3)**.
- Make sure the **microSD card is FAT32 formatted**.
- Check that **RX/TX pins are correctly connected**.
- Power the MP3 module with **5V, not 3.3V**.

### Serial Monitor Not Responding?
- Make sure **baud rate is set to 9600**.
- Double-check the **wiring connections**.
- Try restarting **Arduino IDE** and **re-uploading** the code.

---

## License
This project is open-source under the **MIT License**.

## Contributions
Feel free to contribute to this project by submitting **issues** or **pull requests**.

**Author:** Spinney20

[GitHub Repository](https://github.com/Spinney20/GD330D_SerialMP3_Library)
