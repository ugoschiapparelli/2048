/**
 *\file testGrid.h
 *\brief Permet de lancer les tests
 */

/**
 *\fn static void waitFor (unsigned int t)
 *\brief Attend pendant t secondes avant de continuer l'execution
 *\param t durée de la pause
 */

static void waitFor (unsigned int t);

/**
 *\fn static void afficherGrid(grid g)
 *\brief Affiche la grille dans le terminal
 *\param g grille à afficher
 */

static void afficherGrid(grid g);

/**
 *\fn void initGrid(grid g)
 *\brief Initialise la grille en remplissant toutes ses cases avec des 0
 *\param g grille
 */

static void initGrid(grid g);

/**
 *\fn bool test_set_tile(grid g)
 *\brief Teste set_tile(grid g, int x, int y, tile t) et get_tile(grid g, int x, int y)
 * On ajoute la valeur i dans la grille et on vérifie que celle-ci a bien été affectée au bon endroit
 *\param g la grille à tester
 *\return true si le test a réussi, false sinon
 */

static bool test_get_set_tile(grid g);

/**
 *\fn bool test_add_tile(grid g)
 *\brief Teste add_tile(grid g)
 * On remplit le tableau avec 16 tile en utilisant add_tile
 *\param g la grille à tester
 *\return true si le test a réussi, false sinon
 */

static bool test_add_tile(grid g);

/**
 *\fn bool test_copy_grid(grid g, grid g2)
 *\brief Teste copy_grid(g, g2)
 *\param g grille à copier
 *\param g2 grille destination
 *\return true si le test a réussi, false sinon
 */

static bool test_copy_grid(grid g, grid g2);

/**
 *\fn bool test_can_move(grid g)
 *\brief Teste can_move(g) sur tous les cas possibles de la grille
 *\param g grille
 *\return true si le test a réussi, false sinon
 */

static bool test_can_move(grid g);

/**
 *\fn bool test_game_over(grid g)
 *\brief Teste game_over
 *\param grid grille g
 *\return true si le test a réussi, false sinon
 */

static bool test_game_over(grid g);

/**
 *\fn bool test_score(grid g)
 *\brief Vérifie que grid_score(g) renvoie le bon score
 *\param g grille
 *\return true si le test a réussi, false sinon
 */

static bool test_score(grid g);

/**
 *\fn static bool test_do_move(grid g);
 *\brief Teste do_move(g) sur tous les cas possibles de la grille
 *\param g grille
 *\return true si le test a réussi, false sinon
 */

static bool test_do_move(grid g);

/**
 *\fn int main(void)
 *\lance tous les test
 */

int main(void);
