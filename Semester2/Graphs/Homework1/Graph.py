import copy
from heapq import heappush, heappop


class GraphException(Exception):
    pass


# the class used for implementing the graph
class Graph:
    def __init__(self):
        self.__inbounds = dict()
        self.__outbounds = dict()
        self.__costs = dict()
        self.__vertices = []
        for vertex in self.__vertices:
            self.addVertex(vertex)

    # returns the nr of vertices
    def nrVertices(self):
        return len(self.__outbounds)

    # returns the number of edges
    def nrEdges(self):
        return len(self.__costs)

    # returns a boolean value that expresses the existence of a vertex first
    def checkVertex(self, first):
        if first in self.__outbounds:
            return True

        else:
            return False

    # returns a boolean value expressing th existence of an edge
    def checkEdge(self, vertex1, vertex2):
        if (vertex1, vertex2) in self.__costs:
            return True
        return False

    # adds a vertex
    def addVertex(self, vertex):
        if vertex in self.__inbounds:
            raise GraphException("The vertices that you want to add already exist!")
        else:
            self.__outbounds[vertex] = []
            self.__inbounds[vertex] = []

    # adds an edge to the graph
    def addEdge(self, vertex1, vertex2, cost):
        if vertex1 not in self.__outbounds or vertex1 not in self.__inbounds:
            raise GraphException("You cannot create an edge using unexistent vertices!")
        if vertex2 in self.__outbounds[vertex1]:
            raise GraphException("This edge already exists!")
        self.__outbounds[vertex1].append(vertex2)
        self.__inbounds[vertex2].append(vertex1)
        self.__costs[(vertex1, vertex2)] = cost

    # removes the vertex from the graph
    def removeVertex(self, vertex):
        if self.checkVertex(vertex) is False:
            raise GraphException("This vertex is not in the graph!")
        else:
            new_edges_dict = self.copyEdges()
            ok = 0

            if vertex in self.__outbounds:
                del self.__outbounds[vertex]
                del self.__inbounds[vertex]
                ok = 1
            if ok == 1:
                for edge in new_edges_dict:
                    if edge[0] == vertex or edge[1] == vertex:
                        del self.__costs[(edge[0], edge[1])]


    def shortest_path(self, start_vertex, end_vertex):
        '''Finds the shortest (min length) path from start_vertex to end_vertex
        in the graph 'graph'.
        Returns the list of vertices along the path, starting with start_vertex
        and ending with end_vertex.
        If start_vertex == end_vertex, it returns [start_vertex]
        If there is no path -> returns None`
        If there are several paths of the same length -> returns either of them
        '''
        distances = self.bfs(end_vertex)

        if start_vertex not in distances:
            return None

        path = [start_vertex]
        current_vertex = start_vertex
        while current_vertex != end_vertex:
            for each_vertex in self.__outbounds[current_vertex]:
                if each_vertex in distances.keys() and distances[each_vertex] == distances[current_vertex] - 1:
                    current_vertex = each_vertex
                    path.append(current_vertex)
                    break

        path.reverse()
        return path

    def bfs(self, end_vertex):
        '''Parses the accessible vertices in a Breadth First Search traversal starting from start_vertex.
        Returns a dictionary where the keys are the vertices accessible from start_vertex and
        the values are the distances from start_vertex to each of them.
        queue a list that acts like the queue data structure and as the real life queue by adding elements at the end and poping them from the beginning
        '''
        distances = {end_vertex: 0}
        queue = [end_vertex]
        while queue != []:
            current_vertex = queue.pop(0)
            for vertex in self.__inbounds[current_vertex]:
                if not vertex in distances:
                    queue.append(vertex)
                    distances[vertex] = distances[current_vertex] + 1
        return distances

    def dijkstra(graph, cost, start_vertex, end_vertex=None):
        '''Parses the accessible vertices executing Dijkstra from start_vertex.
        Returns a dictionary where the keys are the vertices accessible from start_vertex and
        the values are the distances from start_vertex to each of them.
        '''
        distances = {end_vertex: 0}
        queue = [(0, end_vertex)]
        while queue != []:
            current_cost, current_vertex = heappop(queue)
            if current_vertex == start_vertex:
                break
            if current_cost > distances[current_vertex]:
                continue
            for vertex in graph.__inbounds[current_vertex]:
                if not vertex in distances or \
                        distances[current_vertex] + cost[(vertex,current_vertex)] < distances[vertex]:
                    distances[vertex] = distances[current_vertex] + cost[(vertex,current_vertex)]
                    heappush(queue, (distances[vertex], vertex))
        return distances

    def min_cost_path(graph, cost, start_vertex, end_vertex):
        '''Finds the min cost path from start_vertex to end_vertex
        in the graph 'graph'.
        Returns the list of vertices along the path, starting with start_vertex
        and ending with end_vertex.
        If start_vertex == end_vertex, it returns [start_vertex]
        If there is no path -> returns None`
        If there are several paths of the same length -> returns either of them
        If start_vertex or end_vertex is not a vertex -> anything can happen
        '''
        distances = graph.dijkstra(cost, start_vertex, end_vertex)


        if start_vertex not in distances:
            return None

        path = [start_vertex]
        current_vertex = start_vertex
        while current_vertex != end_vertex:
            found = False
            for next_vertex in graph.__outbounds[current_vertex]:
                if next_vertex in distances.keys() and \
                        distances[next_vertex] + cost[(current_vertex, next_vertex)] == distances[current_vertex]:
                    current_vertex = next_vertex
                    path.append(current_vertex)
                    found = True
                    break
            if not found:
                raise Exception(f"Could not found previous vertex for {current_vertex}")
        path.reverse()
        return path

    # removes the outerbounds
    def removeOut(self, vertex1, vertex2):
        if self.checkEdge(vertex1, vertex2) is False and vertex1 not in self.__outbounds:
            raise GraphException("The edge does not exist!")
        else:
            for vertex in self.__outbounds[vertex1]:
                if vertex == vertex2:
                    self.__outbounds[vertex1].remove(vertex)

    # removes the innerbound vertex1 vertex2
    def removeIn(self, vertex1, vertex2):
        if self.checkEdge(vertex1, vertex2) is False and vertex1 not in self.__inbounds:
            raise GraphException("The edge does not exist!")
        else:
            for vertex in self.__inbounds[vertex1]:
                if vertex == vertex2:
                    self.__inbounds[vertex1].remove(vertex)

    # removes an edge
    def removeEdge(self, vertex1, vertex2):
        if self.checkEdge(vertex1, vertex2) is False:
            raise GraphException("The edge between this two vertices does not exist!")
        else:
            self.removeIn(vertex1, vertex2)
            self.removeOut(vertex1, vertex2)
            del self.__costs[(vertex1, vertex2)]

    # parses the vertices
    def vertices(self):
        vertices = []
        for key in self.__outbounds.keys():
            vertices.append(key)
        return vertices

    def edges(self):
        return self.__costs

    # returns the inner degree
    def get_in_degree(self, vertex):
        return len(self.__inbounds[vertex])

    # returns the outter degreee
    def get_out_degree(self, vertex):
        return len(self.__outbounds[vertex])

    def costs(self):
        return self.__costs

    # parses the outbounds
    def outbounds(self, vertex):
        return [self.__outbounds[vertex]]

    # returns the inbounds
    def inbounds(self, vertex):
        return [self.__inbounds[vertex]]

    # copies the edges
    def copyEdges(self):
        return copy.deepcopy(self.__costs)

    # copies the graph
    def copyGraph(self):
        return copy.deepcopy(self)

    # cpies the vertices
    def copyVertices(self):
        return copy.deepcopy(self.vertices())

    # copies the inbounds
    def copyInbounds(self):
        return copy.deepcopy(self.__inbounds)

    def copyOutbounds(self):
        return copy.deepcopy(self.__outbounds)

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


def print_graph(g):
    print("Outbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.outbounds(x):
            s = s + " " + str(y)
        print(s)
    print("Inbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.inbounds(x):
            s = s + " " + str(y)
        print(s)
