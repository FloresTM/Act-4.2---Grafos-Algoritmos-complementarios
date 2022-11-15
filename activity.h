#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: David Langarica | Sebastian Flores
// Date: 15 noviembre 2022
// =========================================================

#include "ugraph.h"

template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph,
          std::set<Vertex>& reached, std::stack<Vertex>& TS) {
    typename std::set<Vertex>::iterator itr;

    reached.insert(v);

    for (auto itr : graph->getConnectionFrom(v)) {
        if (reached.find(itr) == reached.end()) {
            dfs2(itr, graph, reached, TS);
        }
    }

    TS.push(v);
}

template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
    typename std::vector<Vertex>::iterator itr;
    std::stringstream aux;

    std::set<Vertex> reached;
    std::stack<Vertex> TS;
    int count = 0;
    int temp_size;

    for (auto v : graph->getVertexes()) {
        if (reached.find(v) == reached.end()) {
            dfs2(v, graph, reached, TS);
        }
    }

    aux << "[";

    while (!TS.empty()) {
        aux << TS.top() << " ";
        TS.pop();
    }

    aux.seekp(-1, std::ios_base::end);

    aux << "]";

    return aux.str();
}

template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {
    std::queue<Vertex> q;

    std::vector<Vertex> vertexes_in_g;

    vertexes_in_g = graph->getVertexes();

    std::vector<int> color(vertexes_in_g.size(), -1);

    bool isbipartite;
    isbipartite = true;

    Vertex vertex = vertexes_in_g.front();
    Vertex u;
    color[0] = 1;

    q.push(vertex);

    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (auto v : graph->getConnectionFrom(u)) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);

            } else if (color[v] == color[u]) {
                isbipartite = false;
            }  // end if
        }      // end for
               // return 1;
    }          // en while

    return isbipartite;

}  // cierra funcion

template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph,
              std::set<Vertex>& reached, Vertex parent) {
    reached.insert(v);

    for (auto u : graph->getConnectionFrom(v)) {
        if (reached.find(u) == reached.end()) {
            if (isCyclic(u, graph, reached, parent))
                return 1;
        }

        else if (u != parent)
            return 1;
    }

    return 0;
}

template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
    for (auto u : graph->getVertexes()) {
        std::set<Vertex> reached;

        if (isCyclic(u, graph, reached, u))
            return 0;
    }

    for (auto v : graph->getVertexes()) {
        std::set<Vertex> reached_;
        if (reached_.find(v) != reached_.end()) {
            return 0;
        }
    }

    return 1;
}

#endif /* ACTIVITY_H */
 