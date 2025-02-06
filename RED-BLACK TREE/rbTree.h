#ifndef RBT_H
#define RBT_H

enum nodeColor {
  RED,
  BLACK
};

struct rbNode {
  int data, color;
  struct rbNode *link[2];
};

struct rbNode * rbtCreateNode(int data);
struct rbNode * rbtInsert(struct rbNode * root, int data);
struct rbNode *  rbtDelete(struct rbNode * root, int data);
void rbtDisplay(struct rbNode *node);

#endif
