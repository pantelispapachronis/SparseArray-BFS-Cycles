# Sparse Graph Implementation with BFS and Cycle Detection

## **Description**
This project implements a **sparse graph** using a **custom data structure** with linked lists. The program supports:
- **Insertion & Deletion** of elements in the sparse array.
- **Breadth-First Search (BFS)** for graph traversal.
- **Cycle detection** to identify loops in the graph.
- **Queue-based BFS** implementation.
- **Efficient memory management** with proper deallocation.

The graph is represented using two **30×30 arrays** (`Vertical` and `Horizontal`), and each node contains pointers to its **adjacent** elements. The implementation optimizes memory usage and ensures efficient search and traversal operations.

---

## **Features**
- **Sparse Graph Representation**: Efficient adjacency storage using linked lists.
- **Insertion (`insert(x, y)`)**: Adds an edge `(x, y)` while maintaining adjacency lists.
- **Deletion (`delete(x, y)`)**: Removes an edge `(x, y)` and properly reconnects nodes.
- **Printing (`print()`)**: Displays the sparse array structure for visualization.
- **BFS (`bfs(root)`)**: Implements breadth-first search from a given node with distance tracking.
- **Cycle Detection (`cycles(a, b)`)**: Detects cycles when adding an edge, ensuring graph integrity.
- **Memory Management (`freeGraph()`)**: Properly deallocates dynamically allocated nodes to prevent memory leaks.

---

## **Getting Started**
### **Compilation & Execution**
To compile the program, use:
```sh
gcc -o sparse_graph main.c -Wall -Wextra -pedantic -std=c11
```

To run the program:
```sh
./sparse_graph
```

---

## **Usage**
When the program runs, it provides a menu with options:
```
(I) Insert a new element
(P) Print the sparse array
(D) Delete an element
(B) Perform Breadth-First Search (BFS)
(C) Detect cycles
(Q) Quit
```
The user can **input** commands to interact with the graph.

### **Example**
1. Insert `(1, 2)`:
    ```
    Give x: 1
    Give y: 2
    Element Inserted!
    ```
2. Print the graph:
    ```
    Sparse Array:
    (1,2) (2,1)
    ```
3. Perform BFS from node `1`:
    ```
    Node 2 
    Distance: 1 
    Parent: 1
    ```
4. Detect cycles when adding `(1, 3)`:
    ```
    Cycle detected between (1,3)
    ```

---

## **Implementation Details**
### **Data Structures**
- `struct Node`: Represents a **graph node** with adjacency pointers.
- `struct queue`: Implements a **FIFO queue** for BFS.
- `struct cycleList`: Supports **cycle detection**.

## **Future Enhancements**
- **Graph visualization** using an external tool (e.g., Graphviz).
- **Weighted graph support**.
- **Shortest path algorithms** (Dijkstra, Floyd-Warshall).

---

## **Author**
Developed by **Pantelis Papachronis** – Feel free to contribute or suggest improvements!