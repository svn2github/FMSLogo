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
        if (AvlNode != NIL)
        {
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
            int balance = leftHeight - rightHeight;
            assert(-1 <= balance);
            assert(balance <= 1);
        }
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

/// Return LEFT - RIGHT
inline
int
AvlGetBalance(
    NODE * AvlNode
    )
{
    if (AvlNode == NULL)
    {
        return 0;
    }
    else
    {
        NODE * leftNode  = AvlGetLeft(AvlNode);
        NODE * rightNode = AvlGetRight(AvlNode);
        int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;
        int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
        return leftHeight - rightHeight;
    }
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


// Update the height of this node based on the heights of its children.
// I'll figure out a more elengant way to do this in the future,
// but for, brute forcing the correction of the height helps me
// write the balancing logic.
inline
void
HackFixHeight(
    NODE * AvlNode
    )
{
    if (AvlNode != NULL)
    {
        NODE * leftNode  = AvlGetLeft(AvlNode);
        NODE * rightNode = AvlGetRight(AvlNode);
        int leftHeight  = leftNode  ? AvlGetHeight(leftNode)  : 0;
        int rightHeight = rightNode ? AvlGetHeight(rightNode) : 0;
        int newHeight   = std::max(leftHeight, rightHeight) + 1;
        AvlSetHeight(AvlNode, newHeight);
    }
}

// Performs a right rotation, which is best understood pictorially.
//
//           +--------------------------+
//           |     4             2      |
//           |    / \           / \     |
//           |   2   5   --->  1   4    |
//           |  / \               / \   |
//           | 1   3             3   5  |
//           |+-------------------------+
//
// This helps balance a tree, while maintaining the order requirement
// of a search tree.
static
void
AvlRotateRight(
    NODE ** AvlNodePtr
    )
{
    assert(AvlNodePtr != NULL);

    NODE *  oldTop  = *AvlNodePtr;                 // node #4
    NODE *  oldLeft = AvlGetLeft(oldTop);          // node #2
    NODE *  oldLeftRight  = AvlGetRight(oldLeft);  // node #3
    NODE ** oldTopLeftPtr = AvlGetLeftPtr(oldTop); // where node #3 belongs

    ref(oldTop); // keep the node alive for this rotation

    setnode(AvlNodePtr,    oldLeft);      // move #2 to the top
    setnode(oldTopLeftPtr, oldLeftRight); // move #3 under #4 (where #2 was)
    AvlSetRight(oldLeft,   oldTop);       // move #4 under #2 (where #3 was)

    deref(oldTop);

    // TODO: update the heights in the logic above.
    HackFixHeight(oldTop);   // fix the height of #4
    HackFixHeight(oldLeft);  // fix the height of #2
}

// Performs a left rotation, which is best understood pictorially.
//
//           +--------------------------+
//           |    2               4     |
//           |   / \             / \    |
//           |  1   4    --->   2   5   |
//           |     / \         / \      |
//           |    3   5       1   3     |
//           +--------------------------+
//
// This helps balance a tree, while maintaining the order requirement
// of a search tree.
static
void
AvlRotateLeft(
    NODE ** AvlNodePtr
    )
{
    assert(AvlNodePtr != NULL);

    NODE *  oldTop   = *AvlNodePtr;                  // node #2
    NODE *  oldRight = AvlGetRight(oldTop);          // node #4
    NODE *  oldRightLeft   = AvlGetLeft(oldRight);   // node #3
    NODE ** oldTopRightPtr = AvlGetRightPtr(oldTop); // where node #3 belongs

    ref(oldTop); // keep the node alive for this rotation

    setnode(AvlNodePtr,     oldRight);     // move #4 to the top
    setnode(oldTopRightPtr, oldRightLeft); // move #3 under #2 (where #4 was)
    AvlSetLeft(oldRight,    oldTop);       // move #2 under #4 (where #3 was)

    deref(oldTop);

    // TODO: update the heights in the logic above.
    HackFixHeight(oldTop);    // fix the height of #2
    HackFixHeight(oldRight);  // fix the height of #4
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

// Inserts Value into a tree.
// If a value already exists for Key, it is replaced.
//
// Parameters:
// RootNodePtr     - A pointer to the root node.
//                   This may be updated to point to a different node
//                   depending on if the tree needs to be rebalanced.
// CompareFunction - A function that defines a strict ordering for keys.
// Key             - The key of the node to insert.
// Value           - The value of the node to insert.
//
void
AvlTreeInsert(
    NODE                  ** RootNodePtr,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  Key,
    NODE                  *  Value
    )
{
    assert(RootNodePtr != NULL);
    ASSERT_AVLNODE_INVARIANT(*RootNodePtr, CompareFunction);

    NODE * currentNode = *RootNodePtr;
    if (currentNode == NIL)
    {
        // We've reached the bottom of the tree without finding
        // a matching node.  Insert a new node here.
        NODE * newNode = AvlCreateNode(Key, Value);
        setnode(RootNodePtr, newNode);
        ASSERT_AVLNODE_INVARIANT(*RootNodePtr, CompareFunction);
        return;
    }


    NODE * nodeKey = AvlGetKey(currentNode);
    int compareValue = CompareFunction(Key, nodeKey);
    if (compareValue == 0)
    {
        // Found it. Replace the existing Value.
        AvlSetValue(currentNode, Value);
        ASSERT_AVLNODE_INVARIANT(*RootNodePtr, CompareFunction);
        return;
    } 

    if (compareValue < 0)
    {
        // Search down the left side
        NODE ** leftNodePtr = AvlGetLeftPtr(currentNode);
        AvlTreeInsert(leftNodePtr, CompareFunction, Key, Value);

        // Rebalance the tree, if necessary.
        // If we inserted on the left side, then
        // the only possible imbalance is a skew to the left
        // (balance of 2).
        int currentBalance = AvlGetBalance(currentNode);
        if (1 < currentBalance)
        {
            // The current node is now out of balance.
            int leftBalance = AvlGetBalance(*leftNodePtr);
            if (leftBalance < 0)
            {
                // The left tree is skewed to the right.
                // Rotate it left to balance it.
                AvlRotateLeft(leftNodePtr);
            }

            // Now balance the current node.
            AvlRotateRight(RootNodePtr);
        }
        else
        {
            HackFixHeight(currentNode);
        }
    }
    else
    {
        // Search down the right side
        NODE ** rightNodePtr = AvlGetRightPtr(currentNode);
        AvlTreeInsert(rightNodePtr, CompareFunction, Key, Value);

        // Rebalance the tree, if necessary.
        // If we inserted on the right side, then
        // the only possible imbalance is a skew to the right
        // (balance of -2).
        int currentBalance = AvlGetBalance(currentNode);
        if (currentBalance < -1)
        {
            // The current node is now out of balance.
            int rightBalance = AvlGetBalance(*rightNodePtr);
            if (0 < rightBalance)
            {
                // The right tree is skewed to the left.
                // Rotate it right to balance it.
                AvlRotateRight(rightNodePtr);
            }

            // Now balance the current node.
            AvlRotateLeft(RootNodePtr);
        }
        else
        {
            HackFixHeight(currentNode);
        }
    }

    ASSERT_AVLNODE_INVARIANT(*RootNodePtr, CompareFunction);
}

// A sub-phase of AvlTreeDelete() that is run when the node to delete has two
// childen.  This routine is called on the right child, finds the smallest
// key'd node, puts that key/value pair into the node to delete, then deletes
// the smallest key'd node (rebalancing, as necessary).
static
void
AvlTreeDeleteWithValueExchange(
    NODE                  ** CurrentNodePtr,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  AvlNodeToDelete
    )
{
    assert(CurrentNodePtr != NULL);
    ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);

    NODE * currentNode = *CurrentNodePtr;
    NODE ** nextNodePtr = AvlGetLeftPtr(currentNode);
    if (*nextNodePtr == NIL)
    {
        // There is no left child, so *SearchNode is the node we've been
        // looking for.  Put its values into AvlNodeToSwap, which effectively
        // deletes the key/value pair in AvlNodeToDelete.
        AvlSetKey(AvlNodeToDelete,   AvlGetKey(currentNode));
        AvlSetValue(AvlNodeToDelete, AvlGetValue(currentNode));

        // Now that searchNode's key/value pair are elsewhere in
        // the tree, we need to remove the node.
        // Since we know that its left child is NIL, we can
        // remove the node, by replacing it with its right child.
        setnode(CurrentNodePtr, AvlGetRight(currentNode));
        ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);
        return;
    }

    // Keep looking (recursively)
    AvlTreeDeleteWithValueExchange(nextNodePtr, CompareFunction, AvlNodeToDelete);

    // Rebalance the tree, if necessary.
    // Since we deleted from the left side, the
    // only possible imbalance is a skew to the right
    // (balance of -2).
    int currentBalance = AvlGetBalance(currentNode);
    if (currentBalance < -1)
    {
        // The current node is now out of balance.
        NODE ** rightNodePtr = AvlGetRightPtr(currentNode);
        // TODO: does rightNodePtr==nextNodePtr?
        int rightBalance = AvlGetBalance(*rightNodePtr);
        if (0 < rightBalance)
        {
            // The right tree is skewed to the left.
            // Rotate it right to balance it.
            AvlRotateRight(rightNodePtr);
        }

        // Now balance the current node.
        AvlRotateLeft(CurrentNodePtr);
    }
    else
    {
        // If no rebalancing is necessary, then we only need to update the height.
        // TODO: take advantage of the fact that we deleted a node from the left side.
        HackFixHeight(currentNode);
    }

    ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);
}

