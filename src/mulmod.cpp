/* return x*y%mod. no overflow if x,y < mod.
 * remove 'i' in "idiv"/"imul" -> unsigned */
/* originally written by Riatre. */
inline long mulmod(long x, long y, long mod) {
  long ans = 0;
  __asm__ (
    "movq %1,%%rax\n imulq %2\n idivq %3\n"
    :"=d"(ans):"m"(x),"m"(y),"m"(mod):"%rax"
  );
  return ans;
}
