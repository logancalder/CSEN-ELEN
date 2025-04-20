datatype 'a tree = empty | node of 'a tree * 'a * 'a tree;

exception Empty;

(* Check if member in tree *)
fun member empty _ = false
    | member (node(l,x,r)) y =
        if y < x then member l y
        else if y > x then member r y
        else true;

(* Insert into BST *)
fun insert empty y = node(empty, y, empty)
    | insert (node(l,x,r)) y = 
        if y < x then node(insert l y, x, r)
        else if y > x then node(l, x, insert r y)
        else node(l, x, r);

fun inorder empty = []
    | inorder (node(l,x,r)) = inorder l @ x :: inorder r;

(* I hope that this is what you meant when you said raise Empty, had to look it up haha *)
(* Return the maximum out of tree *)
fun maximum empty = raise Empty
  | maximum (node(_, x, empty)) = x
  | maximum (node(_, _, r)) = maximum r;

(* setup smlnj
sml bst.sml *)

    