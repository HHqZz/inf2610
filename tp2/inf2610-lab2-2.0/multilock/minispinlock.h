/*
 * minispinlock.h
 *
 *  Created on: 2012-01-27
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#ifndef MINISPINLOCK_H_
#define MINISPINLOCK_H_

void mini_spinlock_lock(int *lock);
void mini_spinlock_unlock(int *lock);

#endif /* MINISPINLOCK_H_ */
