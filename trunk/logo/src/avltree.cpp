// Copyright (C) 2013 by the David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include "avltree.h"
#include "mem.h"
#include "logodata.h"
#include "appendablelist.h"
#include "debugheap.h"

// There isn't enough space to hold a single AVL node in a NODE*,
// so it's spread across two NODE objects with accessors to abtract
// this impelemention detail.
//
// +-----------------+
// | car = AVL left  |
// | cdr = ----------+----> +-----------------+
// | obj = key       |      | car = height  --+--> [int]
// |---------+-------+      | cdr = AVL Right |
//           |              | obj = value   --+--> [value object]
//           v              +-----------------+
//       [key object]
//


inline
NODE *
AvlCreateNode(
    NODE * Key,
    NODE * Value
    )
{
    NODE * firstNode  = newnode(CONS);
    NODE * secondNode = newnode(CONS);
    NODE * balance    = make_intnode(0);

    setcar(firstNode, NIL);
    setcdr(firstNode, secondNode);
    setobject(firstNode, Key);

    setcar(secondNode, balance);
    setcdr(secondNode, NIL);
    setobject(secondNode, Value);

    return firstNode;
}

inline
NODE *
AvlGetLeft(
    const NODE * AvlNode
    )
{
    return car(AvlNode);
}

inline
void
AvlSetLeft(
    NODE * AvlNode,
    NODE * NewLeftNode
    )
{
    setcar(AvlNode, NewLeftNode);
}

inline
NODE *
AvlGetKey(
    const NODE * AvlNode
    )
{
    return getobject(AvlNode);
}

inline
void
AvlSetKey(
    NODE * AvlNode,
    NODE * NewKey
    )
{
    setobject(AvlNode, NewKey);
}

inline
NODE *
AvlGetRight(
    const NODE *  AvlNode
    )
{
    return cddr(AvlNode);
}

inline
void
AvlSetRight(
    NODE * AvlNode,
    NODE * NewRightNode
    )
{
    setcdr(cdr(AvlNode), NewRightNode);
}

inline
int
AvlGetHeight(
    const NODE * Node
    )
{
    return getint(cadr(Node));
}


inline
void
AvlSetHeight(
    NODE *  Node,
    int     NewHeight
    )
{
    NODE * newHeightNode = make_intnode(NewHeight);
    setcar(cdr(Node), newHeightNode);
}

inline
NODE *
AvlGetValue(
    const NODE *  AvlNode
    )
{
    return getobject(cdr(AvlNode));
}

inline
void
AvlSetValue(
    NODE * AvlNode,
    NODE * NewValue
    )
{
    setobject(cdr(AvlNode), NewValue);
}

inline
bool
AvlInvariant(
    const NODE * AvlNode
    )
{
    NODE * rightNode = AvlGetRight(AvlNode);
    NODE * leftNode  = AvlGetLeft(AvlNode);

    int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
    int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;

    int balance = leftHeight - rightHeight;
    if (balance < -1)
    {
        return false;
    }

    if (1 < rightHeight)
    {
        return false;
    }

    return true;
}

// Returns the NODE associated with SearchKey.
// Sets ParentNode to the location above where the node is located.
// If the return value is NULL, then ParentNode is the parent of where
// the node should be inserted.
// 
// IsLeftSide is set to true if the SearchKey is on the left side of
// ParentNode.  IsLeftNode is set to false if SearchKey is on the
// right side.
static
NODE *
AvlTreeFindInsertionPoint(
    NODE *  AvlNode,
    int (*CompareFunction) (NODE *, NODE*),
    NODE *  SearchKey,
    NODE ** ParentNode,
    bool *  IsLeftSide
    )
{
    *ParentNode = NULL;
    *IsLeftSide = false;

    while (AvlNode != NIL)
    {
        NODE * nodeKey = AvlGetKey(AvlNode);
        int compareValue = CompareFunction(SearchKey, nodeKey);
        if (compareValue == 0)
        {
            // Found it
            return AvlNode;
        }
        else if (compareValue < 0)
        {
            // Search down the left side
            *IsLeftSide = true;
            *ParentNode = AvlNode;
            AvlNode = AvlGetLeft(AvlNode);
        }
        else
        {
            // Search down the right side
            *IsLeftSide = false;
            *ParentNode = AvlNode;
            AvlNode = AvlGetRight(AvlNode);
        }
    }

    return AvlNode;
}

