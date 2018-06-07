/*
	Simple Linux CLI wrapper for nanosleep()
	
	Copyright 2018, Daniel G Kohler (dgkohler@gmail.com)
	
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	long nanoRequested = 1000;		//Default to 1us
	int status;
	int interrupted = 0;
	
	if(argc > 1) {
		(void) sscanf(argv[1], "%ld", &nanoRequested);
	}
		
	struct timespec requested, remaining;

	do {
		requested.tv_sec = (long)nanoRequested / (long)1000000000;
		requested.tv_nsec = nanoRequested % (long)1000000000;
		
		if(argc > 2) printf("nanosleep called with %ld s + %ld ns requested\n", (long)requested.tv_sec, requested.tv_nsec);

		if(status = nanosleep(&requested , &remaining) < 0)   
		{
			if(errno == EINTR) {
				if(argc > 2) printf("nanosleep interrupted with %ld s + %ld ns remaining\n", (long)remaining.tv_sec, remaining.tv_nsec);
				memcpy(&requested, &remaining, sizeof(requested));
				interrupted = 1;
			}
		  	else if(errno == EINVAL) {
		  		if(argc > 2) printf("Please enter value between 0 and 2^63\n");
		  		return -1;
		  	}
		  	else {
		  		if(argc > 2) printf("nanosleep failed: %s\n", strerror(errno));
		  	}
		}
		else {
			interrupted = 0;
		}
	}
	while (interrupted);
	
	if(argc > 2) printf("Nano sleep successfull for %ld s + %ld ns \n", (long)requested.tv_sec, requested.tv_nsec);

	return 0;
}
