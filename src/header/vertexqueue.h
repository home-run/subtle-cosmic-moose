/**************************************************************************
 * AUTHOR   : Jesse Mazzella && Dan Karlsson
 * CLASS    : CS1D
 * DATE     : 05-14-2016
 * PROJECT  : 2 - Fantasy Baseball Vacation
 *************************************************************************/
#ifndef VERTEXQUEUE_H
#define VERTEXQUEUE_H

#include "Exceptions.h"
#include <QMap>
#include "vertex.h"
#include <QVector>
#include <iostream>

template <typename C>
class VertexQueue
{
public:
    /**
     * @brief
     * Create a Heap and initialize by pushing a dummy value into
     * the vector to keep the arithmetic nice.
     */
    VertexQueue()
    {
        Vertex *newT = new Vertex();
        elements.push_back(*newT);
        delete newT;
    }

    ~VertexQueue()
    { }

    /**
     * @brief
     * Retrieve the value at the top of the heap.
     * @return a copy of the root value of the heap.
     */
    const Vertex &root() const
    {
        return *(elements.begin() + 1);
    }

    /**
     * @brief
     * Retrieve the current height of the heap.
     * @return the height of the heap.
     */
    int height() const
    {
        int size = this->size();
        int height = 0;
        while (size > 0)
        {
            size = size / 2;
            height++;
        }
        return height;
    }

    /**
     * @brief
     * Retrieve the number of elements currently in the heap.
     * @return the size of the heap.
     */
    int size() const
    {
        return elements.size() - 1;
    }

    /**
     * @brief
     * Insert a new element into the heap and call bubble up to fix
     * element hierarchy.
     * @param newElement the element to add
     */
    void insert(Vertex& newElement)
    {
        elements.push_back(newElement);
        //call bubbleUp from the last element in the heap
        bubbleUp(size());
        reindex();
    }

    /**
     * @brief
     * Remove an element from the heap and bubble down to preserve
     * the proper element hierarchy.
     * @param index the index of the element to remove
     */
    void remove(int index)
    {
        if(index == 0){ index = 1; }

        if (!isEmpty())
        {
            elements[index] = elements[size()];
            elements.pop_back();
            bubbleDown(index);
            reindex();
        }
        else
        {
            throw RuntimeException("Heap is empty!");
        }
    }

    /**
     * @brief
     * Check if the heap is empty.
     * @return true if elements size is 0.
     */
    bool isEmpty() const
    {
        return size() == 0;
    }

    /**
     * @brief removeMin
     * This method will get the root element and pop it off the front of the heap.
     * @return root node
     */
    Vertex removeMin()
    {
        Vertex rootNode;
        rootNode = this->root();
        vertexMap.remove(rootNode.getName());
        this->remove(1);
        return rootNode;
    }

    /**
     * @brief decreaseKey
     * This method will take a key and vertex the find it within the vertexqueue then
     * replace its current distance key with the given key.
     * @param key
     * @param vertex
     */
    void decreaseKey(long key, Vertex vertex)
    {
        int index = 0;
        index = vertexMap.value(vertex.getName());
        qDebug() << "Decrease key " << key << " index - " << index;
        qDebug() << "Setting " << vertex.getName() << " with weight " << vertex.getDistance() << " to the weight " << key;
        elements[index].setDistance(key);
    }

    /**
     * @brief getVertexIndex
     * This method will return the index of the vertex that is located within the vertex
     * queue. The vertex will be given to a map that uses the vertex's name as the key
     * and the value is the index of the vertex in the queue.
     * @param vertex
     * @return int value of the index in the priority queue
     */
    int getVertexIndex(Vertex vertex) const
    {
        return vertexMap.value(vertex.getName());
    }

    /**
     * @brief printElementList
     * Method for debugging the priority queue. This will print the vertices to the
     * console.
     */
    void printElementList()
    {
        for(int i = 1; i < elements.size(); i++)
        {
            qDebug() << "Element - " << elements[i].getName() << " with weight " << elements[i].getDistance();
        }
    }

    /**
     * @brief printMap
     * This method will iterate through the map output the list of values for the unique
     * keys that are stored within the vertex map.
     */
    void printMap()
    {
        QList<QString> list;
        list = vertexMap.uniqueKeys();
        for(int i = 0; i < list.size(); i++)
        {
            qDebug() << "Map index " << vertexMap.value(elements[i].getName()) << " is " << list[i];
        }
    }

    /**
     * @brief reindex
     * This method will iterate through the vertexMap and change the current value of
     * the given key in the map.
     */
    void reindex()
    {
        if(elements.size() > 0)
        {
            for(int i = 1; i < this->size();i++)
            {
                vertexMap.insert(elements[i].getName(),i);
            }
        }
    }

