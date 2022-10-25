import copy
from heapq import heappush, heappop


class GraphException(Exception):
    pass


# the class used for implementing the graph
class Graph:
    def __init__(self):
        self.__edges = dict()
        self.__costs = dict()
        self.__vertices = []
        for vertex in self.__vertices:
            self.addVertex(vertex)

        self._ham_path_cost = 0
        self._starting_vertex = 1
        self._ham_path_vertices = []
        self._visited = []

    # returns the nr of vertices
    def nrVertices(self):
        return len(self.__edges)

    # returns the number of edges
    def nrEdges(self):
        return len(self.__costs)

    # returns a boolean value that expresses the existence of a vertex first
    def checkVertex(self, first):
        if first in self.__edges:
            return True

        else:
            return False

    # returns a boolean value expressing th existence of an edge
    def checkEdge(self, vertex1, vertex2):
        if (vertex1, vertex2) in self.__costs or (vertex2, vertex1) in self.__costs:
            return True
        return False

    # adds a vertex
    def addVertex(self, vertex):
        if vertex in self.__edges:
            raise GraphException("The vertices that you want to add already exist!")
        else:
            self.__edges[vertex] = []

    # adds an edge to the graph
    def addEdge(self, vertex1, vertex2, cost):
        if vertex1 not in self.__edges or vertex2 not in self.__edges:
            raise GraphException("You cannot create an edge using unexistent vertices!")
        if vertex2 in self.__edges[vertex1] or vertex1 in self.__edges[vertex2]:
            raise GraphException("This edge already exists!")
        self.__edges[vertex1].append(vertex2)
        self.__edges[vertex2].append(vertex1)
        self.__costs[(vertex1, vertex2)] = cost
        self.__costs[(vertex2, vertex1)] = cost

    # removes the vertex from the graph
    def removeVertex(self, vertex):
        if self.checkVertex(vertex) is False:
            raise GraphException("This vertex is not in the graph!")
        else:
            new_edges_dict = self.copyEdges()
            ok = 0

            if vertex in self.__edges:
                del self.__edges[vertex]
                ok = 1
            if ok == 1:
                for edge in new_edges_dict:
                    if edge[0] == vertex or edge[1] == vertex:
                        del self.__costs[(edge[0], edge[1])]

    # removes an edge
    def removeEdge(self, vertex1, vertex2):
        if self.checkEdge(vertex1, vertex2) is False:
            raise GraphException("The edge between this two vertices does not exist!")
        else:
            for vertex in self.__edges:
                if vertex == vertex1:
                    self.__edges[vertex1].remove(vertex)
                if vertex == vertex2:
                    self.__edges[vertex2].remove(vertex)
            del self.__costs[(vertex1, vertex2)]

    # parses the vertices
    def vertices(self):
        vertices = []
        for key in self.__edges.keys():
            vertices.append(key)
        return vertices

    def Prim(graph, cost, start_vertex):
        distances = {start_vertex: 0}
        queue = [(0, start_vertex)]
        edges = []
        while queue != []:
            current_cost, current_vertex = heappop(queue)
            edges.append(current_vertex)
            if len(edges) == len(graph.vertices()):
                break
            for vertex in graph.__edges[current_vertex]:
                if not vertex in distances or \
                        cost[(vertex, current_vertex)] < distances[vertex] and vertex not in edges:
                    distances[vertex] = cost[(vertex, current_vertex)]
            minim = float('inf')
            minvertex = 0
            for vertex in distances.keys():
                if distances[vertex] < minim and vertex not in edges:
                    minim = distances[vertex]
                    minvertex = vertex

            heappush(queue, (minim, minvertex))
            # heappush(queue, (distances[vertex], vertex))

        return distances, edges

    def min_cost_path(graph, cost, vertex):
        # vertexes =[]
        distances = graph.Prim(cost, vertex)[0]
        for elem in distances.keys():
            for cost in graph.costs():
                if distances[elem] == graph.__costs[cost] and elem == cost[1]:
                    print(cost)
                    # vertexes.append(cost)

    def dfs_nearest_neighbor(self, source_vertex, cycle_length):
        self._visited[source_vertex] = True
        sorted_outbound_neighbours = self.__edges[source_vertex]
        sorted_outbound_neighbours = sorted(sorted_outbound_neighbours,
                                            key=lambda edge1: self.__costs[(source_vertex, edge1)])
        found_original_vertex = False

        for edge in sorted_outbound_neighbours:
            neighbor = edge
            if neighbor == self._starting_vertex and cycle_length == len(self.vertices()) - 1:
                self._ham_path_vertices.append(source_vertex)
                self._ham_path_cost += self.__costs[(source_vertex, edge)]
                return True
            elif not self._visited[neighbor]:
                found_original_vertex = self.dfs_nearest_neighbor(neighbor, cycle_length + 1)
                if found_original_vertex:
                    self._ham_path_vertices.append(source_vertex)
                    self._ham_path_cost += self.__costs[(source_vertex, edge)]
                    return True

        self._visited[source_vertex] = False
        return found_original_vertex

    def approximate_tsp_nearest_neighbor(self):
        self._starting_vertex = 1
        self._ham_path_cost = 0
        self._visited.clear()
        for i in range(0, len(self.vertices())):
            self._visited.append(False)

        self._ham_path_vertices.clear()
        self.dfs_nearest_neighbor(self._starting_vertex, 0)
        self._ham_path_vertices.insert(0, self._starting_vertex)

    def get_ham_path_vertices(self):
        return self._ham_path_vertices

    def get_ham_path_cost(self):
        return self._ham_path_cost

    def costs(self):
        return self.__costs

    # parses the outbounds
    def edges(self):
        return [self.__edges]

    # copies the edges
    def copyCosts(self):
        return copy.deepcopy(self.__costs)

    # copies the graph
    def copyGraph(self):
        return copy.deepcopy(self)

    # cpies the vertices
    def copyVertices(self):
        return copy.deepcopy(self.vertices())

    # copies the inbounds
    def copyEdges(self):
        return copy.deepcopy(self.__edges)

    # returns the cost of an edge
    def getEdgeCost(self, vertex1, vertex2):
        if self.checkEdge(vertex1, vertex2) is False:
            raise Exception("This edge does not exist!")

        return self.__costs[(vertex1, vertex2)]

    # sets the cost of an edge
    def setEdgeCost(self, vertex1, vertex2, cost):
        if self.checkEdge(vertex1, vertex2) is False:
            raise Exception("This edge does not exist!")

        self.__costs[(vertex1, vertex2)] = cost

    # prints the graph
    def printGraph(self):
        for edge in self.__costs:
            print("Vertices {0} {1} Cost: {2} ".format(edge[0], edge[1], self.__costs[edge]))


