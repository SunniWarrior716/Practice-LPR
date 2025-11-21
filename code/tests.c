#include <criterion/criterion.h>
#include "recipes.h"

/* Helper to avoid repeating sample ingredients */
static Ingredient *make_sugar(void) {
    return newIngredient("sugar", 4.0);   // 4 cal/gram (fake data is okay)
}

static Ingredient *make_flour(void) {
    return newIngredient("flour", 3.5);
}

/*********** creation tests ***********/

Test(recipes, new_book_starts_empty) {
    Book *b = newBook();
    cr_assert_not_null(b, "newBook should not return NULL");
    cr_assert_eq(b->count, 0, "new book should start with 0 recipes");
    freeBook(b);
}

Test(recipes, new_recipe_has_name_and_servings) {
    Recipe *r = newRecipe("Cake", 8);
    cr_assert_not_null(r);
    cr_assert_str_eq(r->name, "Cake");
    cr_assert_eq(r->servings, 8);
    cr_assert_eq(r->count, 0);
    freeRecipe(r);
}

Test(recipes, new_ingredient_has_name_and_calories) {
    Ingredient *sugar = make_sugar();
    cr_assert_not_null(sugar);
    cr_assert_str_eq(sugar->name, "sugar");
    cr_assert_eq(sugar->calories_per_gram, 4.0);
    freeIngredient(sugar);
}

Test(recipes, new_pantry_starts_empty) {
    Pantry *p = newPantry();
    cr_assert_not_null(p);
    cr_assert_eq(p->count, 0);
    freePantry(p);
}

/*********** modification tests ***********/

Test(recipes, add_recipe_increases_book_count) {
    Book *b = newBook();
    Recipe *r1 = newRecipe("Cake", 8);

    cr_assert_eq(b->count, 0);
    addRecipe(b, r1);
    cr_assert_eq(b->count, 1);
    cr_assert_eq(b->recipes[0], r1);

    freeBook(b);   // assumes freeBook does NOT free recipes themselves
    freeRecipe(r1);
}

Test(recipes, add_ingredient_to_recipe) {
    Recipe *r = newRecipe("Cake", 8);
    Ingredient *sugar = make_sugar();

    addIngredient(r, sugar, 100.0); // 100g
    cr_assert_eq(r->count, 1);
    cr_assert_eq(r->items[0].ingredient, sugar);
    cr_assert_float_eq(r->items[0].grams, 100.0, 1e-6);

    freeRecipe(r);
    freeIngredient(sugar);
}

Test(recipes, store_ingredient_in_pantry_adds_quantity) {
    Pantry *p = newPantry();
    Ingredient *sugar = make_sugar();

    storeIngredient(p, sugar, 200.0);
    cr_assert_eq(p->count, 1);
    cr_assert_eq(p->items[0].ingredient, sugar);
    cr_assert_float_eq(p->items[0].grams, 200.0, 1e-6);

    freePantry(p);
    freeIngredient(sugar);
}

/*********** query tests ***********/

Test(recipes, within_calorie_limit_filters_high_calories) {
    Book *b = newBook();
    Ingredient *sugar = make_sugar();
    Ingredient *flour = make_flour();

    Recipe *r1 = newRecipe("LowCalCake", 4);
    addIngredient(r1, flour, 50.0); // 50 * 3.5 = 175 total, 43.75 per serving

    Recipe *r2 = newRecipe("SugarBomb", 2);
    addIngredient(r2, sugar, 300.0); // 300 * 4 = 1200 total, 600 per serving

    addRecipe(b, r1);
    addRecipe(b, r2);

    Pantry *p = newPantry(); // not actually needed for calorie calc here

    Book *filtered = withinCalorieLimit(p, b, 100.0); // limit per serving

    cr_assert_eq(filtered->count, 1);
    cr_assert_eq(filtered->recipes[0], r1);

    freeBook(filtered);
    freePantry(p);
    freeBook(b);
    freeRecipe(r1);
    freeRecipe(r2);
    freeIngredient(sugar);
    freeIngredient(flour);
}

Test(recipes, can_make_any_uses_pantry_quantities) {
    Book *b = newBook();
    Ingredient *sugar = make_sugar();

    Recipe *r1 = newRecipe("SmallCake", 2);
    addIngredient(r1, sugar, 50.0);

    Recipe *r2 = newRecipe("BigCake", 4);
    addIngredient(r2, sugar, 500.0);

    addRecipe(b, r1);
    addRecipe(b, r2);

    Pantry *p = newPantry();
    storeIngredient(p, sugar, 100.0); // enough for SmallCake but not BigCake

    Book *possible = canMakeAny(p, b);

    cr_assert_eq(possible->count, 1);
    cr_assert_eq(possible->recipes[0], r1);

    freeBook(possible);
    freePantry(p);
    freeBook(b);
    freeRecipe(r1);
    freeRecipe(r2);
    freeIngredient(sugar);
}

Test(recipes, can_make_all_returns_all_or_empty) {
    Book *b = newBook();
    Ingredient *sugar = make_sugar();

    Recipe *r1 = newRecipe("Cake1", 2);
    addIngredient(r1, sugar, 50.0);

    Recipe *r2 = newRecipe("Cake2", 2);
    addIngredient(r2, sugar, 50.0);

    addRecipe(b, r1);
    addRecipe(b, r2);

    Pantry *p = newPantry();
    storeIngredient(p, sugar, 100.0); // exactly enough for both

    Book *all = canMakeAll(p, b);
    cr_assert_eq(all->count, 2);

    freeBook(all);
    freePantry(p);
    freeBook(b);
    freeRecipe(r1);
    freeRecipe(r2);
    freeIngredient(sugar);
}
