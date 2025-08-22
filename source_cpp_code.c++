#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

class Area {
public:
    string name;
    int severity;
    unordered_map<string, int> neighbors;

    Area(string n, int s) : name(n), severity(s) {}
};

class RescueTeam {
public:
    string id;
    string location;
    bool busy;

    RescueTeam(string i) : id(i), location("base"), busy(false) {}
};

class DisasterSystem {
    unordered_map<string, Area*> areas;
    vector<RescueTeam*> teams;
    const string base = "base";

public:
    DisasterSystem() {
        areas[base] = new Area(base, 0);
    }

    void addArea(const string& name, int severity) {
        areas[name] = new Area(name, severity);
        cout << "[SUCCESS] Area '" << name << "' added with severity " << severity << ".\n";
    }

    void connectAreas(const string& a1, const string& a2, int dist) {
        if (areas.count(a1) && areas.count(a2)) {
            areas[a1]->neighbors[a2] = dist;
            areas[a2]->neighbors[a1] = dist;
            cout << "[SUCCESS] Connected " << a1 << " <--> " << a2 << " with distance " << dist << ".\n";
        } else {
            cout << "[ERROR] One or both areas not found!\n";
        }
    }

    void addRescueTeam(const string& id) {
        teams.push_back(new RescueTeam(id));
        cout << "[SUCCESS] Rescue team '" << id << "' added at base.\n";
    }

    void showMenu() {
        cout << "\n===== DISASTER MANAGEMENT SYSTEM =====\n";
        cout << "[1] Add Area\n[2] Connect Areas\n[3] Add Rescue Team\n";
        cout << "[4] Dispatch Rescue Teams (By Severity)\n[5] Show Summary\n[0] Exit\n";
    }

    void showSummary() {
        cout << "\n--- Area Summary ---\n";
        for (auto& [name, area] : areas) {
            cout << name << ": Severity " << area->severity << "\n";
        }

        cout << "\n--- Rescue Teams ---\n";
        for (auto* team : teams) {
            cout << "Team " << team->id << " at " << team->location << (team->busy ? " [BUSY]\n" : "\n");
        }
    }

    void dispatchTeams() {
        // Create max-heap by severity
        priority_queue<pair<int, string>> pq;
        for (auto& [name, area] : areas) {
            if (area->severity > 0) {
                pq.push({area->severity, name});
            }
        }

        while (!pq.empty()) {
            auto [sev, zone] = pq.top(); pq.pop();

            // First, try to assign from base
            RescueTeam* available = nullptr;
            for (auto* team : teams) {
                if (!team->busy && team->location == base) {
                    available = team;
                    break;
                }
            }

            // If none at base, try to reassign from already dispatched teams
            if (!available) {
                int minDist = INT_MAX;
                for (auto* team : teams) {
                    if (!team->busy && team->location != base) {
                        int dist = getShortestDistance(team->location, zone);
                        if (dist < minDist) {
                            available = team;
                            minDist = dist;
                        }
                    }
                }
            }

            if (!available) {
                cout << "[INFO] No available teams for " << zone << "\n";
                continue;
            }

            // Assign the selected team
            vector<string> path = getShortestPath(available->location, zone);
            if (path.empty()) {
                cout << "[ERROR] No path from " << available->location << " to " << zone << "\n";
                continue;
            }

            cout << "[DISPATCH] '" << available->id << "' dispatched to " << zone << " via: ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i + 1 < path.size()) cout << " -> ";
            }
            cout << "\n";

            // Update system state
            available->location = zone;
            available->busy = false; // Assume instant rescue
            areas[zone]->severity = 0;
        }
    }

    int getShortestDistance(const string& start, const string& end) {
        if (!areas.count(start) || !areas.count(end)) return INT_MAX;
        unordered_map<string, int> dist;
        for (auto& [name, _] : areas) dist[name] = INT_MAX;

        dist[start] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            for (auto& [v, w] : areas[u]->neighbors) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[end];
    }

    vector<string> getShortestPath(const string& start, const string& end) {
        if (!areas.count(start) || !areas.count(end)) return {};
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;

        for (auto& [name, _] : areas) dist[name] = INT_MAX;
        dist[start] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            for (auto& [v, w] : areas[u]->neighbors) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[end] == INT_MAX) return {};
        vector<string> path;
        string cur = end;
        while (cur != start) {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

// ======================= MAIN ========================

int main() {
    DisasterSystem system;
    int choice;

    system.showMenu();

    while (true) {
        cout << "\nEnter your choice (type 99 to show menu): ";
        cin >> choice;

        if (choice == 0) break;
        else if (choice == 99) system.showMenu();
        else if (choice == 1) {
            string name; int severity;
            cout << "Enter area name: "; cin >> name;
            cout << "Enter severity (1-10): "; cin >> severity;
            system.addArea(name, severity);
        } else if (choice == 2) {
            string a1, a2; int dist;
            cout << "Enter area 1: "; cin >> a1;
            cout << "Enter area 2: "; cin >> a2;
            cout << "Enter distance: "; cin >> dist;
            system.connectAreas(a1, a2, dist);
        } else if (choice == 3) {
            string id;
            cout << "Enter rescue team name: "; cin >> id;
            system.addRescueTeam(id);
        } else if (choice == 4) {
            system.dispatchTeams();
        } else if (choice == 5) {
            system.showSummary();
        } else {
            cout << "[ERROR] Invalid choice.\n";
        }
    }

    cout << "[EXIT] Disaster Management System Closed.\n";
    return 0;
}


