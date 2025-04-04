#include <dsp/controller_functions.h>
#include <dsp/support_functions.h>
#include <stdio.h>
#include <stdlib.h>

#define H " %-7s"
#define L "-------"
#define F " %7.4f"
#define Q " %7d"
#define q(x) ((int)(int16_t)(x))

int main(int argc, char **argv)
{
	arm_pid_instance_f32 pid_f32 = {};
	arm_pid_instance_q15 pid_q15 = {};
	float32_t in_f32, out_f32;
	q15_t in_q15, out_q15;
	int i, count = 10;

	if (argc < 5 || argc > 6) {
		printf("usage: %s Kp Ki Kd in\n", argv[0]);
		return 1;
	}

	pid_f32.Kp = strtof(argv[1], NULL);
	pid_f32.Ki = strtof(argv[2], NULL);
	pid_f32.Kd = strtof(argv[3], NULL);
	in_f32 = strtof(argv[4], NULL);

	if (argc > 5) {
		count = strtol(argv[5], NULL, 0);
	}

	arm_float_to_q15(&pid_f32.Kp, &pid_q15.Kp, 1);
	arm_float_to_q15(&pid_f32.Ki, &pid_q15.Ki, 1);
	arm_float_to_q15(&pid_f32.Kd, &pid_q15.Kd, 1);
	arm_float_to_q15(&in_f32, &in_q15, 1);

	// ------------------------------------------------

	printf("\n### F32 ###\n\n");

	arm_pid_init_f32(&pid_f32, 1);

	printf(H H H H H " %s\n", "Kp", "Ki", "Kd", "A0", "A1", "A2");
	printf(H H H H H " %s\n", L, L, L, L, L, L);
	printf(F F F F F F "\n",
	       pid_f32.Kp, pid_f32.Ki, pid_f32.Kd,
	       pid_f32.A0, pid_f32.A1, pid_f32.A2);

	printf("\n");

	printf(H H H H " %s\n", "in", "out", "S0", "S1", "S2");
	printf(H H H H " %s\n", L, L, L, L, L);

	for (i = 0; i < count; ++i) {
		out_f32 = arm_pid_f32(&pid_f32, in_f32);
		printf(F F F F F "\n",
		       in_f32, out_f32, pid_f32.state[0],
		       pid_f32.state[1], pid_f32.state[2]);
	}

	// ------------------------------------------------

	printf("\n### Q15 ###\n\n");

	arm_pid_init_q15(&pid_q15, 1);

	printf(H H H H H " %s\n", "Kp", "Ki", "Kd", "A0", "A1", "A2");
	printf(H H H H H " %s\n", L, L, L, L, L, L);
	printf(Q Q Q Q Q Q "\n",
	       q(pid_q15.Kp), q(pid_q15.Ki), q(pid_q15.Kd),
	       q(pid_q15.A0), q(pid_q15.A1), q(pid_q15.A2));

	printf("\n");

	printf(H H H H " %s\n", "in", "out", "S0", "S1", "S2");
	printf(H H H H " %s\n", L, L, L, L, L);

	for (i = 0; i < count; ++i) {
		out_q15 = arm_pid_q15(&pid_q15, in_q15);
		printf(Q Q Q Q Q "\n",
		       q(in_q15), q(out_q15), q(pid_q15.state[0]),
		       q(pid_q15.state[1]), q(pid_q15.state[2]));
	}

	return 0;
}
