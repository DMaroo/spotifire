# SpotiFire

DBus code to add a progress bar in Spotify's taskbar icon. The progress bar moves as the song progresses.

### Without SpotiFire

<img src="images/without-spotifire.png" width="200"/>

### With SpotiFire

<img src="images/with-spotifire.png" width="200"/>

# Building

## Dependencies

Make sure you have Qt6 installed. You can get this to work with Qt5 as well, but you'll need to tweak the [`CMakeLists.txt`](./CMakeLists.txt) if you want to do that. You also need DBus and Qt bindings for it installed.

You should also have an application file for Spotify (like `spotify.desktop`) in path (`/usr/share/applications/` or `~/.local/share/applications/`).

## Build

```
$ git clone https://github.com/DMaroo/spotifire
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Running

Inside the build directory, run the following command.

```
./spotifire
```

To make SpotiFire persistent, you can either run it at startup, or run it everytime you open Spotify (recommended) by modifying the command in the application file for Spotify.
