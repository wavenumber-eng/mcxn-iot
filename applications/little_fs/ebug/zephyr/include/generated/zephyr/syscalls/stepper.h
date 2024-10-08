/* auto-generated by gen_syscalls.py, don't edit */

#ifndef Z_INCLUDE_SYSCALLS_STEPPER_H
#define Z_INCLUDE_SYSCALLS_STEPPER_H


#include <zephyr/tracing/tracing_syscall.h>

#ifndef _ASMLANGUAGE

#include <stdarg.h>

#include <zephyr/syscall_list.h>
#include <zephyr/syscall.h>

#include <zephyr/linker/sections.h>


#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_stepper_enable(const struct device * dev, const bool enable);

__pinned_func
static inline int stepper_enable(const struct device * dev, const bool enable)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; const bool val; } parm1 = { .val = enable };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_ENABLE);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_enable(dev, enable);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_enable(dev, enable) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_ENABLE, stepper_enable, dev, enable); 	syscall__retval = stepper_enable(dev, enable); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_ENABLE, stepper_enable, dev, enable, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_move(const struct device * dev, int32_t micro_steps, struct k_poll_signal * async);

__pinned_func
static inline int stepper_move(const struct device * dev, int32_t micro_steps, struct k_poll_signal * async)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; int32_t val; } parm1 = { .val = micro_steps };
		union { uintptr_t x; struct k_poll_signal * val; } parm2 = { .val = async };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_STEPPER_MOVE);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_move(dev, micro_steps, async);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_move(dev, micro_steps, async) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_MOVE, stepper_move, dev, micro_steps, async); 	syscall__retval = stepper_move(dev, micro_steps, async); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_MOVE, stepper_move, dev, micro_steps, async, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_set_max_velocity(const struct device * dev, uint32_t micro_steps_per_second);

__pinned_func
static inline int stepper_set_max_velocity(const struct device * dev, uint32_t micro_steps_per_second)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; uint32_t val; } parm1 = { .val = micro_steps_per_second };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_SET_MAX_VELOCITY);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_set_max_velocity(dev, micro_steps_per_second);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_set_max_velocity(dev, micro_steps_per_second) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_SET_MAX_VELOCITY, stepper_set_max_velocity, dev, micro_steps_per_second); 	syscall__retval = stepper_set_max_velocity(dev, micro_steps_per_second); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_SET_MAX_VELOCITY, stepper_set_max_velocity, dev, micro_steps_per_second, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_set_micro_step_res(const struct device * dev, enum micro_step_resolution resolution);

__pinned_func
static inline int stepper_set_micro_step_res(const struct device * dev, enum micro_step_resolution resolution)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; enum micro_step_resolution val; } parm1 = { .val = resolution };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_SET_MICRO_STEP_RES);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_set_micro_step_res(dev, resolution);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_set_micro_step_res(dev, resolution) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_SET_MICRO_STEP_RES, stepper_set_micro_step_res, dev, resolution); 	syscall__retval = stepper_set_micro_step_res(dev, resolution); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_SET_MICRO_STEP_RES, stepper_set_micro_step_res, dev, resolution, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_get_micro_step_res(const struct device * dev, enum micro_step_resolution * resolution);

__pinned_func
static inline int stepper_get_micro_step_res(const struct device * dev, enum micro_step_resolution * resolution)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; enum micro_step_resolution * val; } parm1 = { .val = resolution };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_GET_MICRO_STEP_RES);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_get_micro_step_res(dev, resolution);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_get_micro_step_res(dev, resolution) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_GET_MICRO_STEP_RES, stepper_get_micro_step_res, dev, resolution); 	syscall__retval = stepper_get_micro_step_res(dev, resolution); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_GET_MICRO_STEP_RES, stepper_get_micro_step_res, dev, resolution, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_set_actual_position(const struct device * dev, int32_t value);

__pinned_func
static inline int stepper_set_actual_position(const struct device * dev, int32_t value)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; int32_t val; } parm1 = { .val = value };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_SET_ACTUAL_POSITION);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_set_actual_position(dev, value);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_set_actual_position(dev, value) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_SET_ACTUAL_POSITION, stepper_set_actual_position, dev, value); 	syscall__retval = stepper_set_actual_position(dev, value); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_SET_ACTUAL_POSITION, stepper_set_actual_position, dev, value, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_get_actual_position(const struct device * dev, int32_t * value);

__pinned_func
static inline int stepper_get_actual_position(const struct device * dev, int32_t * value)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; int32_t * val; } parm1 = { .val = value };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_GET_ACTUAL_POSITION);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_get_actual_position(dev, value);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_get_actual_position(dev, value) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_GET_ACTUAL_POSITION, stepper_get_actual_position, dev, value); 	syscall__retval = stepper_get_actual_position(dev, value); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_GET_ACTUAL_POSITION, stepper_get_actual_position, dev, value, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_set_target_position(const struct device * dev, int32_t value, struct k_poll_signal * async);

__pinned_func
static inline int stepper_set_target_position(const struct device * dev, int32_t value, struct k_poll_signal * async)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; int32_t val; } parm1 = { .val = value };
		union { uintptr_t x; struct k_poll_signal * val; } parm2 = { .val = async };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_STEPPER_SET_TARGET_POSITION);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_set_target_position(dev, value, async);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_set_target_position(dev, value, async) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_SET_TARGET_POSITION, stepper_set_target_position, dev, value, async); 	syscall__retval = stepper_set_target_position(dev, value, async); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_SET_TARGET_POSITION, stepper_set_target_position, dev, value, async, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_is_moving(const struct device * dev, bool * is_moving);

__pinned_func
static inline int stepper_is_moving(const struct device * dev, bool * is_moving)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; bool * val; } parm1 = { .val = is_moving };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_STEPPER_IS_MOVING);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_is_moving(dev, is_moving);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_is_moving(dev, is_moving) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_IS_MOVING, stepper_is_moving, dev, is_moving); 	syscall__retval = stepper_is_moving(dev, is_moving); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_IS_MOVING, stepper_is_moving, dev, is_moving, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_stepper_enable_constant_velocity_mode(const struct device * dev, enum stepper_direction direction, uint32_t value);

__pinned_func
static inline int stepper_enable_constant_velocity_mode(const struct device * dev, enum stepper_direction direction, uint32_t value)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; enum stepper_direction val; } parm1 = { .val = direction };
		union { uintptr_t x; uint32_t val; } parm2 = { .val = value };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_STEPPER_ENABLE_CONSTANT_VELOCITY_MODE);
	}
#endif
	compiler_barrier();
	return z_impl_stepper_enable_constant_velocity_mode(dev, direction, value);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define stepper_enable_constant_velocity_mode(dev, direction, value) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_STEPPER_ENABLE_CONSTANT_VELOCITY_MODE, stepper_enable_constant_velocity_mode, dev, direction, value); 	syscall__retval = stepper_enable_constant_velocity_mode(dev, direction, value); 	sys_port_trace_syscall_exit(K_SYSCALL_STEPPER_ENABLE_CONSTANT_VELOCITY_MODE, stepper_enable_constant_velocity_mode, dev, direction, value, syscall__retval); 	syscall__retval; })
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
#endif /* include guard */