// Deletes a value from the tree, updating the CurrentNodePtr to point to the
// new root, if necessary.
//
// Parameters:
// CurrentNodePtr  - A pointer to the node we're currently on, as we descend
//                   down the tree.  If deleting the node requires restructuring
//                   the tree, then this will be updated to point to a new node.
// CompareFunction - the tree's comparison function.
// Key             - the key of the node that we want to delete.
static
void
AvlTreeDeleteRecursive(
    NODE                  ** CurrentNodePtr,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  Key
    )
{
    ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);
    assert(CurrentNodePtr != NULL);

    if (*CurrentNodePtr == NIL)
    {
        // We reached the bottom of the tree, so there's no
        // value with the given key.
        return;
    }

    NODE * currentNode = *CurrentNodePtr;
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
        }
        else if (rightNode == NIL)
        {
            // Since there is no right node, the left node
            // can take the place of the deleted node.
            setnode(CurrentNodePtr, leftNode);
        }
        else
        {
            // This node has two childern, so we cannot simply
            // replace it with one of its children.
            //
            // Instead, we swap it with a node that has the
            // smallest key down the right (larger) side.
            // This will preserve the "search tree" property,
            // as everything to the left will still be smaller
            // and everything to the right will still be larger.
            //
            // The node with the smallest key down the right side,
            // by definition, cannot have a smaller key, so it's
            // guaranteed not to have a right child, which means
            // that it will be easier to delete.
            NODE ** largerChildPtr = AvlGetRightPtr(currentNode);
            AvlTreeDeleteWithValueExchange(largerChildPtr, CompareFunction, currentNode);

            // Rebalance the tree, if necessary.
            // If we deleted from the right side, then
            // the only possible imbalance is a skew to the left
            // (balance of 2).
            int currentBalance = AvlGetBalance(currentNode);
            if (1 < currentBalance)
            {
                // The current node is now out of balance.
                NODE ** leftNodePtr = AvlGetLeftPtr(currentNode);
                int leftBalance = AvlGetBalance(*leftNodePtr);
                if (leftBalance < 0)
                {
                    // The left tree is skewed to the right.
                    // Rotate it left to balance it.
                    AvlRotateLeft(leftNodePtr);
                }

                // Now balance the current node.
                AvlRotateRight(CurrentNodePtr);
            }
            else
            {
                HackFixHeight(currentNode);
            }
        }
        ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);
        return;
    }

    NODE ** nextNodePtr;
    if (compareValue < 0)
    {
        // Search down the left side
        nextNodePtr = AvlGetLeftPtr(currentNode);
        AvlTreeDeleteRecursive(nextNodePtr, CompareFunction, Key);

        // Rebalance the tree, if necessary.
        // If we deleted from the left side, then
        // the only possible imbalance is a skew to the right
        // (balance of -2).
        int currentBalance = AvlGetBalance(currentNode);
        if (currentBalance < -1)
        {
            // The current node is now out of balance.
            NODE ** rightNodePtr = AvlGetRightPtr(currentNode);
            int rightBalance = AvlGetBalance(*rightNodePtr);
            if (0 < rightBalance)
            {
                // The right tree is skewed to the left.
                // Rotate it right to balance it.
                AvlRotateRight(rightNodePtr);
            }

            // Now balance the current node.
            AvlRotateLeft(CurrentNodePtr);
        }
        else
        {
            HackFixHeight(currentNode);
        }
    }
    else
    {
        // Search down the right side
        nextNodePtr = AvlGetRightPtr(currentNode);
        AvlTreeDeleteRecursive(nextNodePtr, CompareFunction, Key);

        // Rebalance the tree, if necessary.
        // If we deleted from the right side, then
        // the only possible imbalance is a skew to the left
        // (balance of 2).
        int currentBalance = AvlGetBalance(currentNode);
        if (1 < currentBalance)
        {
            // The current node is now out of balance.
            NODE ** leftNodePtr = AvlGetLeftPtr(currentNode);
            int leftBalance = AvlGetBalance(*leftNodePtr);
            if (leftBalance < 0)
            {
                // The left tree is skewed to the right.
                // Rotate it left to balance it.
                AvlRotateLeft(leftNodePtr);
            }

            // Now balance the current node.
            AvlRotateRight(CurrentNodePtr);
        }
        else
        {
            HackFixHeight(currentNode);
        }
    }

    ASSERT_AVLNODE_INVARIANT(*CurrentNodePtr, CompareFunction);
}

// Deletes a value from the tree.
// If a value already exists for Key, it is replaced.
void
AvlTreeDelete(
    NODE                  ** RootNodePtr,
    NODE_COMPARE_FUNCTION    CompareFunction,
    NODE                  *  Key
    )
{
    AvlTreeDeleteRecursive(RootNodePtr, CompareFunction, Key);
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
