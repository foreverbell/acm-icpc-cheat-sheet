#include <ucontext.h>

void _main() {
  // main() goes here.
}

char stack[STACK_SIZE];

int main() {
  ucontext_t ctx;
  getcontext(&ctx);
  ctx.uc_link = nullptr;
  ctx.uc_stack.ss_sp = stack;
  ctx.uc_stack.ss_size = sizeof(stack);
  ctx.uc_stack.ss_flags = 0;
  makecontext(&ctx, _main, 0);
  setcontext(&ctx);
  return 0;
}
