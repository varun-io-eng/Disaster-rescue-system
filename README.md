# 🚨 Disaster Rescue System  

A **C++ console-based Disaster Management System** that helps coordinate **rescue teams** and manage **disaster-hit areas**.  
This project demonstrates the use of **graphs (for area connections), shortest path algorithms (Dijkstra), and priority queues (for severity-based dispatching)** in real-world scenarios like disaster response.  

---

## 📌 Features  
- Add new **areas** with severity levels (1–10).  
- Connect areas with **distances** (bidirectional edges).  
- Add **rescue teams** (all start at the base by default).  
- **Dispatch rescue teams** to the most severe disaster-affected areas using shortest path calculation.  
- Display a **summary** of areas and rescue teams.  
- Menu-driven system with interactive console inputs.  

---

## 🛠️ Technologies Used  
- **Language:** C++  
- **Data Structures:**  
  - Graph (Adjacency List with `unordered_map`)  
  - Priority Queue (for severity-based dispatching & Dijkstra’s Algorithm)  
  - STL containers (`vector`, `queue`, `unordered_map`, etc.)  

---

## ⚙️ How It Works  
1. **Areas & Connections:**  
   - Each area has a severity level (0–10).  
   - Areas can be connected with distances, forming a graph.  

2. **Rescue Teams:**  
   - Rescue teams start at a central **base**.  
   - Teams can be dispatched to the **highest severity areas first**.  

3. **Dispatching Logic:**  
   - If teams are available at the base, they are dispatched directly.  
   - If not, the system finds the **nearest available team** using **Dijkstra’s algorithm**.  
   - After rescue, the area’s severity is reset to **0**.  

---

## 📋 Menu Options  
-===== DISASTER MANAGEMENT SYSTEM =====
-[1] Add Area
-[2] Connect Areas
-[3] Add Rescue Team
-[4] Dispatch Rescue Teams (By Severity)
-[5] Show Summary
-[0] Exit
-Type `99` anytime to re-display the menu.  

---

## ▶️ How to Run  


-Enter your choice (type 99 to show menu): 1
-Enter area name: ZoneA
-Enter severity (1-10): 8
-[SUCCESS] Area 'ZoneA' added with severity 8.

-Enter your choice: 2
-Enter area 1: base
-Enter area 2: ZoneA
-Enter distance: 5
-[SUCCESS] Connected base <--> ZoneA with distance 5.

-Enter your choice: 3
-Enter rescue team name: Team1
-[SUCCESS] Rescue team 'Team1' added at base.

-Enter your choice: 4
-[DISPATCH] 'Team1' dispatched to ZoneA via: base -> ZoneA
