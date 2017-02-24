/**
 *	Julian Sovernigo	0948924
 *	gsoverni@mail.uoguelph.ca
 *	CIS*3110_W17
 *
 * 	This file contains source for a struct that can be used to contain process
 * 	events.
 */

enum event_t
{
	PROCESS,THREAD	
};

struct event
{
	union event_u event;
	enum event_t type;
};

union event_u
{

};
