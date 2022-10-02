# include "../ADT/List.h"
# include "../ADT/Tree.h"
# include "Door.h"

void pathFinding() {
    Stack<TreeNode<Door>>* currentPath = new List<TreeNode<Door>>;
    List<TreeNode<Door>>* clearedOptions = new List<TreeNode<Door>>;

}

// [0, 3, 6, 10, 13, 15] current

// [0, 3, 4, 6, 7, 10, 11, 12, 13, 14, 15, 16, 17]

// Cuando currentPath no tiene mas opciones disponibles
// i.e children == empty list, entonces se agrega dicho
// nodo/posicion a cleared options y se devuelve (pop)
// a la posicion anterior de ser necesario. Para revisar
// que opciones tiene de una puerta a otra, debe hallar
// por lo menos un child node que no este en cleared