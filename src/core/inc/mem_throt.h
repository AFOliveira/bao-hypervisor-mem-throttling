/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __mem_throt_H__
#define __mem_throt_H__

#include <timer.h>
#include <events.h>
#include <bitmap.h>


typedef struct mem_throt_info {
	int budget;              
	bool throttled;			 
	uint64_t counter_id;
	uint64_t period_us;
	uint64_t period_counts;
	uint64_t num_tickets;
	uint64_t num_tickets_left;
	uint64_t ticket_budget;
}mem_throt_t;

extern bool is_mem_throt_initialized;

void mem_throt_config(uint64_t period_us, uint64_t num_tickets_vm, uint64_t ticket_budget, uint64_t* num_tickets_cpu);

void mem_throt_init();

void mem_throt_period_timer_callback(irqid_t);

/* budget is used up. PMU generate an interrupt */
void mem_throt_event_overflow_callback(irqid_t); 
void mem_throt_process_overflow(void);

void mem_throt_timer_init(irq_handler_t hander);
void mem_throt_events_init(events_enum event, unsigned long budget, irq_handler_t handler);

#endif /* __mem_throt_H__ */