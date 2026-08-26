# PacMan vs Ghost — Networked Two-Player Multiplayer Game

A real-time, two-player networked game built in **C++ with SFML**, where one player controls Pac-Man and the other controls a Ghost, connected over TCP through a dedicated relay server. Built for the CMP303 Networking module at Abertay University.

Rather than a single-player Pac-Man clone, this project's focus is the **network architecture**: a authoritative server that pairs two clients, relays their positions to each other, and broadcasts shared world state (collectible balls), while each client applies client-side prediction and interpolation to keep the other player's movement smooth despite network latency.

## Architecture

The project is split into three separately-buildable components, each its own Visual Studio project:

| Component | Role |
|---|---|
| **`PacManvsGhost/`** | The Pac-Man client — yellow circle, arrow-key movement, sends its own position, receives and predicts the Ghost's position |
| **`Ghost/Ghosts/`** | The Ghost client — mirror-image of the Pac-Man client (red rectangle), sends its own position, receives and predicts Pac-Man's position |
| **`Server/Server/`** | A standalone relay server — accepts exactly two TCP connections, identifies each client by an ID string ("PacMan"/"Ghost") sent on connect, and relays position/ball data between them |

Both clients share the same framework code (window/game loop, input, audio, tilemap, collision) but each has its own tailored `Networking` class matching which side of the match it represents.

## How a match works

1. The server starts, binds a `TcpListener` to port `2222`, and waits for two clients to connect.
2. Each client, on launch, prompts the player for the server's IP address and port, connects, then immediately sends an identifying string ("PacMan" or "Ghost") so the server knows which player is which.
3. Once both clients are connected, the server sends a one-off `PT_START` packet to synchronise each client's local game timer, then generates and broadcasts 5 randomly-positioned collectible balls (`PT_BALLS`).
4. Every frame, each client sends its own position (`PT_POSITIONS`) to the server; the server relays it on to the *other* client.
5. Sockets are set to **non-blocking** on the server to keep both connections serviced without one stalling the other.

## Client-side prediction & interpolation

Because position updates only arrive at a fixed interval rather than every frame, each client smooths the other player's movement instead of visibly snapping between updates:

- If it's the first packet received, or the other player hasn't moved, the client **lerps** directly toward the received position.
- Otherwise, it **predicts** the other player's next position using their last-known velocity and a short prediction interval, then lerps toward that predicted point — a lightweight dead-reckoning approach to hide network jitter.

## Features

- **TCP client/server networking** via SFML's `sf::TcpSocket` / `sf::TcpListener`, with a small binary packet protocol (`sf::Int8` packet-type header + payload) to keep messages compact
- **Client-side prediction and linear interpolation** for smooth remote-player movement between network updates
- **Server-authoritative ball spawning** — collectible positions are generated once on the server and broadcast identically to both clients, so both see the same world state
- **Manual connection flow** — the player is prompted for IP/port at launch and the input is validated before connecting
- **Shared timer synchronisation** — the server signals both clients to start their local match timers at the same moment
- **Simple custom game framework** (`Framework/`) — game loop, input handling, tilemaps, animation, audio, and AABB collision, reused across both client builds

## Project structure

```
CMP303_Coursework_Final/
├── PacManvsGhost/PacManvsGhost/   # Pac-Man client
│   ├── Main.cpp                   # Window, game loop, event handling
│   ├── Level.cpp/.h               # Connection flow, per-frame update/render
│   ├── Networking.cpp/.h          # Pac-Man side send/receive, prediction
│   ├── PacMan.cpp/.h              # Pac-Man movement and rendering
│   ├── Ghosts.cpp/.h              # Remote ghost representation + predicted state
│   ├── Balls.cpp/.h               # Collectible ball spawning/rendering
│   └── Framework/                 # Shared game framework (input, tilemap, audio, collision...)
├── Ghost/Ghosts/Ghosts/           # Ghost client (mirrors PacManvsGhost/)
├── Server/Server/Server/
│   ├── Server.cpp                 # Two-client relay server, packet routing
│   └── Balls.cpp/.h               # Server-side ball position generation
└── SFML/SFML-2.6.0/               # SFML library used by all three projects
```

## Building & running

This is a Visual Studio / SFML project with three separate builds.

1. Build `Server/Server` first and run it — it will print its local IP address and listen on port `2222`.
2. Build and run `PacManvsGhost` as one player and `Ghost/Ghosts` as the other (on the same machine or different machines on the same network).
3. Each client will prompt for the server's IP address and port (`2222`) — enter the IP the server printed on startup.
4. Once both clients connect, the match timer starts and balls spawn for both players.

## Background

Built as coursework for CMP303 (Multiplayer & Network Programming) at Abertay University. The goal was to design and implement a real client/server multiplayer architecture from scratch — connection handshaking, a custom packet protocol, server-relayed state, and client-side prediction/interpolation to compensate for network latency — rather than relying on a third-party networking framework.
