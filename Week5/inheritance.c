// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *new = malloc(sizeof(person));
    new->parents[0] = NULL;
    new->parents[1] = NULL;
    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        new->parents[0] = parent0;
        new->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        new->alleles[0] = rand() % 2 == 0 ? parent0->alleles[0] : parent0->alleles[1];
        new->alleles[1] = rand() % 2 == 0 ? parent1->alleles[0] : parent1->alleles[1];
        // new_person->alleles[0] = parent0->alleles[rand() % 2];
        // new_person->alleles[1] = parent1->alleles[rand() % 2];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        new->parents[0] = NULL;
        new->parents[1] = NULL;
        // TODO: Randomly assign alleles
        new->alleles[0] = random_allele();
        new->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return new;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
    p = NULL;
    // ChatGPT:
    // 在 C 或 C++ 中，使用 free(p) 释放指针 p 指向的内存后，指针 p 并不会自动变为 NULL。
    // 它仍然指向已经释放的内存，这被称为“悬挂指针”。
    // 在 C 或 C++ 中，free(p) 之后，表达式 p == NULL 的结果是 假，除非你手动将 p 设置为 NULL。
    // 思考:
    // 但这里不设置 p = NULL , 仍可以使递归完成 why?

    // 此递归函数大致如此: 先一直call新的free_family函数直到父母都是NULL,
    // 然后到达最后一步, 此时p是指向最后一代某个人的指针, 所以最后一代的这个人被删除
    // 这个函数弹出, 继续free p 的 child, 直到最后的child被free, 递归函数结束
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
