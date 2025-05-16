#include <uci.h>

void main()
{
    char path[] = "network.lan.proto";
    char buffer[80];
    struct uci_ptr ptr;
    struct uci_context *c = uci_alloc_context();

    if (!c)
        return;

    if ((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK) ||
        (ptr.o == NULL || ptr.o->v.string == NULL))
    {
        uci_free_context(c);
        return;
    }

    if (ptr.flags & UCI_LOOKUP_COMPLETE)
        strcpy(buffer, ptr.o->v.string);

    printf("%s\n", buffer);

    // setting UCI values
    // -----------------------------------------------------------
    // this will set the value to 1234
    ptr.value = "1234";
    // commit your changes to make sure that UCI values are saved
    if (uci_commit(c, &ptr.p, false) != UCI_OK)
    {
        uci_free_context(c);
        uci_perror(c, "UCI Error");
        return;
    }

    uci_free_context(c);
    printf("UCI value set successfully\n");
}