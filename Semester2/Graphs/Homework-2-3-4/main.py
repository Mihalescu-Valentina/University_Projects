class UserInputException(Exception):
    pass

from  undirectedGraph import Graph, GraphException

def valid_graph(graph):
    if graph is None:
        raise GraphException("There's no graph created!")


def readGraph():
    file = open("undirectedgraph.txt", "r")
    n, m = map(int, file.readline().split())
    g = Graph()
    for x in range(n):
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

def menu():
    print("1 - Create Graph")
    print("2 - Minimal spanning tree using the Prim's algorithm")
    print("3 - Print the vertices")
    print("4 - Prim's algorithm")
    print("5 - Read graph from text file")

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

            if int(user_command) > 6 or int(user_command) < 1:
                raise UserInputException("Enter a correct numerical value between 0 and 18")

            if user_command == "1":
                graph = Graph()

            if user_command == "2":
                pass

            if user_command == "3":
                valid_graph(graph)  # validate graph existence
                vertices_to_print = graph.vertices()
                printVertices(vertices_to_print)

            elif user_command == "4":
                valid_graph(graph)  # validate graph existence
                edges_to_print = graph.copyCosts()
                #printEdges(edges_to_print)
                print(graph.Prim(graph.costs(),0))
                graph.min_cost_path(graph.costs(),0)



            elif user_command == "5":
                graph = readGraph()

            elif user_command == "6":
                graph.approximate_tsp_nearest_neighbor()

                ham_path_vertices = graph.get_ham_path_vertices()

                if len(ham_path_vertices) == 0:
                    print("No cycle found (perhaps the graph is acyclic ?)\n")
                    break

                #print("Hamiltonian cycle cost: " + str(graph.get_ham_path_cost()))
                path = ""
                for vertex in graph.get_ham_path_vertices():
                    path += str(vertex) + " -> "
                path = path[:-4]
                print(path)

        except Exception as message:
            print(message)
