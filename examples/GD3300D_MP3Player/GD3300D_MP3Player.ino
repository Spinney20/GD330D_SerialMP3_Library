#include <SerialMP3.h>

// Define RX and TX pins for software serial communication
#define RX_PIN 10  // Connect to TX of MP3 module
#define TX_PIN 11  // Connect to RX of MP3 module

// Create MP3 object
SerialMP3 mp3(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);  // Start Serial Monitor communication
  mp3.showDebug(true); // Enable debugging messages (set to false to disable)
  mp3.init();          // Initialize the MP3 module
  mp3.setVolume(20);   // Set initial volume (0 - 30)

  Serial.println("\n=== Serial MP3 Player (GD3300D) Demo ===");
  Serial.println("Enter a command:");
  Serial.println("p - Play");
  Serial.println("P - Pause");
  Serial.println("s - Stop");
  Serial.println("> - Next Track");
  Serial.println("< - Previous Track");
  Serial.println("v - Query Volume");
  Serial.println("+ - Increase Volume");
  Serial.println("- - Decrease Volume");
  Serial.println("t - Query Total Tracks");
  Serial.println("c - Query Current Track");
  Serial.println("f - Play Specific Track from Folder");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case 'p':
        Serial.println("Playing Track...");
        mp3.play();
        break;

      case 'P':
        Serial.println("Pausing...");
        mp3.pause();
        break;

      case 's':
        Serial.println("Stopping Playback...");
        mp3.stop();
        break;

      case '>':
        Serial.println("Skipping to Next Track...");
        mp3.playNext();
        break;

      case '<':
        Serial.println("Going to Previous Track...");
        mp3.PlayPrevious();
        break;

      case '+':
        Serial.println("Increasing Volume...");
        mp3.volumeUp();
        break;

      case '-':
        Serial.println("Decreasing Volume...");
        mp3.volumeDown();
        break;

      case 'v':
        Serial.println("Querying Current Volume...");
        mp3.queryVolume();
        break;

      case 't':
        Serial.println("Querying Total Tracks...");
        mp3.queryTotalSong();
        break;

      case 'c':
        Serial.println("Querying Current Track...");
        mp3.querySongCurrent();
        break;

      case 'f':
        Serial.println("Enter Folder Number:");
        while (!Serial.available()); // Wait for input
        int folder = Serial.parseInt();

        Serial.println("Enter File Number:");
        while (!Serial.available()); // Wait for input
        int file = Serial.parseInt();

        if (folder > 0 && file > 0) {
          Serial.print("Playing file ");
          Serial.print(file);
          Serial.print(" from folder ");
          Serial.println(folder);
          mp3.playFolderFile(folder, file);
        } else {
          Serial.println("Invalid folder or file number!");
        }
        break;

      default:
        Serial.println("Invalid command. Try again.");
        break;
    }
  }
}
