#include <bits/stdc++.h>
using namespace std;

class MetroNetwork {
public:
    unordered_map<int, vector<tuple<int, double, double>>> adjList; // dest, time, fare
    unordered_map<int, string> idToStation;

    void addStation(int id, string name) {
        idToStation[id] = name;
    }

    void addRoute(int from, int to, double time, double fare) {
        adjList[from].push_back({to, time, fare});
        adjList[to].push_back({from, time, fare});
    }

    void displayStations() {
        cout << "Available Stations:\n";
        for (auto &[id, name] : idToStation) {
            cout << id << ": " << name << endl;
        }
    }

    vector<int> shortestPath(int src, int dest, string mode, double &total) {
        int n = idToStation.size();
        vector<double> cost(n, 1e9);
        vector<int> parent(n, -1);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

        cost[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [currCost, u] = pq.top(); pq.pop();
            if (u == dest) break;

            for (auto &[v, time, fare] : adjList[u]) {
                double weight = (mode == "time") ? time : (mode == "fare" ? fare : 1);
                if (cost[u] + weight < cost[v]) {
                    cost[v] = cost[u] + weight;
                    parent[v] = u;
                    pq.push({cost[v], v});
                }
            }
        }

        total = cost[dest];
        vector<int> path;
        for (int at = dest; at != -1; at = parent[at])
            path.push_back(at);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    MetroNetwork metro;

    // Add stations
    vector<string> stations = {
        "Rithala", "Rohini West", "Netaji Subhash Place", "Kashmere Gate", "Tis Hazari",
        "Rajiv Chowk", "Central Secretariat", "INA", "AIIMS", "Hauz Khas",
        "Green Park", "Saket", "Qutub Minar", "Chhatarpur", "Huda City Centre"
    };
    for (int i = 0; i < stations.size(); i++)
        metro.addStation(i, stations[i]);

    // Add routes (from, to, time, fare)
    vector<tuple<int, int, double, double>> routes = {
        {0, 1, 2.0, 10}, {1, 2, 2.5, 10}, {2, 3, 3.0, 10}, {3, 4, 2.0, 8}, {4, 5, 3.0, 10},
        {5, 6, 3.0, 10}, {6, 7, 2.5, 8}, {7, 8, 2.0, 8}, {8, 9, 2.0, 10}, {9,10, 2.0, 8},
        {10,11,3.0,10}, {11,12,2.5,10}, {12,13,2.5,10}, {13,14,3.0,12}
    };
    for (auto &[u, v, t, f] : routes)
        metro.addRoute(u, v, t, f);

    // Show station list
    metro.displayStations();

    int src, dest;
    cout << "\nEnter source station ID: ";
    cin >> src;
    cout << "Enter destination station ID: ";
    cin >> dest;

    cout << "\nChoose optimization:\n";
    cout << "1. Minimum Fare\n2. Minimum Time\n3. Minimum Stations\n";
    int choice;
    cin >> choice;

    string mode;
    if (choice == 1) mode = "fare";
    else if (choice == 2) mode = "time";
    else mode = "stations";

    double total = 0;
    vector<int> path = metro.shortestPath(src, dest, mode, total);

    cout << "\nPath:\n";
    for (int id : path) {
        cout << metro.idToStation[id];
        if (id != dest) cout << " -> ";
    }

    cout << "\nTotal " << (mode == "fare" ? "Fare: ₹" : mode == "time" ? "Time: " : "Stations: ");
    if (mode == "stations")
        cout << path.size() - 1 << endl;
    else
        cout << total << (mode == "time" ? " mins" : "") << endl;

    return 0;
}
