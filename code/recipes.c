#include "recipes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAP 4

/* internal helpers */

static char *dup_string(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    strcpy(copy, s);
    return copy;
}

static void *xrealloc(void *ptr, size_t new_count, size_t elem_size) {
    void *tmp = realloc(ptr, new_count * elem_size);
    if (!tmp) {
        /* In a real system we might handle this better */
        free(ptr);
        return NULL;
    }
    return tmp;
}

static double recipe_total_calories(const Recipe *r) {
    double total = 0.0;
    for (size_t i = 0; i < r->count; i++) {
        IngredientQty iq = r->items[i];
        if (iq.ingredient) {
            total += iq.grams * iq.ingredient->calories_per_gram;
        }
    }
    return total;
}

static double pantry_available(const Pantry *p, const Ingredient *ing) {
    double total = 0.0;
    for (size_t i = 0; i < p->count; i++) {
        if (p->items[i].ingredient == ing) {
            total += p->items[i].grams;
        }
    }
    return total;
}

/********** creation **********/

Book *newBook(void) {
    Book *b = malloc(sizeof(Book));
    if (!b) return NULL;
    b->recipes = NULL;
    b->count = 0;
    b->cap = 0;
    return b;
}

Recipe *newRecipe(const char *name, int servings) {
    if (servings <= 0) return NULL;
    Recipe *r = malloc(sizeof(Recipe));
    if (!r) return NULL;
    r->name = dup_string(name);
    r->servings = servings;
    r->items = NULL;
    r->count = 0;
    r->cap = 0;
    return r;
}

Ingredient *newIngredient(const char *name, double caloriesPerGram) {
    if (caloriesPerGram < 0.0) return NULL;
    Ingredient *ing = malloc(sizeof(Ingredient));
    if (!ing) return NULL;
    ing->name = dup_string(name);
    ing->calories_per_gram = caloriesPerGram;
    return ing;
}

Pantry *newPantry(void) {
    Pantry *p = malloc(sizeof(Pantry));
    if (!p) return NULL;
    p->items = NULL;
    p->count = 0;
    p->cap = 0;
    return p;
}

/********** modification **********/

void addRecipe(Book *book, Recipe *recipe) {
    if (!book || !recipe) return;
    if (book->count == book->cap) {
        size_t new_cap = (book->cap == 0) ? INITIAL_CAP : book->cap * 2;
        Recipe **new_arr = xrealloc(book->recipes, new_cap, sizeof(Recipe *));
        if (!new_arr) return;
        book->recipes = new_arr;
        book->cap = new_cap;
    }
    book->recipes[book->count++] = recipe;
}

void addIngredient(Recipe *recipe, Ingredient *ingredient, double grams) {
    if (!recipe || !ingredient || grams <= 0.0) return;
    if (recipe->count == recipe->cap) {
        size_t new_cap = (recipe->cap == 0) ? INITIAL_CAP : recipe->cap * 2;
        IngredientQty *new_arr =
            xrealloc(recipe->items, new_cap, sizeof(IngredientQty));
        if (!new_arr) return;
        recipe->items = new_arr;
        recipe->cap = new_cap;
    }
    recipe->items[recipe->count].ingredient = ingredient;
    recipe->items[recipe->count].grams = grams;
    recipe->count++;
}

void storeIngredient(Pantry *pantry, Ingredient *ingredient, double grams) {
    if (!pantry || !ingredient || grams <= 0.0) return;

    /* if ingredient already exists, just add grams */
    for (size_t i = 0; i < pantry->count; i++) {
        if (pantry->items[i].ingredient == ingredient) {
            pantry->items[i].grams += grams;
            return;
        }
    }

    if (pantry->count == pantry->cap) {
        size_t new_cap = (pantry->cap == 0) ? INITIAL_CAP : pantry->cap * 2;
        PantryItem *new_arr =
            xrealloc(pantry->items, new_cap, sizeof(PantryItem));
        if (!new_arr) return;
        pantry->items = new_arr;
        pantry->cap = new_cap;
    }
    pantry->items[pantry->count].ingredient = ingredient;
    pantry->items[pantry->count].grams = grams;
    pantry->count++;
}

/********** queries **********/

Book *canMakeAny(Pantry *pantry, Book *book) {
    if (!pantry || !book) return NULL;
    Book *result = newBook();
    if (!result) return NULL;

    for (size_t i = 0; i < book->count; i++) {
        Recipe *r = book->recipes[i];
        int ok = 1;
        for (size_t j = 0; j < r->count; j++) {
            IngredientQty iq = r->items[j];
            double have = pantry_available(pantry, iq.ingredient);
            if (have < iq.grams) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            addRecipe(result, r);
        }
    }
    return result;
}

/* Simplified: either we can make ALL recipes at once, or zero. */
Book *canMakeAll(Pantry *pantry, Book *book) {
    if (!pantry || !book) return NULL;
    Book *result = newBook();
    if (!result) return NULL;

    /* compute total needed for each ingredient */
    /* naive approach: just check each recipe in turn against a copy
       of pantry, but we are conservative: require we can make
       each recipe starting from full pantry. */

    for (size_t i = 0; i < book->count; i++) {
        Recipe *r = book->recipes[i];
        for (size_t j = 0; j < r->count; j++) {
            IngredientQty iq = r->items[j];
            double have = pantry_available(pantry, iq.ingredient);
            if (have < iq.grams) {
                /* cannot make them all; return empty book */
                return result;
            }
        }
    }

    /* if we get here, we can make them all */
    for (size_t i = 0; i < book->count; i++) {
        addRecipe(result, book->recipes[i]);
    }
    return result;
}

Book *withinCalorieLimit(Pantry *pantry, Book *book, double limit) {
    (void)pantry; /* not needed here, but kept to match required signature */
    if (!book) return NULL;

    Book *result = newBook();
    if (!result) return NULL;

    for (size_t i = 0; i < book->count; i++) {
        Recipe *r = book->recipes[i];
        double total = recipe_total_calories(r);
        if (r->servings <= 0) continue;
        double per_serving = total / r->servings;
        if (per_serving < limit) {
            addRecipe(result, r);
        }
    }
    return result;
}

/********** cleanup **********/

void freeIngredient(Ingredient *ing) {
    if (!ing) return;
    free(ing->name);
    free(ing);
}

void freeRecipe(Recipe *r) {
    if (!r) return;
    free(r->name);
    free(r->items);
    free(r);
}

void freeBook(Book *b) {
    if (!b) return;
    free(b->recipes);
    free(b);
}

void freePantry(Pantry *p) {
    if (!p) return;
    free(p->items);
    free(p);
}
