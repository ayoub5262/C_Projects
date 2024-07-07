#include "4b.h"
#include <stdio.h>

extern size_t last_alloc;

void nf_free(void *addr) {
	// Ist die Adresse addr sinnvoll?
	if (addr == NULL) return;

	size_t chunk_index = ((char*)addr - heap) / CHUNK_SIZE;

	if (chunk_index >= NUM_CHUNKS || allocation_list[chunk_index].status != CHUNK_ALLOCATED) {
        perror("Invalid free address\n");
        exit(255);
    }
	// Speicher freigeben
	allocation_list[chunk_index].status = CHUNK_FREE;
    size_t old_size = allocation_list[chunk_index].length;

	// Nachfolgende freie Blöcke vereinigen
    size_t next_index = chunk_index + old_size;
    if (next_index < NUM_CHUNKS && allocation_list[next_index].status == CHUNK_FREE) {
        allocation_list[chunk_index].length += allocation_list[next_index].length;
        allocation_list[next_index].length = 0;
    }
    // Vorhergehende freie Blöcke vereinigen
    size_t prev_index = chunk_index;
    while (prev_index > 0 && allocation_list[prev_index - 1].status == CHUNK_FREE)
        prev_index--;

    if (prev_index < chunk_index) {
        allocation_list[prev_index].length += allocation_list[chunk_index].length;
        allocation_list[chunk_index].length = 0;
    }
    // Den letzten Allokationspunkt anpassen, falls er jetzt innerhalb eines freien Blocks liegt
    if (last_alloc >= chunk_index && last_alloc < chunk_index + old_size)
        last_alloc = prev_index;

}