    /**
     * @brief contains
     * This method wraps the vertex map object containing the vertices and will check
     * if the priority queue contain the given vertex.
     * @param vertex
     * @return true if the priority queue contains the vertex; otherwise returns false
     */
    bool contains(Vertex vertex)
    {
        return vertexMap.contains(vertex.getName());
    }

protected:

    /**
     * @brief
     * Iterate up the heap, comparing child to parent. If hierarchy
     * is violated, swap the elements.
     * @param index index of the heap to start from.
     */
    void bubbleUp(int index)
    {
        if (index > 1)
        {
            if (isLess(elements.at(index),
                       elements.at(parent(index))))
            {
                swap(parent(index), index);
            }
            index = parent(index);

            bubbleUp(index);
        }

    }

    /**
     * @brief
     * Iterate down the heap, comparing parent to child. If hierarchy
     * is violated, swap the elements.
     * @param index index of the heap to start from.
     */
    void bubbleDown(int index)
    {
        //if this node has any children
        while (hasLeft(index) || hasRight(index))
        {
            //if this node has both left and right children
            if (hasLeft(index) && hasRight(index))
            {
                //if left child is less than right child
                if (isLess(elements[left(index)], elements[right(index)]))
                {
                    //if left child is less than parent, swap.
                    if (isLess(elements[left(index)], elements[index]))
                    {
                        swap(index, left(index));
                    }
                    index = left(index);
                }
                else
                {
                    //if right child is less than parent, swap
                    if (isLess(elements[right(index)], elements[index]))
                    {
                        swap(index, right(index));
                    }
                    index = right(index);
                }
            }
                //if parent has left child only
            else if (hasLeft(index))
            {
                //if child is less than parent, swap
                if (isLess(elements[left(index)], elements[index]))
                {
                    swap(index, left(index));
                }
                index = left(index);
            }
                //if parent has right child only
            else if (hasRight(index))
            {
                //if right child is less than parent, swap
                if (isLess(elements[right(index)], elements[index]))
                {
                    swap(index, right(index));
                }
                index = right(index);
            }
        }
    }



private:
    std::vector<Vertex> elements; ///< the vector of elements in the heap
    QMap<QString, int> vertexMap;

    /**
     * @brief
     * Swap two elements in the vector
     * @param index1 first index to swap
     * @param index2 second index to swap
     */
    void swap(int index1, int index2)
    {
        Vertex temp = elements.at(index1);
        elements.at(index1) = elements.at(index2);
        elements.at(index2) = temp;
    }

    C isLess; ///< The comparator to use for bubbleUp and bubbleDown

    /**
     * @brief
     * Retrieve the index of the parent of the node at a
     * particular index.
     * @param index child index to get parent index of
     * @return the parent index.
     */
    int parent(int index) const
    {
        return index / 2;
    }

    /**
     * @brief Retrieve the left child of the node at a particular index.
     * @param index parent index to get left child index of
     * @return left child index
     */
    int left(int index) const
    {
        if (hasLeft(index))
        {
            return index * 2;
        }
        else
        {
            throw RuntimeException("Index has no left child");
        }
    }

    /**
     * @brief Retrieve the right child of the node at a particular index.
     * @param index parent index to get right child index of
     * @return right child index
     */
    int right(int index) const
    {
        if (hasRight(index))
        {
            return index * 2 + 1;
        }
        else
        {
            throw RuntimeException("Index has no right child");
        }
    }

    /**
     * @brief Check if the node at a particular index has a left child.
     * @param index parent index to check
     * @return true if parent index has a left child
     */
    bool hasLeft(int index) const
    {
        return (index * 2) <= elements.size();
    }

    /**
     * @brief Check if the node at a particular index has a right child.
     * @param index parent index to check
     * @return true if parent index has a right child
     */
    bool hasRight(int index) const
    {
        return (index * 2 + 1) <= elements.size();
    }

    /**
     * @brief Check if the node at a particular index is the root node.
     * @param index node index to check
     * @return true if node index is the root node.
     */
    bool isRoot(int index) const
    {
        return index == 1;
    }

    /**
     * @brief Check if the node at a particular index is an internal node.
     * @param index node index to check
     * @return true if node is a parent
     */
    bool isInternal(int index) const
    {
        return ((index * 2) <= elements.size()) ||
               ((index * 2 + 1) <= elements.size());
    }

    /**
     * @brief Check if the node at a particular index is an external node.
     * @param index node index to check
     * @return true if node is a child
     */
    bool isExternal(int index) const
    {
        return ((index / 2) > 0);
    }


};


#endif // VERTEXQUEUE_H
