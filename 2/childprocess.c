#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("[Child] Received sorted array. Printing in reverse order:\n");

    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }

    printf("\n[Child] Done.\n");
    return 0;
}

