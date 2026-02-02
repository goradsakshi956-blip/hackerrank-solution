#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct package {
    char id[100];
    int weight;
} package;

typedef struct post_office {
    int min_weight;
    int max_weight;
    int packages_count;
    package* packages;
} post_office;

typedef struct town {
    char name[100];
    int offices_count;
    post_office* offices;
} town;

/* Print all packages in a town */
void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

/* Send acceptable packages */
void send_all_acceptable_packages(
    town* source, int source_office,
    town* target, int target_office
) {
    post_office* src = &source->offices[source_office];
    post_office* tgt = &target->offices[target_office];

    package* accepted = malloc(sizeof(package) * src->packages_count);
    package* rejected = malloc(sizeof(package) * src->packages_count);

    int acc = 0, rej = 0;

    for (int i = 0; i < src->packages_count; i++) {
        int w = src->packages[i].weight;
        if (w >= tgt->min_weight && w <= tgt->max_weight)
            accepted[acc++] = src->packages[i];
        else
            rejected[rej++] = src->packages[i];
    }

    tgt->packages = realloc(
        tgt->packages,
        sizeof(package) * (tgt->packages_count + acc)
    );

    for (int i = 0; i < acc; i++)
        tgt->packages[tgt->packages_count + i] = accepted[i];

    tgt->packages_count += acc;

    free(src->packages);
    src->packages = malloc(sizeof(package) * rej);
    for (int i = 0; i < rej; i++)
        src->packages[i] = rejected[i];

    src->packages_count = rej;

    free(accepted);
    free(rejected);
}

/* Town with most packages */
town town_with_most_packages(town* towns, int towns_count) {
    int max = -1;
    town result;

    for (int i = 0; i < towns_count; i++) {
        int total = 0;
        for (int j = 0; j < towns[i].offices_count; j++)
            total += towns[i].offices[j].packages_count;

        if (total > max) {
            max = total;
            result = towns[i];
        }
    }
    return result;
}

/* Find town by name */
town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++)
        if (strcmp(towns[i].name, name) == 0)
            return &towns[i];
    return NULL;
}

int main() {
    int towns_count;
    scanf("%d", &towns_count);

    town* towns = malloc(sizeof(town) * towns_count);

    for (int i = 0; i < towns_count; i++) {
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);

        towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);

        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d %d %d",
                  &towns[i].offices[j].packages_count,
                  &towns[i].offices[j].min_weight,
                  &towns[i].offices[j].max_weight);

            towns[i].offices[j].packages =
                malloc(sizeof(package) * towns[i].offices[j].packages_count);

            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }

    int queries;
    scanf("%d", &queries);

    while (queries--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            char name[100];
            scanf("%s", name);
            print_all_packages(*find_town(towns, towns_count, name));
        } else if (type == 2) {
            char src[100], dst[100];
            int so, dof;
            scanf("%s %d %s %d", src, &so, dst, &dof);
            send_all_acceptable_packages(
                find_town(towns, towns_count, src), so,
                find_town(towns, towns_count, dst), dof
            );
        } else {
            town t = town_with_most_packages(towns, towns_count);
            printf("Town with the most number of packages is %s\n", t.name);
        }
    }
    return 0;
}
