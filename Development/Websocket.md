## 🔹 Topic:  WebSocket

- [ ] **Q1. What is WebSocket? And When to Use WebSocket?**  
<details>
  <summary>Answer</summary>
  WebSocket is a communication protocol that provides a full-duplex (two-way) connection between the client (like a browser) and the server over a single, persistent TCP connection.

- Unlike HTTP, which is request-response based (you send a request, you get a response),
- WebSocket allows both client and server to send data at any time, without waiting for a request.
- You should use WebSocket when your app needs real-time, continuous communication between client and server. 
</details>  

---
 

- [ ] **Q2.What is the difference between WebSocket and HTTP? Compare both protocols and explain their advantages and disadvantages. ?**  
<details>
  <summary>Answer</summary>

  ---

## ✅ 1. Basic Definition

| Feature       | HTTP                                    | WebSocket                                             |
|---------------|-----------------------------------------|--------------------------------------------------------|
| Type          | Request-Response Protocol               | Full-Duplex Communication Protocol                    |
| Connection    | Short-lived (new connection per request)| Persistent (single connection stays open)            |
| Direction     | One-way (client → server)               | Two-way (client ↔ server)                             |

---

## ✅ 2. Communication Flow

| Aspect              | HTTP                                             | WebSocket                                          |
|---------------------|--------------------------------------------------|---------------------------------------------------|
| Who starts?         | Always the **client** initiates a request        | Either **client or server** can send messages     |
| When is data sent?  | Only when client sends request                   | Any time after connection is established          |
| Handshake?          | Simple HTTP request                              | Starts with HTTP handshake → upgrades to WebSocket|

---

## ✅ 3. Use Cases

| HTTP                            | WebSocket                                 |
|----------------------------------|-------------------------------------------|
| Loading webpages, REST APIs     | Chat apps, multiplayer games, live feeds  |
| CRUD operations (POST/GET/etc.) | Real-time notifications, tracking systems |

---

## ✅ 4. Advantages

### 🔵 HTTP Advantages:
- Simple, well-supported everywhere 🌍  
- Great for **stateless** transactions  
- Easy to cache and debug  
- Works with proxies, firewalls, and CDNs

### 🔵 WebSocket Advantages:
- **Real-time** bi-directional communication ⚡  
- Fewer headers, less overhead after connection  
- More efficient for **frequent updates**  
- Ideal for **event-driven systems**

---

## ✅ 5. Disadvantages

### 🔴 HTTP Disadvantages:
- **No real-time** communication  
- Repeated **request overhead** (connection setup each time)  
- Not suitable for live updates (requires polling)

### 🔴 WebSocket Disadvantages:
- **Not cacheable** by proxies/CDNs  
- May be **blocked** by strict firewalls  
- Needs **custom scaling and reconnect logic**

---
</details>  
 
---
- [ ] **Q3  Which port does WebSocket use ?**

<details>
<summary>Answer</summary>