// Returns the node associated with SearchKey
NODE *
AvlTreeSearch(
    NODE * AvlNode,
    int (*CompareFunction) (NODE *, NODE*),
    NODE * SearchKey
    )
{
    bool isLeft;
    NODE * parentNode;

    NODE * node = AvlTreeFindInsertionPoint(
        AvlNode,
        CompareFunction,
        SearchKey,
        &parentNode,
        &isLeft);
    if (node == NULL)
    {
        // No such key exists in the tree.
        return NULL;
    }

    // Return the value for SearchKey.
    return AvlGetValue(node);
}


// Inserts Value into a tree.
// If a value already exists for Key, it is replaced.
// Returns the new root node.
NODE *
AvlTreeInsert(
    NODE * AvlNode,
    int (*CompareFunction) (NODE *, NODE*),
    NODE * Key,
    NODE * Value
    )
{
    // Special case for a inserting into an empty tree.
    // This shouldn't be necessary, but the way we set
    // left and right nodes (without double pointer)
    // make it necessary.
    if (AvlNode == NULL)
    {
        return AvlCreateNode(Key, Value);
    }

    NODE * currentNode = AvlNode;
    for (;;)
    {
        NODE * nodeKey = AvlGetKey(currentNode);
        int compareValue = CompareFunction(Key, nodeKey);
        if (compareValue == 0)
        {
            // Found it. Replace the existing Value.
            AvlSetValue(currentNode, Value);

            // TODO: rebalance the tree
            return AvlNode;
        } 
        else if (compareValue < 0) 
        {
            // This value belongs down the left side
            NODE * leftNode = AvlGetLeft(currentNode);
            if (leftNode == NIL)
            {
                // We found where the value belongs
                NODE * newNode = AvlCreateNode(Key, Value);
                AvlSetLeft(currentNode, newNode);

                // TODO: rebalance the tree
                return AvlNode;
            }

            // keep looking
            currentNode = leftNode;
        }
        else
        {
            // This value belongs down the right side
            NODE * rightNode = AvlGetRight(currentNode);
            if (rightNode == NIL)
            {
                // We found where the value belongs
                NODE * newNode = AvlCreateNode(Key, Value);
                AvlSetRight(currentNode, newNode);

                // TODO: rebalance the tree
                return AvlNode;
            }

            // keep looking
            currentNode = rightNode;
        }
    }
}


