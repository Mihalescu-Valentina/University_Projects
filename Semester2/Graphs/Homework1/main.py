import random


class UserInputException(Exception):
    pass


from Graph import Graph, GraphException


def menu():
    print("1 - Create Graph")
    print("2 - Add vertex")
    print("3 - Add edge")
    print("4 - Remove vertex")
    print("5 - Remove edge")
    print("6 - Print vertices")
    print("7 - Print edges")
    print("8 - Check edge existence")
    print("9 - Get the in degree of a specified vertex")
    print("10 - Get the out degree of a specified vertex")
    print("11 - Get the in bounds vertices of a vertex")
    print("12 - Get the out bounds vertices of a vertex")
    print("13 - Get edge cost")
    print("14 - Set edge cost")
    print("15 - Read graph from text file")
    print("16 - Write graph to text file")
    print("17 - Generate random graph")
    print("0 - exit")


def generateRandomGraph(nr_vertices, nr_edges):
    nr = 0
    g = Graph()
    for x in range(nr_vertices):
        g.addVertex(x)
    while nr < nr_edges:
        origin = random.randrange(0, nr_vertices)
        target = random.randrange(0, nr_vertices)
        cost = random.randrange(0, nr_vertices)

        if g.checkEdge(origin, target) is False:
            g.addEdge(origin, target, cost)
            nr = nr + 1
    return g


def valid_graph(graph):
    if graph is None:
        raise GraphException("There's no graph created!")


def readGraph():
    file = open("file.txt", "r")
    n, m = map(int, file.readline().split())
    g = Graph()
    for x in range(n+1):
        g.addVertex(x)
    for line in range(m):
        vertex1, vertex2, edge_cost = map(int, file.readline().split())
        g.addEdge(vertex1, vertex2, edge_cost)
    file.close()
    return g


def printVertices(vertices):
    for vertex in vertices:
        print(vertex)


def printEdges(edges):
    for edge in edges:
        cost = edges[edge]
        print("Vertices {0} {1} Cost: {2} ".format(edge[0], edge[1], cost))


def printEdgeExistence(edge, existence):
    if existence:
        print(f"Edge ({edge[0]}, {edge[1]}) exists.")
    else:
        print(f"Edge ({edge[0]}, {edge[1]}) does not exist.")


def writeGraph(g):
    file = open("output.txt", "w")
    file.write("{0} {1}\n".format(g.nrVertices(), g.nrEdges()))
    edges = g.copyEdges()
    for edge in edges:
        file.write("{0} {1} {2}\n".format(edge[0], edge[1], edges[edge]))
    file.close()


def printOutbounds(g):
    print("Outbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.outbounds(x):
            s = s + " " + str(y)
        print(s)


def printInbounds(g):
    print("Inbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.inbounds(x):
            s = s + " " + str(y)
        print(s)


def valid(vertex1, vertex2):
    if vertex1.isdigit() is False and vertex2.isdigit() is False:
        raise UserInputException("The vertices must be numbers!!")

    return True


if __name__ == '__main__':
    menu()
    graph = None

    while True:
        user_command = input("Enter a command: ")

        try:
            if user_command == "0":
                break

            if user_command.isdigit() is False:
                raise UserInputException("Enter a numerical value between 0 and 18")

            if int(user_command) > 19 or int(user_command) < 0:
                raise UserInputException("Enter a correct numerical value between 0 and 18")

            if user_command == "1":
                graph = Graph()
            elif user_command == "2":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Enter vertex: "))
                graph.addVertex(vertex)
            elif user_command == "3":
                valid_graph(graph)  # validate graph existence
                vertex1 = int(input("Vertex 1: "))
                vertex2 = int(input("Vertex 2: "))
                cost = int(input("Cost: "))
                graph.addEdge(vertex1, vertex2, cost)
            elif user_command == "4":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Vertex 1: "))
                graph.removeVertex(vertex)
            elif user_command == "5":
                valid_graph(graph)  # validate graph existence
                vertex1 = int(input("Vertex 1: "))
                vertex2 = int(input("Vertex 2: "))
                graph.removeEdge(vertex1, vertex2)
            elif user_command == "6":
                valid_graph(graph)  # validate graph existence
                vertices_to_print = graph.vertices()
                printVertices(vertices_to_print)
            elif user_command == "7":
                valid_graph(graph)  # validate graph existence
                edges_to_print = graph.copyEdges()
                printEdges(edges_to_print)
            elif user_command == "8":
                valid_graph(graph)  # validate graph existence
                vertex1 = int(input("Vertex 1: "))
                vertex2 = int(input("Vertex 2: "))
                edge_existence = graph.checkEdge(vertex1, vertex2)
                printEdgeExistence([vertex1, vertex2], edge_existence)
            elif user_command == "9":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Vertex: "))
                print(graph.get_in_degree(vertex))
            elif user_command == "10":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Vertex: "))
                print(graph.get_out_degree(vertex))
            elif user_command == "11":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Vertex: "))
                in_bounds_vertices = graph.inbounds(vertex)
                printVertices(in_bounds_vertices)
            elif user_command == "12":
                valid_graph(graph)  # validate graph existence
                vertex = int(input("Vertex: "))
                out_bounds_vertices = graph.outbounds(vertex)
                printVertices(out_bounds_vertices)
            elif user_command == "13":
                valid_graph(graph)  # validate graph existence
                vertex1 = int(input("Vertex 1: "))
                vertex2 = int(input("Vertex 2: "))
                print(graph.getEdgeCost(vertex1, vertex2))
            elif user_command == "14":
                valid_graph(graph)  # validate graph existence
                vertex1 = int(input("Vertex 1: "))
                vertex2 = int(input("Vertex 2: "))
                cost = int(input("Cost: "))
                graph.setEdgeCost(vertex1, vertex2, cost)
            elif user_command == "15":
                graph = readGraph()
            elif user_command == "16":
                if graph != None:
                    writeGraph(graph)
            elif user_command == "17":
                nr_of_vertices = int(input("Number of vertices: "))
                nr_of_edges = int(input("Number of edges: "))
                graph = generateRandomGraph(nr_of_vertices, nr_of_edges)

            elif user_command == "18":
                vertex1 = int(input("Vertex1"))
                vertex2 = int(input("Vertex2"))
                print(graph.shortest_path(vertex1, vertex2))

            elif user_command == "19":
                vertex1 = int(input("Vertex1 "))
                vertex2 = int(input("Vertex2 "))
                print(graph.min_cost_path(graph.costs(),vertex1,vertex2))



        except Exception as message:
            print(message)
