/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Yaire Aguilar
 * Email:aguilary@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  
  struct bst* tree = malloc(sizeof(struct bst));
  tree->root = NULL;
  return tree;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void free_prop(struct bst_node* node){
  if (node != NULL){
    free_prop(node->left);  //use recurr to free each side
    free_prop(node->right);
    free(node); //free mem allocated for the curr node
  }
}

void bst_free(struct bst* bst) {
  //i dont think im doing this right
  free_prop(bst->root); //calls on the root
  free(bst);  //once done free mem allocated for bst
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */


//my helper function
//should return the number of nodes below the node
//essentially it well count the nodes of each side- cntr+=1
int recur_num(struct bst_node* node){
   if (node == NULL) { // Base case: if the node is NULL, return 0
    return 0;
  }
  int lnum = recur_num(node->left);
  int rnum = recur_num(node->right);
  return (1 + lnum + rnum);
}

int bst_size(struct bst* bst) {
  //have to call a helper function to hel with this
  if (bst == NULL || bst->root == NULL){
    return 0;
  }
  return recur_num(bst->root);
}


/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

//helper 1
struct bst_node* construct(int key, void* value){
  //sec 1
  //first initializing the new node and its properties
  struct bst_node* new_node = malloc(sizeof(struct bst_node));
  //assert(new_node);
  if(new_node !=NULL){
    new_node->key = key;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
  }
  return new_node;
}
//helper 2
struct bst_node* check(struct bst_node* node, int key, void* value){
  //sec2
  //checking on the new node to see if the node itself has other "branches"
  if (node == NULL){
    return construct(key, value);
  }
  //recusrions
  else if (node->key > key){
    node->left = check(node->left, key, value);//gonaa have to make it its properties too
  }
  else {
    node->right = check(node->right, key, value);
  }
  return node;
}

void bst_insert(struct bst* bst, int key, void* value) {
  //basically put new val into a given bst
  //basically three sections to it
  //sec 3
  if(bst != NULL){
    bst->root = check(bst->root, key, value);
  }

}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */


struct bst_node* left_finder(struct bst_node* node){
  while(node != NULL && node->left != NULL)
  {
    node = node->left;
  }

  return node;
}
struct bst_node* st_remover(struct bst_node* parent, struct bst_node* node, int key){
if (node == NULL) {
        return node;
}
if (node->key > key) {
  node->left = st_remover(node, node->left, key);
} 
else if (node->key < key) {
  node->right = st_remover(node, node->right, key);
} 
else {
  if (node->left == NULL) {
    struct bst_node* temp = node->right;
    free(node);
      if (parent != NULL) {
        if (parent->left == node) {
            parent->left = temp;
        } 
        else {
          parent->right = temp;
        }
      }
    return temp;
  } 
  else if (node->right == NULL) {
    struct bst_node* temp = node->left;
    free(node);
    if (parent != NULL) {
      if (parent->left == node) {
        parent->left = temp;
      } 
      else {
        parent->right = temp;
      }
    }
    return temp;
  } 
  else {
            // Find in-order successor
    struct bst_node* temp = left_finder(node->right);
    node->key = temp->key;
    node->right = st_remover(node, node->right, temp->key);
  }
  }
  return node;
}

void bst_remove(struct bst* bst, int key) {
  //remember the one closest to the root of the tree is removed
if (bst != NULL) {
  bst->root = st_remover(NULL, bst->root, key);
}
}



/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* node = bst->root;
  while (node != NULL){
    if (node->key == key){
      return node->value;
    }
    else if (node->key > key){
      node = node->left;
    }
    else node = node->right;
  }
  return node;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
//helper
int measure(struct bst_node* root){
  
    if (root == NULL) {
        return -1;
    }

    int lmax = measure(root->left);
    int rmax = measure(root->right);

    if (lmax > rmax){
        return lmax + 1;
    }
    else {
        return rmax + 1;
    }

}

 int bst_height(struct bst* bst) {
  return measure(bst->root);
 }

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
//helper
int bst_sum(struct bst_node* root, int sum){
  if (root == NULL){
    return 0;
  }
  
  int cntr = sum - root->key; // Subtract the key, not the value
  if (root->left == NULL && root->right == NULL && cntr == 0){
    return 1;
  }
  
  int num = 0;
  if (root->left != NULL){
    num += bst_sum(root->left, cntr); // Pass root->left, not cntr
  }
  if (root->right != NULL){
    num += bst_sum(root->right, cntr); // Pass root->right, not cntr
  }

  return num;
}



int bst_path_sum(struct bst* bst, int sum) {
  return bst_sum(bst->root, sum);

  
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  /*
   * FIXME:
   */
  return 0;
}
