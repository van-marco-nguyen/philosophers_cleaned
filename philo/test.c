/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:29:59 by van               #+#    #+#             */
/*   Updated: 2025/04/05 19:30:13 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"

#include <pthread.h>
#include <stdio.h>

void* thread_task(void *arg) {
    int id = *(int*)arg;
    printf("Thread %d en cours\n", id);
    return NULL;
}

int main() {
    pthread_t tid;
    int arg = 42;
    
    if(pthread_create(&tid, NULL, thread_task, &arg) != 0) {
        perror("Erreur création thread");
        return 1;
    }
    
    pthread_join(tid, NULL);  // Attendre la fin du thread
    return 0;
}
