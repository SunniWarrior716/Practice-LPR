#ifndef RECIPES_H
#define RECIPES_H

#include <stddef.h>

typedef struct Ingredient {
    char *name;
    double calories_per_gram;
} Ingredient;

typedef struct IngredientQty {
    Ingredient *ingredient;
    double grams;
} IngredientQty;

typedef struct Recipe {
    char *name;
    int servings;
    IngredientQty *items;
    size_t count;
    size_t cap;
} Recipe;

typedef struct Book {
    Recipe **recipes;
    size_t count;
    size_t cap;
} Book;

typedef struct PantryItem {
    Ingredient *ingredient;
    double grams;
} PantryItem;

typedef struct Pantry {
    PantryItem *items;
    size_t count;
    size_t cap;
} Pantry;

/* creation */
Book       *newBook(void);
Recipe     *newRecipe(const char *name, int servings);
Ingredient *newIngredient(const char *name, double caloriesPerGram);
Pantry     *newPantry(void);

/* modification */
void addRecipe(Book *book, Recipe *recipe);
void addIngredient(Recipe *recipe, Ingredient *ingredient, double grams);
void storeIngredient(Pantry *pantry, Ingredient *ingredient, double grams);

/* queries */
Book *canMakeAny(Pantry *pantry, Book *book);

/* Simplified: returns a book that contains all recipes we can make
 * *simultaneously*. If we cannot make them all, returns an empty book.
 */
Book *canMakeAll(Pantry *pantry, Book *book);

/* All recipes from book whose per-serving calories are < limit */
Book *withinCalorieLimit(Pantry *pantry, Book *book, double limit);

/* helpers for memory cleanup (for valgrind) */
void freeIngredient(Ingredient *ing);
void freeRecipe(Recipe *r);
void freeBook(Book *b);
void freePantry(Pantry *p);

#endif