- Default port is 80 (for ws://)

- 443 for secure WebSocket (wss://)
 
</details>

---

- [ ] **Q 4. What is the WebSocket handshake ?**

<details>
<summary>Answer</summary>
It’s the process where a client requests to upgrade an HTTP connection to WebSocket, and the server accepts it. After that, both can send messages freely.

 
</details>

---
- [ ] **Q5 How do you create websocket in mern using socket.io and socket.io client , And how communication is done ?**

<details>
<summary>Answer</summary>

### Server.js

```js
import express from "express";
import http from "http";
import { Server } from "socket.io";
import cors from "cors";

const app = express();
app.use(cors());

const server = http.createServer(app);
const io = new Server(server, {
  cors: {
    origin: "http://localhost:3000",
    methods: ["GET", "POST"],
  },
});

// 🔗 Socket connection
io.on("connection", (socket) => {
  console.log("🟢 New client connected:", socket.id);

  socket.on("send_message", (data) => {
    console.log("📨 Message from client:", data);

    // Broadcast to all clients
    io.emit("receive_message", data);
  });

  socket.on("disconnect", () => {
    console.log("🔴 Client disconnected:", socket.id);
  });
});

server.listen(5000, () => {
  console.log("✅ Server running on http://localhost:5000");
});

```

### Client side
```js
import React, { useEffect, useState } from "react";
import { io } from "socket.io-client";

// 📡 Connect to server
const socket = io("http://localhost:5000");

function App() {
  const [message, setMessage] = useState("");
  const [messages, setMessages] = useState([]);

  useEffect(() => {
    // Listen for incoming messages
    socket.on("receive_message", (data) => {
      setMessages((prev) => [...prev, data]);
    });

    // Cleanup
    return () => {
      socket.disconnect();
    };
  }, []);

  const sendMessage = () => {
    socket.emit("send_message", message);
    setMessage("");
  };

  return (
    <div>
      <h2>💬 WebSocket Chat (Socket.IO)</h2>
      <input
        value={message}
        onChange={(e) => setMessage(e.target.value)}
        placeholder="Type message..."
      />
      <button onClick={sendMessage}>Send</button>

      <div>
        {messages.map((msg, i) => (
          <p key={i}>🗨️ {msg}</p>
        ))}
      </div>
    </div>
  );
}

export default App;
```
</details>

---

- [ ] **Q6 Summary of Frontend Socket.IO Usage ?**

<details>
<summary>Answer</summary>

| Task               | Code Example                                  |
| ------------------ | --------------------------------------------- |
| Connect            | `const socket = io("http://localhost:5000");` |
| Emit to server     | `socket.emit("event_name", data);`            |
| Listen from server | `socket.on("event_name", callback);`          |


 
</details>

---

- [ ] **Q7 How to we listen on server side ?Give example for few case  .**

<details>
<summary>Answer</summary>

- Note that we always listen inside the io.on blcok

``` js
// Import necessary modules
import express from "express";
import http from "http";
import { Server } from "socket.io";
import cors from "cors";

// Initialize express app
const app = express();

// Enable CORS for frontend (React usually runs on 3000)
app.use(cors());

// Create HTTP server from express app
const server = http.createServer(app);

// Create a new instance of Socket.IO server
const io = new Server(server, {
  cors: {
    origin: "http://localhost:3000", // Replace with your frontend origin
    methods: ["GET", "POST"],
  },
});

// Map to track userId → socket.id
const onlineUsers = new Map();

/**
 * Global connection listener: triggered when a client connects
 */
io.on("connection", (socket) => {
  console.log("🟢 A user connected:", socket.id);

  /**
   * Client sends 'register-user' event with their userId
   * We store the mapping: userId → socket.id
   */
  socket.on("register-user", (userId) => {
    onlineUsers.set(userId, socket.id);
    console.log(`✅ Registered user ${userId} with socket ${socket.id}`);
  });

  /**
   * Listen for 'send_message' event
   * Broadcast it to all connected clients
   */
  socket.on("send_message", (data) => {
    console.log("📨 Message from client:", data);
    io.emit("receive_message", data);
  });

  /**
   * Private messaging: send message to specific user by userId
   */
  socket.on("send-to-user", ({ toUserId, message }) => {
    const targetSocketId = onlineUsers.get(toUserId);
    if (targetSocketId) {
      io.to(targetSocketId).emit("private-message", {
        from: socket.id,
        message,
      });
      console.log(`📤 Sent private message to ${toUserId}`);
    } else {
      console.log(`❌ User ${toUserId} not online`);
    }
  });

  /**
   * Handle client disconnection
   */
  socket.on("disconnect", () => {
    console.log("🔴 Client disconnected:", socket.id);

    // Remove user from the map
    for (let [userId, sockId] of onlineUsers.entries()) {
      if (sockId === socket.id) {
        onlineUsers.delete(userId);
        console.log(`🗑️ Removed user ${userId} from map`);
        break;
      }
    }
  });

  /**
   * Optional: log all events from this socket
   */
  socket.onAny((event, ...args) => {
    console.log(`📡 Event received → ${event}:`, args);
  });

  /**
   * Optional: handle socket errors
   */
  socket.on("error", (err) => {
    console.error("❗ Socket error:", err);
  });
});

// Start the server
server.listen(5000, () => {
  console.log("🚀 Server running at http://localhost:5000");
});
```
### 🧪 Test Functionality
You can test this with a React frontend using:

- socket.emit("register-user", userId)

- socket.emit("send_message", "Hello world")

- socket.emit("send-to-user", { toUserId: "xyz", message: "Hi!" })


 
</details>

--- 
- [ ] **Q8 Give ex of emit from server  in various casess  ?**

<details>
<summary>Answer</summary>

| Case                                     | Function Used                                | Description                                               |
|------------------------------------------|-----------------------------------------------|-----------------------------------------------------------|
| To same client only                      | `socket.emit()`                               | Sends only to the connected client                        |
| To all clients                           | `io.emit()`                                   | Sends to everyone (including sender)                     |
| To all except sender                     | `socket.broadcast.emit()`                     | Sends to everyone **except** the sender                  |
| To specific user (private)               | `io.to(socketId).emit()`                      | Sends to a specific user using their socket ID           |
| To room                                  | `io.to("room").emit()`                        | Sends to all users in a given room                       |
| To room except sender                    | `socket.to("room").emit()`                    | Sends to everyone in room **except** sender              |
| Every 1 hour to all clients              | `setInterval(() => io.emit(...))`            | Auto-broadcast to all clients on a timer                 |
| Every 1 hour to specific user by userId  | `setInterval(() => io.to(socketId).emit(...))`| Auto-send to a specific user using mapped socketId       |
| Every 1 hour to each room                | `setInterval(() => io.to(room).emit(...))`    | Loops over rooms and sends message to each one           |
| Every 1 hour to all online users         | `setInterval(() => io.to(socketId).emit(...))`| Loops over all mapped users and sends individually       |
| Server emits without any client trigger  | `io.emit()` inside `setInterval`              | Server sends by itself (like heartbeat/notifications)    |

---
```js
import express from "express";
import http from "http";
import { Server } from "socket.io";
import cors from "cors";

const app = express();
app.use(cors());

// Create HTTP + WebSocket server
const server = http.createServer(app);

const io = new Server(server, {
  cors: {
    origin: "http://localhost:3000", // Frontend origin
    methods: ["GET", "POST"],
  },
});

// Mappings
const onlineUsers = new Map();   // userId → socket.id
const userRooms = new Map();     // roomName → Set of socket ids

// 🔌 Handle client connections
io.on("connection", (socket) => {
  console.log("🟢 Connected:", socket.id);

  // 1. Emit to self
  socket.emit("welcome", "👋 Welcome to the server!");

  // 2. Register userId mapping
  socket.on("register-user", (userId) => {
    onlineUsers.set(userId, socket.id);
    console.log(`✅ Registered: ${userId} → ${socket.id}`);
  });

  // 3. Broadcast to all clients
  socket.on("broadcast-message", (msg) => {
    io.emit("broadcast", `📢 ${msg}`);
  });

  // 4. Emit to all except sender
  socket.on("user-typing", () => {
    socket.broadcast.emit("show-typing", `${socket.id} is typing...`);
  });

  // 5. Private message to specific user
  socket.on("send-to-user", ({ toUserId, message }) => {
    const targetSocketId = onlineUsers.get(toUserId);
    if (targetSocketId) {
      io.to(targetSocketId).emit("private-message", {
        from: socket.id,
        message,
      });
    }
  });

  // 6. Join a room and track
  socket.on("join-room", (room) => {
    socket.join(room);
    if (!userRooms.has(room)) {
      userRooms.set(room, new Set());
    }
    userRooms.get(room).add(socket.id);
    console.log(`🏠 ${socket.id} joined ${room}`);
  });

  // 7. Send message to a room
  socket.on("room-message", ({ room, text }) => {
    io.to(room).emit("room-message", `💬 [${room}] ${text}`);
  });

  // 8. Send message to room except sender
  socket.on("notify-room", (room) => {
    socket.to(room).emit("room-notify", `🔔 Someone is active in ${room}`);
  });

  // 9. Disconnect cleanup
  socket.on("disconnect", () => {
    console.log("🔴 Disconnected:", socket.id);

    // Remove from user map
    for (const [userId, sockId] of onlineUsers.entries()) {
      if (sockId === socket.id) {
        onlineUsers.delete(userId);
        break;
      }
    }

    // Remove from room sets
    for (const [room, socketSet] of userRooms.entries()) {
      socketSet.delete(socket.id);
      if (socketSet.size === 0) {
        userRooms.delete(room);
      }
    }
  });
});

// 10. Server emits to all clients every 1 hour
setInterval(() => {
  io.emit("hi-all-clients", "⏰ Hi all clients! (every 1 hour)");
  console.log("📤 Broadcasted hourly message to all clients");
}, 60 * 60 * 1000);

// 11. Server emits to a specific user every 1 hour
const TARGET_USER_ID = "user123";
setInterval(() => {
  const socketId = onlineUsers.get(TARGET_USER_ID);
  if (socketId) {
    io.to(socketId).emit("hi-user", `👋 Hi ${TARGET_USER_ID}, from server (1hr)`);
    console.log(`📤 Sent hourly hi to ${TARGET_USER_ID}`);
  }
}, 60 * 60 * 1000);

// 12. Server emits to each room every 1 hour
setInterval(() => {
  for (const room of userRooms.keys()) {
    io.to(room).emit("hi-room", `🏠 Hello room ${room}, from server (1hr)`);
    console.log(`📤 Sent hi to room: ${room}`);
  }
}, 60 * 60 * 1000);

// 13. Server emits to all online users individually every 1 hour
setInterval(() => {
  for (const [userId, socketId] of onlineUsers.entries()) {
    io.to(socketId).emit("hi-online-user", `🌐 Hello ${userId}, from server!`);
  }
  console.log("📤 Sent hi to each online user individually");
}, 60 * 60 * 1000);

// 14. Server emits without any client interaction (every 10s for demo) to all connected client
setInterval(() => {
  io.emit("server-tick", "⏲️ Server ping at " + new Date().toLocaleTimeString());
}, 10000); // every 10 seconds

// 🚀 Start the server
server.listen(5000, () => {
  console.log("🚀 Server running at http://localhost:5000");
});
```
 
</details>

---
- [ ] **Q9 . Can WebSocket fall back to HTTP ?**

<details>
<summary>Answer</summary>

No. If WebSocket fails, it won’t automatically fall back. But libraries like Socket.IO can fallback to HTTP long-polling.

 
</details>

---
- [ ] **Q10 What is a WebSocket frame  ?**

<details>
<summary>Answer</summary>
WebSocket messages are split into small packets called frames. These are transferred efficiently over the connection.

 
</details>

---
- [ ] **Q11 Built-in Events (Socket.IO)  ?**

<details>
<summary>Answer</summary>

| Event Name          | Triggered When…                                            | Listener Side |
| ------------------- | ---------------------------------------------------------- | ------------- |
| `connect`           | A client successfully connects to the server               | **Client**    |
| `connection`        | A new socket connection is made                            | **Server**    |
| `disconnect`        | A client disconnects (tab closed, refresh, network lost)   | **Both**      |
| `connect_error`     | Connection fails (e.g., server down, CORS issue)           | **Client**    |
| `reconnect`         | Client reconnects after disconnection                      | **Client**    |
| `reconnect_attempt` | A reconnection attempt is being made                       | **Client**    |
| `ping`              | Server pings the client to check if it's alive (low-level) | **Internal**  |
| `pong`              | Client responds to ping (used to measure latency)          | **Internal**  |
| `error`             | An error occurs on the socket                              | **Both**      |


 
</details>

---