// Deletes a value from the tree.
// If a value already exists for Key, it is replaced.
// returns the new root node
NODE *
AvlTreeDelete(
    NODE * AvlNode,
    int (*CompareFunction) (NODE *, NODE*),
    NODE * Key
    )
{
    NODE * parentNode = NULL;
    bool   wentLeft   = false;

    NODE * searchNode = AvlNode;
    while (searchNode != NULL)
    {
        NODE * nodeKey = AvlGetKey(searchNode);
        int compareValue = CompareFunction(Key, nodeKey);
        if (compareValue == 0)
        {
            // Found it
            NODE * leftNode  = AvlGetLeft(searchNode);
            NODE * rightNode = AvlGetRight(searchNode);

            if (leftNode == NIL)
            {
                // Since there is no left node, the right node
                // can take the place of the deleted node.

                if (parentNode == NULL)
                {
                    // We are deleting the root node.
                    return rightNode;
                }

                if (wentLeft)
                {
                    AvlSetLeft(parentNode, rightNode);
                }
                else
                {
                    AvlSetRight(parentNode, rightNode);
                }

                // TODO: rebalance the tree
                return AvlNode;
            }
            else if (rightNode == NIL)
            {
                if (parentNode == NULL)
                {
                    // We are deleting the root node.
                    return leftNode;
                }

                // The left node can take the place of this node
                if (wentLeft)
                {
                    AvlSetLeft(parentNode, leftNode);
                }
                else
                {
                    AvlSetRight(parentNode, leftNode);
                }


                // TODO: rebalance the tree
                return AvlNode;
            }
            else
            {
                NODE * rightNodeKey = AvlGetKey(rightNode);

                // This node has two childern.
                // Only one of these can be replace this node.
                // The other node must be moved to the correct
                // location (as an insert)
                if (parentNode == NULL)
                {
                    // We will replace the top node with whatever is to the left of it.

                    // Find where the right node goes in the new tree.
                    bool setRightNodeOnLeftOfParent;
                    NODE * rightParentNode;
                    NODE * node = AvlTreeFindInsertionPoint(
                        leftNode,
                        CompareFunction,
                        rightNodeKey,
                        &rightParentNode,
                        &setRightNodeOnLeftOfParent);

                    // Because we orphanded the right side, it's values
                    // should not be found in the tree.
                    assert(node == NULL);

                    if (setRightNodeOnLeftOfParent)
                    {
                        assert(AvlGetLeft(rightParentNode) == NULL);
                        AvlSetLeft(rightParentNode, rightNode);
                    }
                    else
                    {
                        assert(AvlGetRight(rightParentNode) == NULL);
                        AvlSetRight(rightParentNode, rightNode);
                    }

                    // Use the left node as the new root.
                    return leftNode;
                }

                // Reference right node because setting the left node
                // into the parent would otherise orphan it and leave
                // it with no refrences.
                ref(rightNode);

                // Replace this node with the left node
                if (wentLeft)
                {
                    AvlSetLeft(parentNode, leftNode);
                }
                else
                {
                    AvlSetRight(parentNode, leftNode);
                }

                // Find where the right node goes
                bool setRightNodeOnLeftOfParent;
                NODE * rightParentNode;
                NODE * node = AvlTreeFindInsertionPoint(
                    AvlNode,
                    CompareFunction,
                    rightNodeKey,
                    &rightParentNode,
                    &setRightNodeOnLeftOfParent);

                // Because we orphanded the right side, it's values
                // should not be found in the tree.
                assert(node == NULL);

                if (setRightNodeOnLeftOfParent)
                {
                    assert(AvlGetLeft(rightParentNode) == NULL);
                    AvlSetLeft(rightParentNode, rightNode);
                }
                else
                {
                    assert(AvlGetRight(rightParentNode) == NULL);
                    AvlSetRight(rightParentNode, rightNode);
                }

                // Remove the reference we added above.
                deref(rightNode);

                // TODO: rebalance the tree
                return AvlNode;
            }
        }
        else if (compareValue < 0)
        {
            // Search down the left side
            parentNode = searchNode;
            wentLeft   = true;
            searchNode = AvlGetLeft(searchNode);
        }
        else
        {
            // Search down the right side
            parentNode = searchNode;
            wentLeft   = false;
            searchNode = AvlGetRight(searchNode);
        }
    }

    // The node was not in the tree.
    return AvlNode;
}

static
void
AvlTreeFlatten(
    NODE *            AvlNode,
    CAppendableList & AccumulatedList
    )
{
    // Iterate down the left side of the tree
    // and recurse down the right side.
    // We intentionally don't do an in-order walk
    // so that the caller doesn't expect any particular
    // order.
    while (AvlNode != NIL)
    {
        NODE * key   = AvlGetKey(AvlNode);
        AccumulatedList.AppendElement(key);

        NODE * value = AvlGetValue(AvlNode);
        AccumulatedList.AppendElement(value);

        // recurse down the right side
        NODE * rightNode = AvlGetRight(AvlNode);
        AvlTreeFlatten(rightNode, AccumulatedList);

        // Iterate down the left side
        AvlNode = AvlGetLeft(AvlNode);
    }
}

// Gets a list of name-value pairs from the tree.
NODE *
AvlTreeFlatten(
    NODE * AvlNode
    )
{
    CAppendableList flatList;

    AvlTreeFlatten(AvlNode, flatList);

    return flatList.GetList();
}
