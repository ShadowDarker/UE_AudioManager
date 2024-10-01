Unreal Engine 5.3

Example of basic audio manager subsystem with some functions to handle music.

A blueprint subclass of the audio manager can be referenced in **AudioManagerSubsystemSettings** through Project Settings to create an instance of it.

The audio manager makes use of a **MusicData** data asset to collect audio assets and configuration identified by an string ID, and handles the music elements through the available functions using their ID.
