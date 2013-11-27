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
#include <algorithm>

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
    NODE * height     = make_intnode(1);

    setcar(firstNode, NIL);
    setcdr(firstNode, secondNode);
    setobject(firstNode, Key);

    setcar(secondNode, height);
    setcdr(secondNode, NIL);
    setobject(secondNode, Value);

    return firstNode;
}

inline
NODE **
AvlGetLeftPtr(
    NODE * AvlNode
    )
{
    assert(AvlNode != NULL);
    return &AvlNode->nunion.ncons.ncar;
}

inline
NODE *
AvlGetLeft(
    NODE * AvlNode
    )
{
    assert(AvlNode != NULL);
    return *AvlGetLeftPtr(AvlNode);
}

inline
NODE **
AvlGetRightPtr(
    NODE * AvlNode
    )
{
    return &cdr(AvlNode)->nunion.ncons.ncdr;
}

inline
NODE *
AvlGetRight(
    NODE *  AvlNode
    )
{
    assert(AvlNode != NULL);
    return *AvlGetRightPtr(AvlNode);
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
NODE *
AvlGetKey(
    const NODE * AvlNode
    )
{
    return getobject(AvlNode);
}

inline
NODE *
AvlGetValue(
    const NODE *  AvlNode
    )
{
    return getobject(cdr(AvlNode));
}

#ifdef NDEBUG
#  define ASSERT_AVLNODE_INVARIANT(NODE, COMPAREFUNC)
#else
#  define ASSERT_AVLNODE_INVARIANT(NODE, COMPAREFUNC) CAvlNodeInvariant::AssertInvariant(NODE, COMPAREFUNC)

class CAvlNodeInvariant
{
public:
    CAvlNodeInvariant(
        NODE                  * AvlNode,
        NODE_COMPARE_FUNCTION   CompareFunction
        )
        : m_AvlNode(AvlNode),
          m_CompareFunction(CompareFunction)
    {
        AssertInvariant();
    }

    ~CAvlNodeInvariant()
    {
        AssertInvariant();
    }

    void AssertInvariant() const
    {
        AssertInvariant(m_AvlNode, m_CompareFunction);
    }

    static
    void
    AssertInvariant(
        NODE                  * AvlNode, 
        NODE_COMPARE_FUNCTION   CompareFunction
        )
    {
        assert(AvlNode != NULL);

        NODE * key       = AvlGetKey(AvlNode);
        NODE * rightNode = AvlGetRight(AvlNode);
        NODE * leftNode  = AvlGetLeft(AvlNode);

        int rightHeight;
        if (rightNode != NULL)
        {
            // This node should compare less than the right node.
            NODE * rightKey = AvlGetKey(rightNode);
            assert(CompareFunction(key, rightKey) < 0);
            assert(CompareFunction(rightKey, key) > 0);

            rightHeight = AvlGetHeight(rightNode);
        }
        else
        {
            rightHeight = 0;
        }

        int leftHeight;
        if (leftNode != NULL)
        {
            // This node should compare greater than the left node.
            NODE * leftKey = AvlGetKey(leftNode);
            assert(CompareFunction(key, leftKey) > 0);
            assert(CompareFunction(leftKey, key) < 0);

            leftHeight = AvlGetHeight(leftNode);
        }
        else
        {
            leftHeight = 0;
        }

        int calculatedHeight = std::max(rightHeight, leftHeight) + 1;
        int actualHeight = AvlGetHeight(AvlNode);
        assert(calculatedHeight == actualHeight);

        // An AVL node may have a balance of 0, 1, or -1.
        // TODO: Once rebalancing logic is implemented.
        //int balance = leftHeight - rightHeight;
        //assert(-1 <= balance);
        //assert(balance <= 1);
    }

private:
    NODE                  * m_AvlNode;
    NODE_COMPARE_FUNCTION   m_CompareFunction;
};

#endif


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
void
AvlSetLeft(
    NODE * AvlNode,
    NODE * NewLeftNode
    )
{
    // Update the height
    NODE * rightNode = AvlGetRight(AvlNode);
    int rightHeight = (rightNode == NULL) ? 0 : AvlGetHeight(rightNode);
    if (NewLeftNode == NULL)
    {
        // We're removing the left node, so the height
        // is based on the right node.
        AvlSetHeight(AvlNode, rightHeight + 1);
    }
    else
    {
        // We're replacing the left node.
        int leftHeight = AvlGetHeight(NewLeftNode);
        if (rightHeight < leftHeight)
        {
            AvlSetHeight(AvlNode, leftHeight + 1);
        }
    }

    // Set the left node
    setcar(AvlNode, NewLeftNode);
}

inline
void
AvlSetRight(
    NODE * AvlNode,
    NODE * NewRightNode
    )
{
    // Update the height
    NODE * leftNode = AvlGetLeft(AvlNode);
    int leftHeight = (leftNode == NULL) ? 0 : AvlGetHeight(leftNode);
    if (NewRightNode == NULL)
    {
        // We're removing the right node, so the height
        // is based on the left node.
        AvlSetHeight(AvlNode, leftHeight + 1);
    }
    else
    {
        // We're replacing the right node.
        int rightHeight = AvlGetHeight(NewRightNode);
        if (leftHeight < rightHeight)
        {
            AvlSetHeight(AvlNode, rightHeight + 1);
        }
    }

    // Set the right node
    setcdr(cdr(AvlNode), NewRightNode);
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
void
AvlSetValue(
    NODE * AvlNode,
    NODE * NewValue
    )
{
    setobject(cdr(AvlNode), NewValue);
}


// Returns the node associated with SearchKey
NODE *
AvlTreeSearch(
    NODE                  * AvlNode,
    NODE_COMPARE_FUNCTION   CompareFunction,
    NODE                  * SearchKey
    )
{
    while (AvlNode != NIL)
    {
        ASSERT_AVLNODE_INVARIANT(AvlNode, CompareFunction);

        NODE * nodeKey = AvlGetKey(AvlNode);
        int compareValue = CompareFunction(SearchKey, nodeKey);
        if (compareValue == 0)
        {
            // Found it
            return AvlGetValue(AvlNode);
        }
        else if (compareValue < 0)
        {
            // Search down the left side
            AvlNode = AvlGetLeft(AvlNode);
        }
        else
        {
            // Search down the right side
            AvlNode = AvlGetRight(AvlNode);
        }
    }

    // No such key exists in the tree.
    return NIL;
}

static
void
AvlTreeInsertRecursive(
    NODE                  * AvlNode,
    NODE_COMPARE_FUNCTION   CompareFunction,
    NODE                  * SearchKey,
    NODE                  * Value
    )
{
    ASSERT_AVLNODE_INVARIANT(AvlNode, CompareFunction);

    assert(AvlNode != NIL);

    NODE * nodeKey = AvlGetKey(AvlNode);
    int compareValue = CompareFunction(SearchKey, nodeKey);
    if (compareValue == 0)
    {
        // Found it. Replace the existing Value.
        AvlSetValue(AvlNode, Value);

        // TODO: we don't need to rebalance the tree.
        return;
    } 

    NODE * leftNode  = AvlGetLeft(AvlNode);
    NODE * rightNode = AvlGetRight(AvlNode);
    NODE * nextNode;

    if (compareValue < 0) 
    {
        // This value belongs down the left side
        if (leftNode == NIL)
        {
            // We found where the value belongs
            NODE * newNode = AvlCreateNode(SearchKey, Value);
            AvlSetLeft(AvlNode, newNode);
            return;
        }

        // keep looking
        nextNode = leftNode;
    }
    else
    {
        // This value belongs down the right side
        if (rightNode == NIL)
        {
            // We found where the value belongs
            NODE * newNode = AvlCreateNode(SearchKey, Value);
            AvlSetRight(AvlNode, newNode);
            return;
        }

        // keep looking
        nextNode = rightNode;
    }

    // Keep looking
    AvlTreeInsertRecursive(
        nextNode,
        CompareFunction,
        SearchKey,
        Value);

    // TODO: rebalance the tree

    // Update the height of this branch.
    // TODO: take advantage of whether we inserted on the left or right.
    int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;
    int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
    int newHeight   = std::max(leftHeight, rightHeight) + 1;
    AvlSetHeight(AvlNode, newHeight);
}

// Inserts Value into a tree.
// If a value already exists for Key, it is replaced.
// Returns the new root node.
NODE *
AvlTreeInsert(
    NODE                  * AvlNode,
    NODE_COMPARE_FUNCTION   CompareFunction,
    NODE                  * Key,
    NODE                  * Value
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

    AvlTreeInsertRecursive(
        AvlNode,
        CompareFunction,
        Key,
        Value);

    // TODO: rebalance the tree
    return AvlNode;
}

static
void
AvlTreeInsertNode(
    NODE                  *  AvlNode,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  SearchKey,
    NODE                  *  NodeToInsert
    )
{
    assert(AvlNode != NIL);

    NODE * leftNode  = AvlGetLeft(AvlNode);
    NODE * rightNode = AvlGetRight(AvlNode);
    NODE * nodeKey   = AvlGetKey(AvlNode);
    int compareValue = CompareFunction(SearchKey, nodeKey);

    // This is only called for nodes that don't exist in the tree.
    assert(compareValue != 0);

    NODE * nextNode;
    if (compareValue < 0) 
    {
        // This value belongs down the left side
        if (leftNode == NIL)
        {
            // We found where the value belongs
            AvlSetLeft(AvlNode, NodeToInsert);
            return;
        }

        // keep looking
        nextNode = leftNode;
    }
    else
    {
        // This value belongs down the right side
        if (rightNode == NIL)
        {
            // We found where the value belongs
            AvlSetRight(AvlNode, NodeToInsert);
            return;
        }

        // keep looking
        nextNode = rightNode;
    }

    AvlTreeInsertNode(
        nextNode,
        CompareFunction,
        SearchKey,
        NodeToInsert);

    // Update the height of this branch.
    // TODO: take advantage of whether we inserted on the left or right.
    int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;
    int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
    int newHeight   = std::max(leftHeight, rightHeight) + 1;
    AvlSetHeight(AvlNode, newHeight);

    ASSERT_AVLNODE_INVARIANT(AvlNode, CompareFunction);
}

// Deletes a value from the tree.
// Returns the new root node
//
// Parameters:
// RootNode        - A pointer to the root node of the tree.
//                   If the root nodes of the tree changes, this will be
//                   updated to point to the new root node.
// CurrentNode     - A pointer to the node we're currently on, as we descend
//                   down the tree.
// CompareFunction - the tree's comparison function.
// Key             - the key of the node that we want to delete.
static
void
AvlTreeDeleteRecursive(
    NODE                  ** RootNodePtr,
    NODE                  ** CurrentNodePtr,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  Key
    )
{
    assert(RootNodePtr != NULL);
    assert(CurrentNodePtr != NULL);

    if (*CurrentNodePtr == NIL)
    {
        // We reached the bottom of the tree, so there's no
        // value with the given key.
        return;
    }

    NODE * currentNode = *CurrentNodePtr;
    ASSERT_AVLNODE_INVARIANT(currentNode, CompareFunction);

    NODE * nodeKey = AvlGetKey(currentNode);
    int compareValue = CompareFunction(Key, nodeKey);
    if (compareValue == 0)
    {
        // Found it
        NODE * leftNode  = AvlGetLeft(currentNode);
        NODE * rightNode = AvlGetRight(currentNode);

        if (leftNode == NIL)
        {
            // Since there is no left node, the right node
            // can take the place of the deleted node.
            setnode(CurrentNodePtr, rightNode);

            // TODO: rebalance the tree
        }
        else if (rightNode == NIL)
        {
            // Since there is no right node, the left node
            // can take the place of the deleted node.
            setnode(CurrentNodePtr, leftNode);

            // TODO: rebalance the tree
        }
        else
        {
            NODE * rightNodeKey = AvlGetKey(rightNode);

            // This node has two childern.
            // Only one of these can be replace this node.
            // The other node must be moved to the correct
            // location (as an insert)

            // Reference right node because setting the left node
            // into the parent would otherwise orphan it and leave
            // it with no refrences.
            ref(rightNode);

            // Replace this node with the left node
            setnode(CurrentNodePtr, leftNode);

            // Find where the right node goes in the new tree
            AvlTreeInsertNode(
                *RootNodePtr,
                CompareFunction,
                rightNodeKey,
                rightNode);

            // Remove the reference we added above.
            deref(rightNode);

            // TODO: rebalance the tree
        }

        return;
    }

    NODE ** nextNodePtr;
    if (compareValue < 0)
    {
        // Search down the left side
        nextNodePtr = AvlGetLeftPtr(currentNode);
    }
    else
    {
        // Search down the right side
        nextNodePtr = AvlGetRightPtr(currentNode);
    }

    AvlTreeDeleteRecursive(
        RootNodePtr,
        nextNodePtr,
        CompareFunction,
        Key);

    // TODO: rebalance the tree

    // Update the height of this branch.
    // TODO: take advantage of whether we inserted on the left or right.
    NODE * leftNode  = AvlGetLeft(currentNode);
    NODE * rightNode = AvlGetRight(currentNode);
    int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;
    int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
    int newHeight   = std::max(leftHeight, rightHeight) + 1;
    AvlSetHeight(currentNode, newHeight);

    ASSERT_AVLNODE_INVARIANT(currentNode, CompareFunction);
}

// Deletes a value from the tree.
// If a value already exists for Key, it is replaced.
void
AvlTreeDelete(
    NODE                  ** AvlNode,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  Key
    )
{
    AvlTreeDeleteRecursive(AvlNode, AvlNode, CompareFunction, Key);
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
