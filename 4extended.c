#include "4extended.h"
#include <stdio.h>
// Hier ggf. weitere Includes

/*
 * Hier koennen Sie ggf. benoetigte globale Varibalen und/oder Hilfsfunktionen ablegen
 */


/*
 * Hinweis: Implementieren Sie eine Hilfsfunktion, die eine freie Luecke mit der passenden Groesse findet:
 */
static size_t find_gap(size_t req_size) {
	size_t bestfit = NUM_CHUNKS;

	size_t bestfit_size = NUM_CHUNKS + 1;

    for (size_t i = 0; i < NUM_CHUNKS; i++) {
        if (allocation_list[i].status == CHUNK_FREE && allocation_list[i].length >= req_size) {
            if (allocation_list[i].length < bestfit_size) {
                bestfit = i;
                bestfit_size = allocation_list[i].length;
            }
        }
    }
	if (bestfit < NUM_CHUNKS) {
		return bestfit;
	} else {
		return NUM_CHUNKS;
	}
}



void *bf_alloc(size_t size) {
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
    return heap + chunk_index * CHUNK_SIZE;
}



void bf_free(void *addr) {
	// Ist die Adresse addr sinnvoll?
	if (addr == NULL) return;

    size_t chunk_index = ((char *)addr - heap) / CHUNK_SIZE;
    if (chunk_index >= NUM_CHUNKS || allocation_list[chunk_index].status != CHUNK_ALLOCATED) {
        perror("Invalid free address\n");
        exit(255);
    }

    // Speicher freigeben
    allocation_list[chunk_index].status = CHUNK_FREE;
    size_t old_size = allocation_list[chunk_index].length;

    // Merge mit dem naechsten freien Block falls moegilch
    size_t next_index = chunk_index + old_size;
    if (next_index < NUM_CHUNKS && allocation_list[next_index].status == CHUNK_FREE) {
        allocation_list[chunk_index].length += allocation_list[next_index].length;
        allocation_list[next_index].length = 0;
    }

    // Merge mit dem vorherigen freien Block falls moegilch
    if (chunk_index > 0) {
        size_t prev_index = chunk_index - 1;
        while (prev_index > 0 && allocation_list[prev_index].length == 0)
            prev_index--;
        
        if (allocation_list[prev_index].status == CHUNK_FREE) {
            allocation_list[prev_index].length += allocation_list[chunk_index].length;
            allocation_list[chunk_index].length = 0;
        }
    }
}
