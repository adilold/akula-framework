/***************************************************************************
 *   Copyright (C) 2006 by Krasimir Marinov   *
 *   krasimir.vanev@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef THREAD_MUTEX_H
#define THREAD_MUTEX_H

#include <pthread.h>

namespace utils
{
    class CConditionObject;

    class Thread_Mutex
    {
        friend class CConditionObject;
        
    public:
        Thread_Mutex(void)
        {
            ::pthread_mutex_init(&m_Mutex, NULL);
        }
        
        ~Thread_Mutex(void)
        {
            ::pthread_mutex_destroy(&m_Mutex);
        }

        ///Returns 0 if successfull
        int acquire(void)
        {
            return ::pthread_mutex_lock(&m_Mutex);
        }

        ///Returns 0 if successfull
        int release(void)
        {
            return ::pthread_mutex_unlock(&m_Mutex);
        }


    private:
        pthread_mutex_t m_Mutex;

        /*Disallow copying and assignment*/
        Thread_Mutex(const Thread_Mutex&);
        void operator=(const Thread_Mutex&);
    };
}//namespace utils

#endif /*THREAD_MUTEX_H*/

