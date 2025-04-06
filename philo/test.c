/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:29:59 by van               #+#    #+#             */
/*   Updated: 2025/04/06 10:39:35 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    pthread_mutex_t mutex;
    int* nombres;
    int* ordre_execution;
    int current_index;
    int max_threads;
} SharedData;

typedef struct {
    int id;
    SharedData* shared;
} ThreadData;

void* task(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    while(1) {
        pthread_mutex_lock(&data->shared->mutex);
        
        // Vérifier si c'est notre tour en comparant avec l'ordre d'exécution
        if(data->shared->current_index < data->shared->max_threads && 
           data->shared->ordre_execution[data->shared->current_index] == data->id) {
            
            int valeur = data->shared->nombres[data->id];
            printf("Thread %d (valeur=%d) s'exécute\n", data->id, valeur);
            
            data->shared->current_index++;
            pthread_mutex_unlock(&data->shared->mutex);
            break;
        }
        
        pthread_mutex_unlock(&data->shared->mutex);
        usleep(1000);
    }
    
    free(data);
    return NULL;
}

int main() {
    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];
    
    // Initialisation des données partagées
    SharedData* shared = malloc(sizeof(SharedData));
    shared->nombres = malloc(NUM_THREADS * sizeof(int));
    shared->ordre_execution = malloc(NUM_THREADS * sizeof(int));
    shared->current_index = 0;
    shared->max_threads = NUM_THREADS;
    pthread_mutex_init(&shared->mutex, NULL);

    // Exemple de tableau (modifiable)
    int nombres[NUM_THREADS] = {3, 1, 2}; // Ordre d'exécution: 2, 1, 0
    
    // Copier les valeurs et déterminer l'ordre d'exécution
    for(int i=0; i<NUM_THREADS; i++) {
        shared->nombres[i] = nombres[i];
        shared->ordre_execution[i] = i;
    }
    
    // Trier les indices selon les valeurs (ordre croissant)
    for(int i=0; i<NUM_THREADS-1; i++) {
        for(int j=i+1; j<NUM_THREADS; j++) {
            if(shared->nombres[shared->ordre_execution[i]] > shared->nombres[shared->ordre_execution[j]]) {
                int temp = shared->ordre_execution[i];
                shared->ordre_execution[i] = shared->ordre_execution[j];
                shared->ordre_execution[j] = temp;
            }
        }
    }
    
    // Création des threads
    for(int i=0; i<NUM_THREADS; i++) {
        ThreadData* data = malloc(sizeof(ThreadData));
        data->id = i;
        data->shared = shared;
        pthread_create(&threads[i], NULL, task, data);
    }
    
    // Attente des threads
    for(int i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Nettoyage
    free(shared->nombres);
    free(shared->ordre_execution);
    pthread_mutex_destroy(&shared->mutex);
    free(shared);
    
    return 0;
}
