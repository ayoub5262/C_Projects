#include "4a.h"
#include <stdio.h>

size_t last_alloc = 0; // Verwenden Sie diese Variable um letzte Allokation festzuhalten.

/*
 * Hinweis: Implementieren Sie eine Hilfsfunktion, die eine freie Luecke mit der passenden Groesse findet:
 */
static size_t find_gap(size_t req_size) {
	size_t i = last_alloc;
    size_t count = 0;

    // Durchlaufen die allocation_list ausgehend vom last_alloc
    while (count < NUM_CHUNKS) {
        // Wenn wir einen freien Block mit ausreichender Größe finden
        if (allocation_list[i].status == CHUNK_FREE && allocation_list[i].length >= req_size)
            return i;

        // Zum nächsten Block wechseln, ggf. umbrechen
        i = (i + 1) % NUM_CHUNKS;
        count++;
    }
	return NUM_CHUNKS;
}



void *nf_alloc(size_t size) {
	// Ist der Wert von size sinnvoll?
	if (size == 0) return NULL;

	size = size_to_chunks(size);
	size_t chunk_index = find_gap(size);

	// Kein geeigneter Block gefunden
	if (chunk_index == NUM_CHUNKS) return NULL;

	// Allokation durchführen
    allocation_list[chunk_index].status = CHUNK_ALLOCATED;
    size_t remaining = allocation_list[chunk_index].length - size;
    allocation_list[chunk_index].length = size;

    if (remaining > 0) {
        allocation_list[chunk_index + size].status = CHUNK_FREE;
        allocation_list[chunk_index + size].length = remaining;
    }

	last_alloc = chunk_index;

	return heap + chunk_index * CHUNK_SIZE;
}
